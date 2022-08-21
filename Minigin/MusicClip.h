#pragma once
#include "Clip.h"
#include <SDL_mixer.h>
class MusicClip final :  public Clip
{
private:
	Mix_Music* m_pSample = nullptr;
public:
	explicit MusicClip(const std::string& path, int loops, int volume);
	~MusicClip() override;

	MusicClip(const MusicClip& other) = delete;
	MusicClip(MusicClip&& other) = delete;
	MusicClip& operator=(const MusicClip& other) = delete;
	MusicClip& operator=(MusicClip&& other) noexcept = delete;
	bool operator==(const MusicClip& ac) const;

	bool LoadWav() override;

	void Play() override;
	void Pause() const override;
	void Resume() const override;
	void SetVolume(const int volume) override;
	bool IsPlaying() const override;
};

