#include "pch.h"

#include "Minigin.h"
#include "JsonReader.h"
#include "Prefab.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"

void Scene01(dae::Scene& scene)
{
	JsonReader::GetInstance().ReadFile(scene, "Level01.json");
	const auto ai{ BlueTankPrefab(scene) };
	scene.Add(ai);
	const auto player{ RedTankPrefab(scene) };
	scene.Add(player);
}
int main(int, char* []) {

	// -- Init -- //t
	dae::Minigin engine;
	engine.Initialize();
	ServiceLocator::RegisterSoundSystem(new SDLSoundSystem());

	// -- Load Game -- //z
	dae::SceneManager::GetInstance().SetSpawnLevelFunc(Scene01, "Scene01");
	dae::SceneManager::GetInstance().LoadScene("Scene01");

	// -- Run -- //
	engine.Run();

	// -- Close -- // 
	ServiceLocator::ReleaseSoundSystem();
	return 0;
}
