#include "pch.h"

#include "Controller.h"
#include "EEvent.h"
#include "GameManager.h"
#include "Minigin.h"
#include "JsonReader.h"
#include "Prefab.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ScoreBoard.h"
#include "ServiceLocator.h"
#include "SkipLevelButton.h"
#include "TankComponent.h"

void Level01(dae::Scene& scene)
{
	JsonReader::GetInstance().ReadFile(scene, "Level01.json");
	scene.Add(BlueTankPrefab(scene));
}
void Level02(dae::Scene& scene)
{
	JsonReader::GetInstance().ReadFile(scene, "Level02.json");
	scene.Add(BlueTankPrefab(scene));
	scene.Add(BlueTankPrefab(scene));
}
void Level03(dae::Scene& scene)
{
	JsonReader::GetInstance().ReadFile(scene, "Level03.json");
	scene.Add(BlueTankPrefab(scene));
	scene.Add(BlueTankPrefab(scene));
	scene.Add(BlueTankPrefab(scene));
}
void DEFAULT(dae::Scene& scene)
{
	const auto gameManager{ std::make_shared<dae::GameObject>("GameManager") };
	gameManager->AddComponent<GameManager>();
	scene.AddDefault(gameManager);

	const auto player{ RedTankPrefab(scene) };
	scene.AddDefault(player);
	
	const auto skipButton{ std::make_shared<dae::GameObject>() };
	skipButton->AddComponent(new SkipLevelButton(skipButton.get(), { 0,0,600,200 }, { 500,300,100,30 }, "ButtonSprite.png"));
	scene.AddDefault(skipButton);
}

void ScoreBoardScene(dae::Scene& scene)
{
	const auto scoreDisplay{ std::make_shared<dae::GameObject>() };
	scoreDisplay->AddComponent<ScoreBoard>();
	scene.AddDefault(scoreDisplay);
}
int main(int, char* []) {

	// -- Init -- //t
	dae::Minigin engine;
	engine.Initialize();
	ServiceLocator::RegisterSoundSystem(new SDLSoundSystem());

	// -- Load Game -- //z
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(DEFAULT, "DEFAULT");
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(Level01, "Level01");
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(Level02, "Level02");
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(Level03, "Level03");
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(ScoreBoardScene, "ScoreBoard");
	dae::SceneManager::GetInstance().LoadScene("DEFAULT");
	dae::SceneManager::GetInstance().LoadScene("Level01");
	//dae::SceneManager::GetInstance().LoadScene("ScoreBoard");

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
