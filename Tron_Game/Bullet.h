#pragma once
#include "pch.h"
#include <Component.h>
class Bullet final : public Component
{
public:
	Bullet(dae::GameObject* pGO, dae::GameObject* parent, const glm::vec3& direction) :Component(pGO), m_Direction(direction), m_pParent(parent) {}
	~Bullet() override = default;

	Bullet(const Bullet& other) = delete;
	Bullet(Bullet&& other) noexcept = delete;
	Bullet& operator=(const Bullet& other) = delete;
	Bullet& operator=(Bullet&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override {}
	void Render() const override {}

	bool IsDead() { return m_IsDead; }
	
private:
	glm::vec3 m_Direction;
	int m_AmountBounces{ 0 };
	const int m_MaxBounces{ 5 };
	dae::GameObject* m_pParent;
	bool m_IsDead{ false };
};

