#include "pch.h"
#include "Controller.h"

#include "EEvent.h"
#include "InputManager.h"

void Controller::Notify(const dae::GameObject& , EEvent event)
{
	if (EEvent::Die != event)
		return;
	--m_Lives;


	if(m_Lives <= 0)
		GetSubject()->Notify(*GetGameObject(), EEvent::Lose);
	// else
	// Respawn
}
