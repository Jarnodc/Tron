#pragma once
#include "pch.h"
#include <SubjectComponent.h>

#include "Bullet.h"

class TankComponent final: public SubjectComponent
{
public:
	TankComponent(dae::GameObject* pGO, const SDL_Rect& mapRect) :SubjectComponent(pGO), m_MapRect(mapRect) { MoveToRandomLocation(); }
	~TankComponent() override = default;

	TankComponent(const TankComponent& other) = delete;
	TankComponent(TankComponent&& other) noexcept = delete;
	TankComponent& operator=(const TankComponent& other) = delete;
	TankComponent& operator=(TankComponent&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override{}
	void Render() const override{}

	void Hit() const;
	void Attack() const;
	void Rotate(bool clockWise = true);

	float GetTurretAngle() const { return m_TurretAngle; }

	void MoveToRandomLocation() const;
private:
	float m_TurretAngle{};
	float m_RotateSpeed{ 10 };

	SDL_Rect m_MapRect;
};

