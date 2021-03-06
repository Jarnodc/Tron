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
class RotateCWCommand final : public Command
{
public:
	RotateCWCommand(dae::GameObject* gameObject):Command(gameObject){}
	~RotateCWCommand() override= default;

	RotateCWCommand(const RotateCWCommand& other) = delete;
	RotateCWCommand(RotateCWCommand&& other) noexcept = delete;
	RotateCWCommand& operator=(const RotateCWCommand& other) = delete;
	RotateCWCommand& operator=(RotateCWCommand&& other) noexcept = delete;

	void Execute() override
	{
		GetGameObject()->GetComponent<TankComponent>()->Rotate();
	}
};
class RotateCCWCommand final : public Command
{
public:
	RotateCCWCommand(dae::GameObject* gameObject):Command(gameObject){}
	~RotateCCWCommand() override= default;

	RotateCCWCommand(const RotateCCWCommand& other) = delete;
	RotateCCWCommand(RotateCCWCommand&& other) noexcept = delete;
	RotateCCWCommand& operator=(const RotateCCWCommand& other) = delete;
	RotateCCWCommand& operator=(RotateCCWCommand&& other) noexcept = delete;

	void Execute() override
	{
		GetGameObject()->GetComponent<TankComponent>()->Rotate(false);
	}
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
	}
private:
	glm::vec3 m_MoveVec;
};
