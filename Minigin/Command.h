#pragma once
#include "GameObject.h"

class Command
{
public:
	explicit Command(dae::GameObject* gameObject);
	virtual ~Command() = default;
	virtual void Execute() = 0;

	Command(const Command& other) = delete;
	Command(Command&& other) noexcept = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other) noexcept = delete;
protected:
	dae::GameObject* GetGameObject() const;
private:
	dae::GameObject* m_pGameObject = nullptr;
};