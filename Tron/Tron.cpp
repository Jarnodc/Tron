#include "Minigin.h"
#include "ServiceLocator.h"

int main(int, char* []) {

	// -- Init --
	dae::Minigin engine;
	engine.Initialize();
	ServiceLocator::RegisterSoundSystem(new SDLSoundSystem());

	// -- Load Game --


	// -- Run -- 
	engine.Run();

	// -- Close --
	ServiceLocator::ReleaseSoundSystem();
	return 0;
}
