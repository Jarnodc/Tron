#include "pch.h"
#include "Bullet.h"

#include "BoxCollider.h"
#include "BulletManager.h"
#include "GameObject.h"
#include "TankComponent.h"
#include "PhysicsManager.h"
#include "RigidBody.h"

void Bullet::Update()
{
	GetGameObject()->GetComponent<RigidBody>()->Move(m_Direction);
	if(const auto bc = GetGameObject()->GetComponent<BoxCollider>())
	{
		const auto overlappers = PhysicsManager::GetInstance().GetOverlappers(bc);
		for (const auto& overlapper : overlappers)
		{
			const auto tag{ overlapper->GetGameObject()->GetTag() };
			if(tag == "Wall" || tag == "Teleporter")
			{
				++m_AmountBounces; // Change direction with Calc funtion
				if (m_AmountBounces >= m_MaxBounces)
				{
					m_IsDead = true;
				}
				return;
			}
			if(tag == "Tank" && overlapper->GetGameObject() != m_pParent)
			{
				overlapper->GetGameObject()->GetComponent<TankComponent>()->Hit();
				m_IsDead = true;
				return;
			}
		}
	}
}
