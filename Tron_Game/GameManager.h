#pragma once
#include <Component.h>

#include "Observer.h"

class GameManager final :  public Component, public Observer
{
public:
<<<<<<< HEAD
	GameManager(dae::GameObject* pGO):Component(pGO),Observer() {}
=======
	enum class Level
	{
		Level01,
		Level02,
		Level03,
		DEFAULT
	};
	GameManager(dae::GameObject* pGO) :Component(pGO), Observer() {  }
>>>>>>> parent of 356ae7f (add scoreboard scene, skip buttons and levels switcher)
	~GameManager() override = default;

	GameManager(const GameManager& other) = delete;
	GameManager(GameManager&& other) noexcept = delete;
	GameManager& operator=(const GameManager& other) = delete;
	GameManager& operator=(GameManager&& other) noexcept = delete;
<<<<<<< HEAD
=======

	void Notify(const dae::GameObject& pObject, EEvent event) override;

	void Update() override{}
	void FixedUpdate() override{}
	void Render() const override{}
private:
	void SwitchLevel();

	Level m_CurLevel{ Level::DEFAULT };
>>>>>>> parent of 356ae7f (add scoreboard scene, skip buttons and levels switcher)
};

