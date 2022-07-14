#pragma once
#include "SubjectComponent.h"

class HealthComponent final:  public SubjectComponent
{
public:
	HealthComponent(dae::GameObject* pGO, int health):SubjectComponent(pGO), m_Health(health) {}
	~HealthComponent() override = default;

	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) noexcept = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) noexcept = delete;

	void Update() override{}
	void FixedUpdate() override{}
	void Render() const override{}

	void Hit(int damage = 1);
private:
	int m_Health;
};

