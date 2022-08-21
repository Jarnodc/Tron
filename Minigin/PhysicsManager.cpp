#include "MiniginPCH.h"
#include "PhysicsManager.h"

#include "GameObject.h"

std::vector<BoxCollider*> PhysicsManager::GetColliders(std::string tag) const
{
	std::vector<BoxCollider*> bcs{};
	for (const auto boxCol : m_Colliders)
	{
		if (boxCol->GetGameObject()->GetTag() == tag)
			bcs.emplace_back(boxCol);
	}
	return bcs;
}

std::vector<BoxCollider*> PhysicsManager::GetOverlappers(BoxCollider* bc, bool includeBorders) const
{
	std::vector<BoxCollider*> bcs{};
	for (const auto boxCol : m_Colliders)
	{
		if (boxCol == bc)
			continue;
		if (boxCol->IsOverlapping(bc, includeBorders))
		{
			bcs.emplace_back(boxCol);
		}
	}
	return bcs;
}

std::vector<BoxCollider*> PhysicsManager::GetOverlappers(BoxCollider* bc, bool includeBorders, std::string tag) const
{
	std::vector<BoxCollider*> bcs{};
	for (const auto boxCol : m_Colliders)
	{
		if (boxCol == bc)
			continue;
		if (boxCol->IsOverlapping(bc, includeBorders,tag))
		{
			bcs.emplace_back(boxCol);
		}
	}
	return bcs;
}

std::vector<BoxCollider*> PhysicsManager::GetOverlappers(BoxCollider* bc, std::string tag) const
{
	std::vector<BoxCollider*> bcs{};
	for (const auto boxCol : m_Colliders)
	{
		if (boxCol == bc)
			continue;
		if (boxCol->IsOverlapping(bc, tag))
		{
			bcs.emplace_back(boxCol);
		}
	}
	return bcs;
}

bool PhysicsManager::IsOverlapping(BoxCollider* bc, bool includeBorders) const
{
	for (const auto boxCol : m_Colliders)
	{
		if (boxCol == bc)
			continue;
		if (boxCol->IsOverlapping(bc, includeBorders))
			return true;
	}
	return false;
}

bool PhysicsManager::IsOverlapping(BoxCollider* bc, bool includeBorders, std::string tag) const
{
	for (const auto boxCol : m_Colliders)
	{
		if (boxCol == bc)
			continue;
		if (boxCol->IsOverlapping(bc, includeBorders,tag))
			return true;
	}
	return false;
}

bool PhysicsManager::IsOverlapping(BoxCollider* bc, std::string tag) const
{
	for (const auto boxCol : m_Colliders)
	{
		if (boxCol == bc)
			continue;
		if (boxCol->IsOverlapping(bc, tag))
			return true;
	}
	return false;
}

Ray PhysicsManager::RayCast(const glm::vec3& startPosition, const glm::vec3& direction, dae::GameObject* pGO , const int maxDistance)
{
	const auto dir = glm::normalize(direction);

	Ray ray = Ray(dir, maxDistance);
	ray.HitPoint = startPosition;

	std::vector<BoxCollider*> colliders{};
	if (pGO)
	{
		std::vector objects{ pGO };
		size_t checkedCount{ 0 };

		while (objects.size() == checkedCount)
		{
			for (const auto& obj : objects)
			{
				if (obj->GetChildCount() != 0)
				{
					const auto children{ obj->GetChildren() };
					for (const auto& child : children)
					{
						objects.emplace_back(child);
					}
				}
				++checkedCount;
			}
		}
		for (const auto& obj : objects)
		{
			if (const auto bc = obj->GetComponent<BoxCollider>())
				colliders.emplace_back(bc);
		}
	}


	while(ray.MaxDistance >= glm::distance(ray.HitPoint, startPosition))
	{
		ray.HitPoint += dir ;
		for (const auto& col : m_Colliders)
		{
			if (IsPointInRect(col,colliders, ray.HitPoint))
			{
				ray.Distance = glm::distance(ray.HitPoint, startPosition);
				ray.HitObject = col->GetGameObject();
				
				return ray;
			}
		}
	}
	return ray;
}

bool PhysicsManager::IsPointInRect(BoxCollider* pBC, const std::vector<BoxCollider*>& cols, const  glm::vec3& point) const
{
	bool exist{ false };
	for (const auto& bc : cols)
	{
		if (pBC == bc)
		{
			exist = true;
			break;
		}
	}
	if (exist)
		return false;

	if (pBC->IsPointInRect(point))
		return true;

	return false;
}
