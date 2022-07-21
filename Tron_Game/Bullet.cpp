#include "pch.h"
#include "Bullet.h"

#include "BoxCollider.h"
#include "GameObject.h"
#include "TankComponent.h"
#include "PhysicsManager.h"
#include "RigidBody.h"
#include "Scene.h"
#include "SceneManager.h"

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
					dae::SceneManager::GetInstance().GetScene().Remove(std::shared_ptr<dae::GameObject>(GetGameObject()));
				}
				return;
			}
			if(tag == "Tank" && overlapper->GetGameObject() != m_pParent)
			{
				overlapper->GetGameObject()->GetComponent<TankComponent>()->Hit();
				dae::SceneManager::GetInstance().GetScene().Remove(std::shared_ptr<dae::GameObject>(GetGameObject()));
				return;
			}
		}
	}
}
