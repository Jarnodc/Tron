#pragma once
#include "UIButton.h"

class SkipLevelButton final : public UIButton
{
public:
	SkipLevelButton(dae::GameObject* pGO, const SDL_Rect& srcRect, const SDL_Rect& dstRect, const std::string& path, bool hasPressedImage = true)
		:UIButton(pGO, srcRect, dstRect, path, hasPressedImage){}
	~SkipLevelButton() override = default;

	SkipLevelButton(const SkipLevelButton& other) = delete;
	SkipLevelButton(SkipLevelButton&& other) noexcept = delete;
	SkipLevelButton& operator=(const SkipLevelButton& other) = delete;
	SkipLevelButton& operator=(SkipLevelButton&& other) noexcept = delete;

	void Render() const override;

	void OnButtonDown() override{}
	void OnButtonUp() override;
private:
};

