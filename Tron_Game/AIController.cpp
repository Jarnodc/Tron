	#include "pch.h"
#include "AIController.h"

#include "GameObject.h"
#include "EEvent.h"
#include "MoveComponent.h"
#include "PhysicsManager.h"
#include "TankComponent.h"
#include "TimerInfo.h"

void AIController::Update()
{
	if (m_pTargets.empty())
		return;

	CalcTarget();
	CalcAttack();
	CalcPath();
}

void AIController::FixedUpdate()
{		
}

void AIController::Notify(const dae::GameObject& , EEvent event)
{
	if (EEvent::Die != event)
		return;
	
	// else
	// Respawn
}

void AIController::CalcAttack()
{
	const auto tankComp{ GetGameObject()->GetComponent<TankComponent>() };


	const auto vec{ m_pTarget->GetLocalPosition() - GetGameObject()->GetLocalPosition() };
	const auto angleD{ Angle(vec) - tankComp->GetTurretAngle()};
	tankComp->Rotate(angleD > 0);

	if (m_CurRate < m_FireRate)
		m_CurRate += dae::TimerInfo::GetInstance().deltaTime;
	else
	{
		const glm::vec3 dir{ cos(ToRadians(tankComp->GetTurretAngle())),sin(ToRadians(tankComp->GetTurretAngle())),0};
		const auto ray = PhysicsManager::GetInstance().RayCast(GetGameObject()->GetLocalPosition() + glm::vec3{8,8,0}, dir, GetGameObject());
		if (ray.HitObject->GetTag() == "Player")
		{
			tankComp->Attack();
			m_CurRate -= m_FireRate;
		}
	}
}

void AIController::CalcPath() const
{
	glm::vec3 moveVec{};
	glm::vec3 dir{ m_pTarget->GetLocalPosition() - GetGameObject()->GetLocalPosition() };
	if(dir.x < 0)
	{
		moveVec.x = -1;
	}
	else if (dir.x > 0)
	{
		moveVec.x = 1;
	}
	else if(dir.y != 0)
	{
		moveVec.x = -1;
	}
	if(dir.y < 0)
	{
		moveVec.y = -1;
	}
	else if (dir.y > 0)
	{
		moveVec.y = 1;
	}
	GetGameObject()->GetComponent<MoveComponent>()->Move(moveVec);
}

void AIController::CalcTarget()
{
	const auto pos{ GetGameObject()->GetLocalPosition() };
	m_pTarget = m_pTargets.front();
	assert(m_pTarget);
	int closestDist{ Magnitude<int>(m_pTarget->GetLocalPosition() - pos) };
	for (const auto& pTarget : m_pTargets)
	{
		if (pTarget == m_pTarget)
			continue;

		const int enemyDist{ Magnitude<int>(pTarget->GetLocalPosition() - pos) };
		if (enemyDist < closestDist)
		{
			m_pTarget = pTarget;
			closestDist = enemyDist;
		}
	}
}
