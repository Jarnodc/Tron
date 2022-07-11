#include "pch.h"
#include "BulletPrefab.h"

#include "BoxCollider.h"
#include "Bullet.h"
#include "SpriteComponent.h"

BulletPrefab::BulletPrefab(const glm::vec3& direction, Tag tag)
	:GameObject(tag)
{
	AddComponent(new Bullet(this, direction));
	AddComponent(new BoxCollider(this, 10));
	AddComponent(new SpriteComponent(this, SpriteComponent::SourcePart("TronSpriteSheet.png", 1, 1, { 32 * 6,0,10,10 }), { 0,0,10,10 }));
}
