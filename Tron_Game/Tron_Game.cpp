#include "pch.h"

#include "Minigin.h"
#include "JsonReader.h"
#include "Prefab.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"

void test(dae::Scene& scene)
{
	//const auto test = std::make_shared<dae::GameObject>();
	//test->MovePosition(10, 10);
	//test->AddComponent(new HorizontalSpriteList(test.get(), new SpriteComponent(test.get(), SpriteComponent::SourcePart("test.png", 5, 2), { 10,0,30,30 }, .1f), 3));
	//scene.Add(test);
	const auto player{ BlueTankPrefab(scene) };
	player.get()->MovePosition(17, 17);
	scene.Add(player);
	JsonReader::GetInstance().ReadFile(scene, "Level01.json");
}
int main(int, char* []) {

	// -- Init -- //
	dae::Minigin engine;
	engine.Initialize();
	ServiceLocator::RegisterSoundSystem(new SDLSoundSystem());

	// -- Load Game -- //
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(test, "test");
	dae::SceneManager::GetInstance().LoadScene("test");

	// -- Run -- //
	engine.Run();

	// -- Close -- // 
	ServiceLocator::ReleaseSoundSystem();
	return 0;
}
