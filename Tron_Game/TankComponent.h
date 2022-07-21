#pragma once
#include "pch.h"
#include <SubjectComponent.h>

#include "Bullet.h"

class TankComponent final: public SubjectComponent
{
public:
	TankComponent(dae::GameObject* pGO):SubjectComponent(pGO) {}
	~TankComponent() override = default;

	TankComponent(const TankComponent& other) = delete;
	TankComponent(TankComponent&& other) noexcept = delete;
	TankComponent& operator=(const TankComponent& other) = delete;
	TankComponent& operator=(TankComponent&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override{}
	void Render() const override{}

	void Hit();
	void Attack();
	void Rotate(bool clockWise = true);
private:
	std::vector<Bullet> m_Bullets{  };
	float m_TurretAngle{};
	float m_RotateSpeed{ 2 };
};

