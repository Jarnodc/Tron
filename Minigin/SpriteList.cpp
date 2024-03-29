#include "MiniginPCH.h"
#include "SpriteList.h"

#include "GameObject.h"
#include "SceneManager.h"

void SpriteList::RemoveItem(int amount) const
{
	assert(static_cast<size_t>(amount) <= GetGameObject()->GetChildCount());

	for (int i = 0; i < amount; ++i)
	{
		GetGameObject()->RemoveChild(static_cast<int>(GetGameObject()->GetChildCount() - 1));
	}
}

void SpriteList::RemoveItem(const SpriteComponent* item) const
{
	GetGameObject()->RemoveChild(item->GetGameObject());
}

void SpriteList::Update()
{
}

void SpriteList::FixedUpdate()
{
}

void SpriteList::Render() const
{
}

