#pragma once

#include "Component.h"
#include "Renderer.h"

class Bullet;

class BulletManager final : public Component
{
public:
	BulletManager(dae::GameObject* pGO) :Component(pGO) {}
	~BulletManager() override = default;

	BulletManager(const BulletManager& other) = delete;
	BulletManager(BulletManager&& other) noexcept = delete;
	BulletManager& operator=(const BulletManager& other) = delete;
	BulletManager& operator=(BulletManager&& other) noexcept = delete;

	void AddBullet(const std::shared_ptr<dae::GameObject>& bullet);
	void RemoveBullet(const std::shared_ptr<dae::GameObject>& bullet);
	void ClearBullets();

	void Update() override;
	void FixedUpdate() override{}
	void Render() const override{}

private:

	std::vector<std::shared_ptr<dae::GameObject>> m_pBullets{};
};

