#include "pch.h"
#include "TankComponent.h"

#include "BulletManager.h"
#include "Prefab.h"
#include "TimerInfo.h"
#include "EEvent.h"
#include "PhysicsManager.h"
#include "ServiceLocator.h"
#include "SpriteComponent.h"

void TankComponent::Update()
{
	BoxCollider* pBC{ GetGameObject()->GetComponent<BoxCollider>() };
	if (PhysicsManager::GetInstance().IsOverlapping(pBC, std::string("Teleporter")))
	{
		MoveToRandomLocation();
	}
}


void TankComponent::Attack()
{
	if (m_CurRate < m_FireRate)
	{
		m_CurRate += dae::TimerInfo::GetInstance().deltaTime;
		return;
	}
	m_CurRate -= m_FireRate;

	// -- Sound Effect -- //
	ServiceLocator::GetSoundSystem().AddToQueue("Shot.wav");


	const float angle{ ToRadians(m_TurretAngle) };
	const auto bullet{ BulletPrefab(GetGameObject(),{cos(angle),sin(angle),0}) };
	const auto pos{ GetGameObject()->GetLocalPosition() + glm::vec3{7,7,0} };
	bullet->SetPosition(pos.x, pos.y);
	GetGameObject()->GetComponent<BulletManager>()->AddBullet(bullet);

}

void TankComponent::Rotate(bool clockWise)
{
	if(clockWise)
	{
		m_TurretAngle += m_RotateSpeed * dae::TimerInfo::GetInstance().deltaTime;
	}
	else
	{
		m_TurretAngle -= m_RotateSpeed * dae::TimerInfo::GetInstance().deltaTime;
	}
	m_TurretAngle = AbsAngleDegrees(m_TurretAngle);
	if (GetGameObject()->GetChildCount() != 0)
	{
		const auto spriteComp{ GetGameObject()->GetChildAt(0)->GetComponent<SpriteComponent>() };
		spriteComp->SetRotation({ 10,25 }, m_TurretAngle);
	}
}

void TankComponent::MoveToRandomLocation() const
{
	BoxCollider* pBC{ GetGameObject()->GetComponent<BoxCollider>() };
	srand(static_cast<unsigned>(time(nullptr)));
	do
	{
		glm::vec2 randomPos{ rand() % m_MapRect.w,rand() % m_MapRect.h};
		randomPos += glm::vec2{m_MapRect.x, m_MapRect.y};
		Side side{ Side(rand() % 4) };
		switch (side)
		{
		case Side::Left:
			while(randomPos.x >= m_MapRect.x)
			{
				randomPos.x -= 1;
				GetGameObject()->SetPosition(randomPos.x, randomPos.y);
				if(!PhysicsManager::GetInstance().IsOverlapping(pBC))
				{
					return;
				}
			}
			break;
		case Side::Right:
			while (randomPos.x <= m_MapRect.w)
			{
				randomPos.x += 1;
				GetGameObject()->SetPosition(randomPos.x, randomPos.y);
				if (!PhysicsManager::GetInstance().IsOverlapping(pBC))
				{
					return;
				}
			}
			break;
		case Side::Bottom:
			while (randomPos.y <= m_MapRect.h)
			{
				randomPos.y += 1;
				GetGameObject()->SetPosition(randomPos.x, randomPos.y);
				if (!PhysicsManager::GetInstance().IsOverlapping(pBC))
				{
					return;
				}
			}
			break;
		case Side::Top:
			while (randomPos.y >= m_MapRect.y)
			{
				randomPos.y -= 1;
				GetGameObject()->SetPosition(randomPos.x, randomPos.y);
				if (!PhysicsManager::GetInstance().IsOverlapping(pBC))
				{
					return;
				}
			}
			break;
		}
	} while (PhysicsManager::GetInstance().IsOverlapping(pBC));
}

void TankComponent::Hit() const
{
	GetSubject()->Notify(*GetGameObject(), EEvent::LoseHealth);
}
