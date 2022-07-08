#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <stdio.h>
#include <iostream>
#include <sstream> 
#include <memory> 
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <SDL.h>
#pragma warning (pop)

#include "Minigin.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "SpriteComponent.h"

void test(dae::Scene& scene)
{
	const auto test = std::make_shared<dae::GameObject>();
	test->AddComponent(new SpriteComponent(test.get(), SpriteComponent::SourcePart( "test.png", 5, 2), { 100,100 },.1f));
	scene.Add(test);
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
