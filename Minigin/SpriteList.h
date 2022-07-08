#pragma once
#include "Component.h"
#include "SpriteComponent.h"

class SpriteList : public Component
{
public:
	SpriteList(const SpriteList& other) = delete;
	SpriteList(SpriteList&& other) noexcept = delete;
	SpriteList& operator=(const SpriteList& other) = delete;
	SpriteList& operator=(SpriteList&& other) noexcept = delete;


	void AddItem(int amount = 1) const;
	void AddItem(SpriteComponent* item) const;

	void RemoveItem(int amount = 1) const;
	void RemoveItem(const SpriteComponent* item) const;
	
protected:
	SpriteList(dae::GameObject* pGO):Component(pGO){}
	~SpriteList() override = default;


	SpriteComponent* m_pSpriteTemplate{ nullptr };
private:
};

