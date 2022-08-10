#include "pch.h"
#include "MoveComponent.h"

#include "GameObject.h"
#include "PhysicsManager.h"
#include "RigidBody.h"
#include "TimerInfo.h"
#include <SpriteComponent.h>



void MoveComponent::Move(glm::vec3 moveVec) const
{
	const auto rigidBody{ GetGameObject()->GetComponent<RigidBody>() };
	const auto velocity = moveVec * dae::TimerInfo::GetInstance().deltaTime * rigidBody->GetSpeed();

	if (velocity.x > 0 && !CanMoveTo(EDirection::Right))//CanMoveLeft
	{
		moveVec.x = 0;
	}
	else if (velocity.x < 0 && !CanMoveTo(EDirection::Left))//CanMoveRight
	{
		moveVec.x = 0;
	}
	if (velocity.y > 0 && !CanMoveTo(EDirection::Down))//CanMoveDown
	{
		moveVec.y = 0;
	}
	else if (velocity.y < 0 && !CanMoveTo(EDirection::Up))//CanMoveUp
	{
		moveVec.y = 0;
	}
	if (moveVec.x == 0 && moveVec.y == 0)
		return;
	rigidBody->Move(moveVec);


	float angle{};
	if (moveVec.x != 0)// 90 or 270 degrees
	{
		if (moveVec.x > 0)
			angle = 90;
		else
			angle = 90;
	}
	else if (moveVec.y > 0)
			angle = 180;
	GetGameObject()->GetComponent<SpriteComponent>()->SetRotation({ 12.5f,12.5f }, angle);
}

bool MoveComponent::CanMoveTo(EDirection dir) const
{
	const auto rigidBody{ GetGameObject()->GetComponent<RigidBody>() };
	auto velocity = dae::TimerInfo::GetInstance().deltaTime * rigidBody->GetSpeed();
	const auto boxCollider = GetGameObject()->GetComponent<BoxCollider>();
	auto rect = boxCollider->GetBoxCollider();
	const auto left{ rect.x }, bottom{ rect.y };
	switch (dir)
	{
	case EDirection::Up:
	{
		velocity *= glm::vec3{ 0, -1, 0 };
		rect.y += static_cast<int>(velocity.y) - 1;
		boxCollider->SetBoxCollider(rect);
		if (PhysicsManager::GetInstance().IsOverlapping(boxCollider))
		{
			const auto overlappers = PhysicsManager::GetInstance().GetOverlappers(boxCollider);
			bool overlappedNonBullet{ false };
			for (const auto& overlapper : overlappers)
			{
				if (overlapper->GetGameObject()->GetTag() != "Bullet" && overlapper->GetGameObject()->GetTag() != "Teleporter")
				{
					overlappedNonBullet = true;
				}
			}
			rect.y = bottom;
			boxCollider->SetBoxCollider(rect);
			return !overlappedNonBullet;
		}
		rect.y = bottom;
		boxCollider->SetBoxCollider(rect);
	}
	break;
	case EDirection::Down:
	{
		velocity *= glm::vec3{ 0, 1, 0 };
		rect.y += static_cast<int>(velocity.y) + 1;
		boxCollider->SetBoxCollider(rect);
		if (PhysicsManager::GetInstance().IsOverlapping(boxCollider))
		{
			const auto overlappers = PhysicsManager::GetInstance().GetOverlappers(boxCollider);
			bool overlappedNonBullet{ false };
			for (const auto& overlapper : overlappers)
			{
				if (overlapper->GetGameObject()->GetTag() != "Bullet" && overlapper->GetGameObject()->GetTag() != "Teleporter")
				{
					overlappedNonBullet = true;
				}
			}
			rect.y = bottom;
			boxCollider->SetBoxCollider(rect);
			return !overlappedNonBullet;
		}
		rect.y = bottom;
		boxCollider->SetBoxCollider(rect);
	}
	break;
	case EDirection::Left:
	{
		velocity *= glm::vec3{ -1,0, 0 };
		rect.x += static_cast<int>(velocity.x) - 1;
		boxCollider->SetBoxCollider(rect);

		if (PhysicsManager::GetInstance().IsOverlapping(boxCollider))
		{
			const auto overlappers = PhysicsManager::GetInstance().GetOverlappers(boxCollider);
			bool overlappedNonBullet{ false };
			for (const auto& overlapper : overlappers)
			{
				if (overlapper->GetGameObject()->GetTag() != "Bullet" && overlapper->GetGameObject()->GetTag() != "Teleporter")
				{
					overlappedNonBullet = true;
				}
			}
			rect.x = left;
			boxCollider->SetBoxCollider(rect);
			return !overlappedNonBullet;
		}
		rect.x = left;
		boxCollider->SetBoxCollider(rect);
	}
	break;
	case EDirection::Right:
	{
		velocity *= glm::vec3{ 1, 0,0 };
		rect.x += static_cast<int>(velocity.x) + 1;
		boxCollider->SetBoxCollider(rect);
		if (PhysicsManager::GetInstance().IsOverlapping(boxCollider))
		{
			const auto overlappers = PhysicsManager::GetInstance().GetOverlappers(boxCollider);
			bool overlappedNonBullet{ false };
			for (const auto& overlapper : overlappers)
			{
				if (overlapper->GetGameObject()->GetTag() != "Bullet" && overlapper->GetGameObject()->GetTag() != "Teleporter")
				{
					overlappedNonBullet = true;
				}
			}
			rect.x = left;
			boxCollider->SetBoxCollider(rect);
			return !overlappedNonBullet;
		}
		rect.x = left;
		boxCollider->SetBoxCollider(rect);
	}
	break;
	case EDirection::Horizontal:
		return CanMoveTo(EDirection::Left) || CanMoveTo(EDirection::Right);
		break;
	case EDirection::Vertical:
		return CanMoveTo(EDirection::Down) || CanMoveTo(EDirection::Up);
		break;
	}
	return true;
}
