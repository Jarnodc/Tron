#include "pch.h"

#include "Controller.h"
#include "EEvent.h"
#include "GameManager.h"
#include "InputManager.h"
#include "Minigin.h"
#include "JsonReader.h"
#include "LoadGameMode.h"
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
	Level01(scene);
}
void COOPDEFAULT(dae::Scene& scene)
{
	const auto gameManager{ std::make_shared<dae::GameObject>("GameManager") };
	gameManager->AddComponent<GameManager>();
	scene.AddDefault(gameManager);

	const auto player{ RedTankPrefab(scene) };
	scene.AddDefault(player);

	const auto skipButton{ std::make_shared<dae::GameObject>() };
	skipButton->AddComponent(new SkipLevelButton(skipButton.get(), { 0,0,600,200 }, { 500,300,100,30 }, "ButtonSprite.png"));
	scene.AddDefault(skipButton);

	const auto player2{ GreenTankPrefab(scene) };
	scene.AddDefault(player2);
	Level01(scene);
}
void VERSUSDEFAULT(dae::Scene& scene)
{
	const auto gameManager{ std::make_shared<dae::GameObject>("GameManager") };
	gameManager->AddComponent<GameManager>();
	scene.AddDefault(gameManager);

	const auto player{ RedTankPrefab(scene) };
	scene.AddDefault(player);

	const auto skipButton{ std::make_shared<dae::GameObject>() };
	skipButton->AddComponent(new SkipLevelButton(skipButton.get(), { 0,0,600,200 }, { 500,300,100,30 }, "ButtonSprite.png"));
	scene.AddDefault(skipButton);

	const auto player2{ BluePlayerTankPrefab(scene) };
	scene.AddDefault(player2);
	Level01(scene);
}

void MainScene(dae::Scene& scene)
{
	const auto defaultButton{ std::make_shared<dae::GameObject>() };
	defaultButton->AddComponent(new LoadGameMode(defaultButton.get(), { 0,0,600,200 }, { 250,100,150,50 }, "ButtonSprite.png","DEFAULT"));
	scene.Add(defaultButton);

	const auto coopButton{ std::make_shared<dae::GameObject>() };
	coopButton->AddComponent(new LoadGameMode(coopButton.get(), { 0,0,600,200 }, { 250,200,150,50 }, "ButtonSprite.png","COOP"));
	scene.Add(coopButton);

	const auto versusButton{ std::make_shared<dae::GameObject>() };
	versusButton->AddComponent(new LoadGameMode(versusButton.get(), { 0,0,600,200 }, { 250,300,150,50 }, "ButtonSprite.png", "VERSUS"));
	scene.Add(versusButton);
}

void ScoreBoardScene(dae::Scene& scene)
{
	dae::InputManager::GetInstance().ResetManager();
	const auto scoreDisplay{ std::make_shared<dae::GameObject>() };
	scoreDisplay->AddComponent<ScoreBoard>();
	scene.Add(scoreDisplay);
}

int main(int, char* []) {

	// -- Init -- //t
	dae::Minigin engine;
	engine.Initialize();
	ServiceLocator::RegisterSoundSystem(new SDLSoundSystem());

	// -- Load Game -- //z
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(MainScene, "MainScene");
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(DEFAULT, "DEFAULT");
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(COOPDEFAULT, "COOP");
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(VERSUSDEFAULT, "VERSUS");
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(Level01, "Level01");
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(Level02, "Level02");
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(Level03, "Level03");
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(ScoreBoardScene, "ScoreBoard",false);
	dae::SceneManager::GetInstance().LoadScene("MainScene");

	const auto Controllers = dae::SceneManager::GetInstance().GetScene().GetGameObject<Controller>();
	for (const auto& controller : Controllers)
	{
		controller->GetComponent<TankComponent>()->MoveToRandomLocation();
	}
	ServiceLocator::GetSoundSystem().AddToQueue("Background.mp3", -1, 10);

	// -- Run -- //
	engine.Run();

	// -- Close -- // 
	ServiceLocator::ReleaseSoundSystem();
	return 0;
}
