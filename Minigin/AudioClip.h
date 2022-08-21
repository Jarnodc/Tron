#pragma once
#include <string>

#include "Clip.h"
#include "SDL_mixer.h"

class AudioClip final : public Clip
{
private:
	Mix_Chunk* m_pSample = nullptr;
public:
	explicit AudioClip(const std::string& path, int loops, int volume);
	~AudioClip() override;

	AudioClip(const AudioClip& other) = delete;
	AudioClip(AudioClip&& other) = delete;
	AudioClip& operator=(const AudioClip& other) = delete;
	AudioClip& operator=(AudioClip&& other) noexcept = delete;
	bool operator==(const AudioClip& ac) const;

	bool LoadWav() override;

	void Play() override;
	void Pause() const override;
	void Resume() const override;
	void SetVolume(const int volume) override;
	bool IsPlaying() const override;
};
