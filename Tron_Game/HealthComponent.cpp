#include "pch.h"
#include "HealthComponent.h"

#include "EEvent.h"
#include "HorizontalSpriteList.h"

void HealthComponent::Notify(const dae::GameObject& , EEvent event)
{
	if (EEvent::LoseHealth != event)
		return;
	if (m_Health - 1 <= 0)
	{
		GetSubject()->Notify(*GetGameObject(), EEvent::Die);
		return;
	}
	--m_Health;
	GetGameObject()->GetComponent<HorizontalSpriteList>()->RemoveItem(1);
}
