#pragma once
class Clip
{
protected:
	std::string m_Path;
	int m_Volume;
	int m_Loops;
	int m_Channel;
public:
	explicit Clip(const std::string& path, int loops, int volume);
	virtual ~Clip() = default;

	Clip(const Clip& other) = delete;
	Clip(Clip&& other) = delete;
	Clip& operator=(const Clip& other) = delete;
	Clip& operator=(Clip&& other) noexcept = delete;
	bool operator==(const Clip& c) const;

	virtual bool LoadWav() = 0;

	virtual void Play() = 0;
	virtual void Pause() const = 0;
	virtual void Resume() const = 0;
	virtual void SetVolume(const int volume) = 0;
	virtual bool IsPlaying() const = 0;
};

