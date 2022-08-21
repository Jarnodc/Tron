#include "MiniginPCH.h"
#include "Sound_System.h"

#include <mutex>
#include <queue>
#include <stack>

#include "AudioClip.h"
#include "InputManager.h"
#include "MusicClip.h"

class SDLSoundSystem::SoundSystemImpl final
{
public:
	SoundSystemImpl() = default;
	~SoundSystemImpl();

	SoundSystemImpl(const SoundSystemImpl& other) = delete;
	SoundSystemImpl(SoundSystemImpl&& other) noexcept = delete;
	SoundSystemImpl& operator=(const SoundSystemImpl& other) = delete;
	SoundSystemImpl& operator=(SoundSystemImpl&& other) noexcept = delete;

	void AddToQueue(const std::string& filename, int loops = 0, int volume = 50);
	void StopQueue() { m_Active = false; };
	void CheckQueue();

private:
	bool LoadSound(Clip* ac);
	void PlaySound(Clip* ac);

	bool m_Active = true;
	std::mutex m_Mutex;
	std::queue<Clip*> m_pSoundQueue{};
};


SDLSoundSystem::SDLSoundSystem()
	:m_pImpl(new SoundSystemImpl())
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	m_thread = std::thread(&SDLSoundSystem::CheckQueue,this);
}

SDLSoundSystem::~SDLSoundSystem()
{
	m_thread.join();
	Mix_CloseAudio();
	delete m_pImpl;
	m_pImpl = nullptr;
}

void SDLSoundSystem::AddToQueue(const std::string& filename, int loops, int volume)
{
	m_pImpl->AddToQueue(filename, loops, volume);
}

void SDLSoundSystem::CheckQueue()
{
	m_pImpl->CheckQueue();
}

void SDLSoundSystem::StopQueue()
{
	m_pImpl->StopQueue();
}


SDLSoundSystem::SoundSystemImpl::~SoundSystemImpl()
{
	for (size_t i = 0; i < m_pSoundQueue.size(); ++i)
	{
		m_pSoundQueue.pop();
	}
}

void SDLSoundSystem::SoundSystemImpl::AddToQueue(const std::string& filename, int loops, int volume)
{
	m_Mutex.lock();
	if(filename.ends_with("wav"))
		m_pSoundQueue.push(new AudioClip("../Data/" + filename, loops, volume));
	else if (filename.ends_with("mp3"))
		m_pSoundQueue.push(new MusicClip("../Data/" + filename, loops, volume));
	m_Mutex.unlock();
}

void SDLSoundSystem::SoundSystemImpl::CheckQueue()
{
	std::vector<Clip*> ac {};
	while (m_Active)
	{
		if (!m_pSoundQueue.empty())
		{
			m_Mutex.lock();
			ac.emplace_back(m_pSoundQueue.front());
			m_pSoundQueue.pop();
			m_Mutex.unlock();
			for (size_t i = 0; i < ac.size(); ++i)
			{
				if (ac[i]->IsPlaying())
					continue;
				if (LoadSound(ac[i]))
				{
					PlaySound(ac[i]);
					break;
				}
			}
		}
		if(!ac.empty())
		{
			for (size_t i = 0; i < ac.size(); ++i)
			{
				if (ac[i]->IsPlaying())
					continue;
				delete ac[i];
				ac[i] = nullptr;
				ac.erase(std::ranges::remove(ac,ac[i]).begin());
			}
		}
	}
	for (size_t i = 0; i < ac.size(); ++i)
	{
		delete ac[i];
		ac[i] = nullptr;
	}
	ac.clear();
}

bool SDLSoundSystem::SoundSystemImpl::LoadSound(Clip* ac)
{
	return ac->LoadWav();
}

void SDLSoundSystem::SoundSystemImpl::PlaySound(Clip* ac)
{
	ac->Play();
}
