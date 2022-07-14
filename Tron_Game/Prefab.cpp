#include "pch.h"
#include "Prefab.h"

#include "BoxCollider.h"
#include "Bullet.h"
#include "SpriteComponent.h"


std::shared_ptr<dae::GameObject> BulletPrefab(dae::GameObject* parent, const glm::vec3& direction)
{
	const auto pGO{ std::make_shared<dae::GameObject>() };
	pGO->AddComponent(new Bullet(pGO.get(), parent, direction));
	pGO->AddComponent(new BoxCollider(pGO.get(), 10));
	pGO->AddComponent(new SpriteComponent(pGO.get(), SpriteComponent::SourcePart("TronSpriteSheet.png", 1, 1, { 32 * 6,0,10,10 }), { 0,0,10,10 }));

	return pGO;
}
