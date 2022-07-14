#include "pch.h"
#include "HealthComponent.h"

#include "EEvent.h"

void HealthComponent::Hit(int damage)
{
	m_Health -= damage;
	if(m_Health <= 0)
	{
		GetSubject()->Notify(*GetGameObject(), EEvent::Die);
	}
}
