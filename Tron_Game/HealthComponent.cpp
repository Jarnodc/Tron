#include "pch.h"
#include "HealthComponent.h"

#include "EEvent.h"
#include "HorizontalSpriteList.h"

void HealthComponent::Notify(const dae::GameObject& , EEvent event)
{
	if (EEvent::LoseHealth != event)
		return;
	--m_Health;
	if (m_Health <= 0)
	{
		GetSubject()->Notify(*GetGameObject(), EEvent::Die);
		return;
	}
}
