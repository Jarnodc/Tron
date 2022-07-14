#include "pch.h"
#include "TankComponent.h"

#include "Prefab.h"
#include "Scene.h"
#include "TimerInfo.h"
#include "SceneManager.h"


void TankComponent::Update()
{
}


void TankComponent::Attack()
{
	const float angle{ ToRadians(m_TurretAngle) };
	
	dae::SceneManager::GetInstance().GetScene().Add(BulletPrefab(GetGameObject(),{cos(angle),sin(angle),0}));
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
