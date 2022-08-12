#include "pch.h"
#include "GameManager.h"

#include "AIController.h"
#include "BulletManager.h"
#include "EEvent.h"
#include "Scene.h"
#include "SceneManager.h"

void GameManager::Notify(const dae::GameObject&, EEvent event)
{
	switch (event)
	{
	case EEvent::Lose:
		dae::SceneManager::GetInstance().LoadScene("ScoreBoard");
		break;
	case EEvent::SwitchLevel:
		SwitchLevel();
		break;
	}
}

void GameManager::SwitchLevel()
{
	const auto bulletManagers{ dae::SceneManager::GetInstance().GetScene().GetGameObject<BulletManager>() };
	for (const auto& bulletmanager : bulletManagers)
	{
		bulletmanager->GetComponent<BulletManager>()->ClearBullets();
	}

	switch (m_CurLevel)
	{
	case Level::Level01:
		dae::SceneManager::GetInstance().LoadScene("Level02");
		m_CurLevel = Level::Level02;
		break;
	case Level::Level02:
		dae::SceneManager::GetInstance().LoadScene("Level03");
		m_CurLevel = Level::Level03;
		break;
	case Level::Level03:
		dae::SceneManager::GetInstance().LoadScene("Level01");
		m_CurLevel = Level::Level01;
		break;
	}
	const auto& scene{ dae::SceneManager::GetInstance().GetScene() };
	const auto AIControllers = scene.GetGameObject<AIController>();
	const auto controllers = scene.GetGameObject<Controller>("Player");
	for (const auto& controller : controllers)
	{
		controller->GetComponent<TankComponent>()->MoveToRandomLocation();
	}
	for (const auto& controller : AIControllers)
	{
		controller->GetComponent<AIController>()->SetTargets(controllers);
	}
}
