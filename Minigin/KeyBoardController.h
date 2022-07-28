#pragma once
#include "PlayerController.h"
class KeyBoardController final: public PlayerController
{
	class KeyBoardControllerImpl;
	KeyBoardControllerImpl* m_pImpl = nullptr;
public:
	explicit KeyBoardController(int controllerIdx);
	~KeyBoardController() override;

	void Update() const override;

	bool IsDown(SDL_Scancode scancode)const;
	bool IsUp(SDL_Scancode scancode)const;
	bool IsPressed(SDL_Scancode scancode)const;
};

