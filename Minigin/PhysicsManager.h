#pragma once
#include "BoxCollider.h"
#include "Singleton.h"

struct Ray
{
	glm::vec3 HitPoint {0,0,0};
	glm::vec3 Direction{0,0,0};
	float Distance{ 0 };
	dae::GameObject* HitObject{ nullptr };

	Ray() = default;
	Ray(const glm::vec3& direction,int maxDistance)
		:Direction(direction), MaxDistance(maxDistance){}
	int MaxDistance = INT_MAX;
};

class PhysicsManager final: public dae::Singleton<PhysicsManager>
{
public:
	~PhysicsManager() override = default;

	PhysicsManager(const PhysicsManager& other) = delete;
	PhysicsManager(PhysicsManager&& other) noexcept = delete;
	PhysicsManager& operator=(const PhysicsManager& other) = delete;
	PhysicsManager& operator=(PhysicsManager&& other) noexcept = delete;

	void AddBoxCollider(BoxCollider* bc) { m_Colliders.emplace_back(bc); }
	void RemoveBoxCollider(const BoxCollider* bc) {
		for (size_t i = 0; i < m_Colliders.size(); ++i)
		{
			if (m_Colliders.at(i) == bc)
			{
				m_Colliders.erase(m_Colliders.begin() + i);
				return;
			}
		}
	}

	std::vector<BoxCollider*> GetColliders(std::string tag) const;
	std::vector<BoxCollider*> GetOverlappers(BoxCollider* bc, bool includeBorders = false) const;
	std::vector<BoxCollider*> GetOverlappers(BoxCollider* bc, bool includeBorders, std::string tag) const;
	std::vector<BoxCollider*> GetOverlappers(BoxCollider* bc, std::string tag) const;

	bool IsOverlapping(BoxCollider* bc, bool includeBorders = false) const;
	bool IsOverlapping(BoxCollider* bc, bool includeBorders, std::string tag) const;
	bool IsOverlapping(BoxCollider* bc, std::string tag) const;

	Ray RayCast(const glm::vec3& startPosition, const glm::vec3& direction,dae::GameObject* pGO = nullptr, const int maxDistance = INT_MAX);
private:
	friend class Singleton<PhysicsManager>;
	PhysicsManager() = default;
	std::vector<BoxCollider*> m_Colliders{};

	bool IsPointInRect(BoxCollider* pBC, const std::vector<BoxCollider*>& cols, const  glm::vec3& point) const;
};

