#pragma once
#include "Command.h"
#include "TankComponent.h"

class AttackCommand final : public Command
{
public:
	AttackCommand(dae::GameObject* gameObject):Command(gameObject){}
	~AttackCommand() override= default;

	AttackCommand(const AttackCommand& other) = delete;
	AttackCommand(AttackCommand&& other) noexcept = delete;
	AttackCommand& operator=(const AttackCommand& other) = delete;
	AttackCommand& operator=(AttackCommand&& other) noexcept = delete;

	void Execute() override
	{
		GetGameObject()->GetComponent<TankComponent>()->Attack();
	}
};
class RotateCommand final : public Command
{
public:
	RotateCommand(dae::GameObject* gameObject, bool cwrotate = false):Command(gameObject),m_CWRotate(cwrotate){}
	~RotateCommand() override= default;

	RotateCommand(const RotateCommand& other) = delete;
	RotateCommand(RotateCommand&& other) noexcept = delete;
	RotateCommand& operator=(const RotateCommand& other) = delete;
	RotateCommand& operator=(RotateCommand&& other) noexcept = delete;

	void Execute() override
	{
		GetGameObject()->GetComponent<TankComponent>()->Rotate(m_CWRotate);
	}
private:
	bool m_CWRotate{ false };
};

#include "MoveComponent.h"
class MoveCommand final : public Command
{
public:
	MoveCommand(dae::GameObject* gameObject, const glm::vec3& moveVec) :Command(gameObject), m_MoveVec(moveVec) {}
	~MoveCommand() override = default;

	MoveCommand(const MoveCommand& other) = delete;
	MoveCommand(MoveCommand&& other) noexcept = delete;
	MoveCommand& operator=(const MoveCommand& other) = delete;
	MoveCommand& operator=(MoveCommand&& other) noexcept = delete;

	void Execute() override
	{
		GetGameObject()->GetComponent<MoveComponent>()->Move(m_MoveVec);
		if(m_MoveVec.x == 0)// 90 or 270 degrees
		{
			if (m_MoveVec.y > 0)
				GetGameObject()->GetComponent<SpriteComponent>()->SetRotation(180);
			else
				GetGameObject()->GetComponent<SpriteComponent>()->SetRotation(0);
		}
		else
		{
			if (m_MoveVec.x > 0)
				GetGameObject()->GetComponent<SpriteComponent>()->SetRotation(90);
			else
				GetGameObject()->GetComponent<SpriteComponent>()->SetRotation(270);
		}
	}
private:
	glm::vec3 m_MoveVec;
};
