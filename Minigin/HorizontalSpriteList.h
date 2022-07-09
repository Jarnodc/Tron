#pragma once
#include "SpriteList.h"
class HorizontalSpriteList final: public SpriteList
{
public:
	enum class Allignment
	{
		Left,Right
	};
	HorizontalSpriteList(dae::GameObject* pGO, SpriteComponent* spriteTemplate, int beginAmount = 0,Allignment allignment = Allignment::Left);
	~HorizontalSpriteList() override = default;

	HorizontalSpriteList(const HorizontalSpriteList& other) = delete;
	HorizontalSpriteList(HorizontalSpriteList&& other) noexcept = delete;
	HorizontalSpriteList& operator=(const HorizontalSpriteList& other) = delete;
	HorizontalSpriteList& operator=(HorizontalSpriteList&& other) noexcept = delete;

	void AddItem(int amount) const override;
	void AddItem(SpriteComponent* item) const override;

	void Update() override{}
	void FixedUpdate() override{}
	void Render() const override{}
private:
	Allignment m_Allignment;
};

