#include "MiniginPCH.h"
#include "SpriteList.h"

void SpriteList::AddItem(int amount) const
{
	assert(m_pSpriteTemplate);
	const auto pGO = new dae::GameObject();
	pGO->AddComponent(m_pSpriteTemplate);
	GetGameObject()->AddChild(pGO);
}

void SpriteList::AddItem(SpriteComponent* item) const
{
	assert(item);
	const auto pGO = new dae::GameObject();
	pGO->AddComponent(item);
	GetGameObject()->AddChild(pGO);
}

void SpriteList::RemoveItem(int amount) const
{
	assert(amount <= GetGameObject()->GetChildCount());
	for (size_t i = 0; i < amount; ++i)
	{
		GetGameObject()->RemoveChild(GetGameObject()->GetChildCount() - 1);
	}
}

void SpriteList::RemoveItem(const SpriteComponent* item) const
{
	GetGameObject()->RemoveChild(item->GetGameObject());
}
