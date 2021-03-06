#include "pch.h"
#include "TankComponent.h"

#include "Prefab.h"
#include "Scene.h"
#include "TimerInfo.h"
#include "SceneManager.h"
#include "EEvent.h"

void TankComponent::Update()
{
}


void TankComponent::Attack()
{
	const float angle{ ToRadians(m_TurretAngle) };
	const auto bullet{ BulletPrefab(GetGameObject(),{cos(angle),sin(angle),0}) };
	const auto pos{ GetGameObject()->GetLocalPosition() };
	bullet.get()->SetPosition(pos.x, pos.y);
	dae::SceneManager::GetInstance().GetScene().Add(bullet);
}

void TankComponent::Rotate(bool clockWise)
{
	if(clockWise)
	{
		m_TurretAngle += m_RotateSpeed * dae::TimerInfo::GetInstance().deltaTime;
		if (m_TurretAngle >= 360)
			m_TurretAngle -= 360;
	}
	else
	{
		m_TurretAngle -= m_RotateSpeed * dae::TimerInfo::GetInstance().deltaTime;
		if (m_TurretAngle <= -360)
			m_TurretAngle += 360;
	}
}

void TankComponent::Hit()
{
	GetSubject()->Notify(*GetGameObject(), EEvent::Die);
}