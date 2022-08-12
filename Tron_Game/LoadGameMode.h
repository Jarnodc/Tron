#pragma once
#include <UIButton.h>
class LoadGameMode final : public UIButton
{
public:
	LoadGameMode(dae::GameObject* pGO, const SDL_Rect& srcRect, const SDL_Rect& dstRect, const std::string& path, const std::string& levelName) :UIButton(pGO, srcRect, dstRect, path), m_LevelName{ levelName } {}

	LoadGameMode(const LoadGameMode& other) = delete;
	LoadGameMode(LoadGameMode&& other) noexcept = delete;
	LoadGameMode& operator=(const LoadGameMode& other) = delete;
	LoadGameMode& operator=(LoadGameMode&& other) noexcept = delete;

	void Update() override{}
	void FixedUpdate() override{}
	void Render() const override;

	void OnButtonDown() override{}
	void OnButtonUp() override;

private:
	const std::string m_LevelName;
};

