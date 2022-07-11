#pragma once
#include "pch.h"
#include <Component.h>
class Bullet final : public Component
{
public:
	Bullet(dae::GameObject* pGO, const glm::vec3& direction) :Component(pGO), m_Direction(direction) {}
	~Bullet() override = default;

	Bullet(const Bullet& other) = delete;
	Bullet(Bullet&& other) noexcept = delete;
	Bullet& operator=(const Bullet& other) = delete;
	Bullet& operator=(Bullet&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override {}
	void Render() const override {}
	
private:
	glm::vec3 m_Direction;
	int m_AmountBounces{ 0 };
};

