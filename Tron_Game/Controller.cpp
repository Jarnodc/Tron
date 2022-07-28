#include "pch.h"
#include "Controller.h"

#include "EEvent.h"
#include "HorizontalSpriteList.h"
#include "InputManager.h"

void Controller::Notify(const dae::GameObject& gameObject, EEvent event)
{
	if (EEvent::Die != event || m_Lives <= 0)
		return;
	--m_Lives;
	gameObject.GetComponent<HorizontalSpriteList>()->RemoveItem(1);

	if (m_Lives <= 0)
	{
		GetSubject()->Notify(*GetGameObject(), EEvent::Lose);
	}
	// else
	// Respawn
}
