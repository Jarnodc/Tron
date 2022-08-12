#include "pch.h"
#include "Controller.h"

#include "EEvent.h"
#include "HorizontalSpriteList.h"
#include "InputManager.h"
#include "TankComponent.h"

void Controller::Notify(const dae::GameObject& gameObject, EEvent event)
{
	if (EEvent::Die != event || m_Lives <= 0)
		return;

	if(GetGameObject()->GetTag() == "AI")
	{
		GetGameObject()->GetComponent<TankComponent>()->MoveToRandomLocation();
		return;
	}
	--m_Lives;
	gameObject.GetComponent<HorizontalSpriteList>()->RemoveItem(1);

	if (m_Lives <= 0)
	{
		GetSubject()->Notify(*GetGameObject(), EEvent::Lose);
	}
	else
	{
		GetSubject()->Notify(*GetGameObject(), EEvent::SwitchLevel);
	}
}
