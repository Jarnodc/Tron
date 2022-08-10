#include "pch.h"

#include "Controller.h"
#include "EEvent.h"
#include "GameManager.h"
#include "Minigin.h"
#include "JsonReader.h"
#include "Prefab.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "TankComponent.h"

void Level01(dae::Scene& scene)
{
	JsonReader::GetInstance().ReadFile(scene, "Level01.json");
	const auto ai{ BlueTankPrefab(scene) };
	scene.Add(ai);
}
void DEFAULT(dae::Scene& scene)
{
	const auto gameManager{ std::make_shared<dae::GameObject>("GameManager") };
	gameManager->AddComponent<GameManager>();
	scene.AddDefault(gameManager);

	const auto player{ RedTankPrefab(scene) };
	scene.AddDefault(player);

}
int main(int, char* []) {

	// -- Init -- //t
	dae::Minigin engine;
	engine.Initialize();
	ServiceLocator::RegisterSoundSystem(new SDLSoundSystem());

	// -- Load Game -- //z
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(DEFAULT, "DEFAULT");
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(Level01, "Level01");
	dae::SceneManager::GetInstance().LoadScene("DEFAULT");
	dae::SceneManager::GetInstance().LoadScene("Level01");

	const auto Controllers = dae::SceneManager::GetInstance().GetScene().GetGameObject<Controller>();
	for (const auto& controller : Controllers)
	{
		controller->GetComponent<TankComponent>()->MoveToRandomLocation();
	}

	// -- Run -- //
	engine.Run();

	// -- Close -- // 
	ServiceLocator::ReleaseSoundSystem();
	return 0;
}
