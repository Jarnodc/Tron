#include "pch.h"
#include "Bullet.h"

#include "BoxCollider.h"
#include "Controller.h"
#include "EEvent.h"
#include "GameObject.h"
#include "TankComponent.h"
#include "PhysicsManager.h"
#include "RigidBody.h"
#include "ServiceLocator.h"

void Bullet::Update()
{
	GetGameObject()->GetComponent<RigidBody>()->Move(m_Direction);
	if(const auto bc = GetGameObject()->GetComponent<BoxCollider>())
	{
		const auto overlappers = PhysicsManager::GetInstance().GetOverlappers(bc);
		for (auto& overlapper : overlappers)
		{
			const auto tag{ overlapper->GetGameObject()->GetTag() };
			if((tag == "Wall" || tag == "Teleporter") && m_pPrevBoxCollider != overlapper)
			{
				// -- Sound Effect -- //
				ServiceLocator::GetSoundSystem().AddToQueue("Bounce.wav");


				m_pPrevBoxCollider = overlapper;
				++m_AmountBounces;
				ChangeDirection(overlapper);
				GetGameObject()->GetComponent<RigidBody>()->Move(m_Direction);
				if (m_AmountBounces >= m_MaxBounces)
				{
					m_IsDead = true;
				}
				return;
			}
			if(overlapper->GetGameObject() != m_pParent)
			{
				if(tag == "Player")
				{
					overlapper->GetGameObject()->GetComponent<TankComponent>()->Hit();
					m_IsDead = true;
				}
				else if (tag == "AI")
				{
					overlapper->GetGameObject()->GetComponent<TankComponent>()->Hit();
					m_IsDead = true;
					if (m_pParent->GetTag() == "Player")
						m_pParent->GetComponent<Controller>()->GetSubject()->Notify(*overlapper->GetGameObject(), EEvent::Kill);
				}
				return;
			}
		}
	}
}

void Bullet::ChangeDirection(const BoxCollider* overlapper)
{
	switch (overlapper->HitSide(GetGameObject()->GetComponent<BoxCollider>()))
	{
	case Side::Left:
		m_Direction.x *= -1;
		//std::cout << "Left" << std::endl;
		break;
	case Side::Right:
		m_Direction.x *= -1;
		//std::cout << "Right" << std::endl;
		break;
	case Side::Bottom:
		m_Direction.y *= -1;
		//std::cout << "Bottom" << std::endl;
		break;
	case Side::Top:
		m_Direction.y *= -1;
		//std::cout << "Top" << std::endl;
		break;
	}
}

