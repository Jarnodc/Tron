#pragma once
#include <Component.h>

#include "Observer.h"

class GameManager final : public Component, public Observer
{
public:
	enum class Level
	{
		Level01,
		Level02,
		Level03,
	};
	GameManager(dae::GameObject* pGO):Component(pGO), Observer() {  }
	~GameManager() override = default;

	GameManager(const GameManager& other) = delete;
	GameManager(GameManager&& other) noexcept = delete;
	GameManager& operator=(const GameManager& other) = delete;
	GameManager& operator=(GameManager&& other) noexcept = delete;

	void Notify(const dae::GameObject& pObject, EEvent event) override;

	void Update() override{}
	void FixedUpdate() override{}
	void Render() const override{}
private:
	void SwitchLevel();

	Level m_CurLevel{ Level::Level01 };
};

