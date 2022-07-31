#pragma once
#include "pch.h"
#include <SubjectComponent.h>

#include "Bullet.h"

class TankComponent final: public SubjectComponent
{
public:
	TankComponent(dae::GameObject* pGO, const SDL_Rect& mapRect, int value) :SubjectComponent(pGO), m_MapRect(mapRect), m_Value(value) { MoveToRandomLocation(); }
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
	int GetValue()const { return m_Value; }

	void MoveToRandomLocation() const;

private:
	float m_TurretAngle{};
	float m_RotateSpeed{ 40 };

	SDL_Rect m_MapRect;

	int m_Value;
};

