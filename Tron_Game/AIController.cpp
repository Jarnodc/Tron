#include "pch.h"
#include "AIController.h"

#include "GameObject.h"
#include "EEvent.h"

void AIController::Update()
{
}

void AIController::FixedUpdate()
{
}

void AIController::Notify(const dae::GameObject& , EEvent event)
{

	if (EEvent::Die != event)
		return;

	//GetSubject()->Notify(*GetGameObject(), EEvent::Lose);
	// else
	// Respawn
}

void AIController::CalcAttack()
{
}

void AIController::CalcPath()
{
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
