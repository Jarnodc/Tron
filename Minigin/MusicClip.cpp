#include "MiniginPCH.h"
#include "MusicClip.h"


MusicClip::MusicClip(const std::string& path, int loops, int volume)
	:Clip(path, loops, volume)
{
}

MusicClip::~MusicClip()
{
	Mix_FreeMusic(m_pSample);
	m_pSample = nullptr;
}

bool MusicClip::operator==(const MusicClip& ac) const
{
	return ac.m_Loops == m_Loops && ac.m_Volume == m_Volume && ac.m_Path == m_Path;
}

bool MusicClip::LoadWav()
{
	m_pSample = Mix_LoadMUS(m_Path.c_str());
	SetVolume(m_Volume);
	if (m_pSample)
		return true;

	printf("Mix_LoadMUS: %s\n", Mix_GetError());
	return false;

}

void MusicClip::Play()
{
	m_Channel = Mix_PlayMusic(m_pSample, m_Loops);
	if (m_Channel == -1)
	{
		printf("Mix_PlayMusic: %s\n", Mix_GetError());
	}
}

void MusicClip::Pause() const
{
	if (m_Channel != -1)
	{
		Mix_PauseMusic();
	}
}

void MusicClip::Resume() const
{
	if (m_Channel != -1)
	{
		Mix_ResumeMusic();
	}
}

void MusicClip::SetVolume(const int volume)
{
	m_Volume = Mix_VolumeMusic(volume);
}

bool MusicClip::IsPlaying() const
{
	return Mix_PlayingMusic() == 1;
}
