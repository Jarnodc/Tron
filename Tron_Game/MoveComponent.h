#pragma once
#include <Component.h>
class MoveComponent final : public Component
{
public:
	enum class EDirection
	{
		Up,
		Down,
		Left,
		Right,
		Vertical,
		Horizontal
	};


	MoveComponent(dae::GameObject* pGO) :Component(pGO) {}
	~MoveComponent() override = default;

	MoveComponent(const MoveComponent& other) = delete;
	MoveComponent(MoveComponent&& other) noexcept = delete;
	MoveComponent& operator=(const MoveComponent& other) = delete;
	MoveComponent& operator=(MoveComponent&& other) noexcept = delete;

	void Update() override {};
	void FixedUpdate() override {}
	void Render() const override {}

	void Move(glm::vec3 moveVec) const;

	bool CanMoveTo(EDirection dir) const;
private:

};

