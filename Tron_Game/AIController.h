#pragma once
#include <algorithm>

#include "Controller.h"
#include "Renderer.h"

class AIController final: public Controller
{
public:
	AIController(dae::GameObject* pGO):Controller(pGO){}
	~AIController() override = default;

	AIController(const AIController& other) = delete;
	AIController(AIController&& other) noexcept = delete;
	AIController& operator=(const AIController& other) = delete;
	AIController& operator=(AIController&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override;
	void Render() const override {}

	void Notify(const dae::GameObject& pObject, EEvent event) override;

	void SetTargets(const std::vector<dae::GameObject*>& pTargets) { m_pTargets = pTargets; }
	void AddTarget(dae::GameObject* pTarget) { m_pTargets.emplace_back(pTarget); }
	void RemoveTarget(dae::GameObject* pTarget) { m_pTargets.erase(std::ranges::remove(m_pTargets, pTarget).begin()); }
private:
	void CalcAttack();
	void CalcPath();
	void CalcTarget();

	std::vector<dae::GameObject*> m_pTargets{};
	dae::GameObject* m_pTarget{ nullptr };

	const float m_FireRate{ .3f };

	float m_CurRate{ m_FireRate };

};

	