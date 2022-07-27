#include "pch.h"

#include "Minigin.h"
#include "JsonReader.h"
#include "Prefab.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"

void Scene01(dae::Scene& scene)
{
	const auto ai{ BlueTankPrefab(scene) };
	ai->MovePosition(100, 17);
	scene.Add(ai);
	const auto player{ RedTankPrefab(scene) };
	player->MovePosition(17, 17);
	scene.Add(player);
	JsonReader::GetInstance().ReadFile(scene, "Level01.json");
}
int main(int, char* []) {

	// -- Init -- //t
	dae::Minigin engine;
	engine.Initialize();
	ServiceLocator::RegisterSoundSystem(new SDLSoundSystem());

	// -- Load Game -- //
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(Scene01, "Scene01");
	dae::SceneManager::GetInstance().LoadScene("Scene01");

	// -- Run -- //
	engine.Run();

	// -- Close -- // 
	ServiceLocator::ReleaseSoundSystem();
	return 0;
}
