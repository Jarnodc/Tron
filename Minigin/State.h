#pragma once
#include "GameObject.h"
#include "SpriteComponent.h"

class State
{
public:
	State(dae::GameObject* pGO, SpriteComponent::SourcePart sp)
	:m_pGameObject{pGO},m_SpritePart { sp }{}
	virtual ~State() = default;

	State(const State& other) = delete;
	State(State&& other) noexcept = delete;
	State& operator=(const State& other) = delete;
	State& operator=(State&& other) noexcept = delete;
	virtual void Start()
	{
		if(const auto spriteComp = m_pGameObject->GetComponent<SpriteComponent>())
			spriteComp->ChangeState(m_SpritePart);
	}
	virtual void Execute()
	{
		
	}
protected:
	SpriteComponent::SourcePart m_SpritePart{};
	dae::GameObject* m_pGameObject{};
};