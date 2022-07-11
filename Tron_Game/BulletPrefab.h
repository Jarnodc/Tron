#pragma once
#include <GameObject.h>
class BulletPrefab final: public dae::GameObject
{
public:
	BulletPrefab(const glm::vec3& direction, Tag tag = "Null");
	~BulletPrefab() override = default;

	BulletPrefab(const BulletPrefab& other) = delete;
	BulletPrefab(BulletPrefab&& other) noexcept = delete;
	BulletPrefab& operator=(const BulletPrefab& other) = delete;
	BulletPrefab& operator=(BulletPrefab&& other) noexcept = delete;

private:
};

