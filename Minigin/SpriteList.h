#pragma once
#include "Component.h"
#include "SpriteComponent.h"

class SpriteList : public Component
{
public:
	~SpriteList() override { delete m_pSpriteTemplate; m_pSpriteTemplate = nullptr; }

	SpriteList(const SpriteList& other) = delete;
	SpriteList(SpriteList&& other) noexcept = delete;
	SpriteList& operator=(const SpriteList& other) = delete;
	SpriteList& operator=(SpriteList&& other) noexcept = delete;

	virtual void AddItem(int  = 1) const{}
	virtual void AddItem(SpriteComponent* ) const{}

	virtual void RemoveItem(int amount = 1) const;
	virtual void RemoveItem(const SpriteComponent* item) const;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override;
	
protected:
	SpriteList(dae::GameObject* pGO, SpriteComponent* spriteTemplate):Component(pGO), m_pSpriteTemplate(spriteTemplate) {}


	SpriteComponent* m_pSpriteTemplate{ nullptr };
private:
};

