#include "pch.h"
#include "Prefab.h"

#include "AIController.h"
#include "BoxCollider.h"
#include "Bullet.h"
#include "HealthComponent.h"
#include "HorizontalSpriteList.h"
#include "MoveComponent.h"
#include "RigidBody.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "TankComponent.h"


std::shared_ptr<dae::GameObject> BulletPrefab(dae::GameObject* parent, const glm::vec3& direction)
{
	const auto pGO{ std::make_shared<dae::GameObject>() };
	pGO->AddComponent(new Bullet(pGO.get(), parent, direction));
	pGO->AddComponent(new BoxCollider(pGO.get(), 10));
	pGO->AddComponent(new SpriteComponent(pGO.get(), SpriteComponent::SourcePart("TronSpriteSheet.png", 1, 1, { 32 * 6,0,10,10 }), { 0,0,10,10 }));
	pGO->AddComponent(new RigidBody(pGO.get(), { 100,100,100 }));

	return pGO;
}

std::shared_ptr<dae::GameObject> RedTankPrefab(dae::Scene& scene)
{
	const auto pGO{ std::make_shared<dae::GameObject>("AI") };

	pGO->AddComponent(new BoxCollider(pGO.get(), 30));
	pGO->AddComponent(new SpriteComponent(pGO.get(), SpriteComponent::SourcePart("TronSpriteSheet.png", 1, 1, { 32 * 11,0,32,32 }), { 0,0,30,30 }));
	pGO->AddComponent(new RigidBody(pGO.get(),{40,40,40}));
	pGO->AddComponent<MoveComponent>();

	const auto controller{ pGO->AddComponent<AIController>()};

	const auto pHealth{ std::make_shared<dae::GameObject>() };
	const auto healthComp{ new HealthComponent(pGO.get(), 1) };
	pHealth->AddComponent(healthComp);

	healthComp->GetSubject()->AddObserver(controller);
	pGO->AddComponent<TankComponent>()->GetSubject()->AddObserver(healthComp);

	scene.Add(pHealth);

	return pGO;
}
#include "InputManager.h"
#include "ICommand.h"
std::shared_ptr<dae::GameObject> BlueTankPrefab(dae::Scene& scene)
{
	const auto pGO{ std::make_shared<dae::GameObject>("Player")};

	pGO->AddComponent(new BoxCollider(pGO.get(), 25));
	pGO->AddComponent(new SpriteComponent(pGO.get(), SpriteComponent::SourcePart("TronSpriteSheet.png", 1, 1, { 32 * 9,0,32,32 }), { 0,0,25,25 }));
	pGO->AddComponent(new RigidBody(pGO.get(), { 200,200,200 }));
	pGO->AddComponent<MoveComponent>();
	
	const auto cont{ pGO->AddComponent<Controller>() };
	const auto playerID{ dae::InputManager::GetInstance().AddPlayer() };

	// -- Attack --
	dae::InputManager::GetInstance().AddCommand(dae::Xbox360Controller::ControllerButton::ButtonA, std::make_shared<AttackCommand>(pGO.get()), playerID,dae::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_E, std::make_shared<AttackCommand>(pGO.get()), dae::EInputState::Pressed);

	// -- RotateCW --
	dae::InputManager::GetInstance().AddCommand(dae::Xbox360Controller::ControllerButton::ButtonRightShoulder, std::make_shared<RotateCWCommand>(pGO.get()), playerID, dae::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_X, std::make_shared<RotateCWCommand>(pGO.get()), dae::EInputState::Pressed);

	// -- RotateCCW --
	dae::InputManager::GetInstance().AddCommand(dae::Xbox360Controller::ControllerButton::ButtonLeftShoulder, std::make_shared<RotateCCWCommand>(pGO.get()), playerID, dae::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_C, std::make_shared<RotateCCWCommand>(pGO.get()), dae::EInputState::Pressed);

	// -- MoveLeft --
	dae::InputManager::GetInstance().AddCommand(dae::Xbox360Controller::ControllerButton::ButtonDPADLeft, std::make_shared<MoveCommand>(pGO.get(),glm::vec3{-1,0,0}), playerID, dae::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_A, std::make_shared<MoveCommand>(pGO.get(), glm::vec3{ -1,0,0 }), dae::EInputState::Pressed);
	
	// -- MoveRight --
	dae::InputManager::GetInstance().AddCommand(dae::Xbox360Controller::ControllerButton::ButtonDPADRight, std::make_shared<MoveCommand>(pGO.get(),glm::vec3{1,0,0}), playerID, dae::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_D, std::make_shared<MoveCommand>(pGO.get(), glm::vec3{ 1,0,0 }), dae::EInputState::Pressed);

	// -- MoveUp --
	dae::InputManager::GetInstance().AddCommand(dae::Xbox360Controller::ControllerButton::ButtonDPADUp, std::make_shared<MoveCommand>(pGO.get(),glm::vec3{ 0,-1,0}), playerID, dae::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_W, std::make_shared<MoveCommand>(pGO.get(), glm::vec3{ 0,-1,0 }), dae::EInputState::Pressed);
	
	// -- MoveDown --
	dae::InputManager::GetInstance().AddCommand(dae::Xbox360Controller::ControllerButton::ButtonDPADDown, std::make_shared<MoveCommand>(pGO.get(),glm::vec3{ 0,1,0}), playerID, dae::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_S, std::make_shared<MoveCommand>(pGO.get(), glm::vec3{ 0,1,0 }), dae::EInputState::Pressed);


	const auto pHealth{ std::make_shared<dae::GameObject>() };
	const auto healthComp{ new HealthComponent(pHealth.get(), 1) };
	pHealth->AddComponent(healthComp);
	pHealth->AddComponent(new HorizontalSpriteList(pHealth.get(),new SpriteComponent(pHealth.get(), SpriteComponent::SourcePart("TronSpriteSheet.png", 1, 1, { 32 * 9,0,32,32 }), { 0,0,30,30 }),3));
	pHealth->MovePosition(200);
	healthComp->GetSubject()->AddObserver(cont);
	pGO->AddComponent<TankComponent>()->GetSubject()->AddObserver(healthComp);

	scene.Add(pHealth);

	const auto AIControllers = scene.GetGameObject("AI");

	for (const auto& controller : AIControllers)
	{
		controller->GetComponent<AIController>()->AddTarget(pGO.get());
	}


	return pGO;
}

std::shared_ptr<dae::GameObject> GreenTankPrefab(dae::Scene& scene)
{
	const auto pGO{ std::make_shared<dae::GameObject>() };
	pGO->AddComponent(new BoxCollider(pGO.get(), 30));
	pGO->AddComponent(new SpriteComponent(pGO.get(), SpriteComponent::SourcePart("TronSpriteSheet.png", 1, 1, { 32 * 8,0,32,32 }), { 0,0,30,30 }));
	pGO->AddComponent(new RigidBody(pGO.get(), { 20,20,20 }));
	pGO->AddComponent<MoveComponent>();

	const auto cont{ pGO->AddComponent<Controller>() };

	const auto pHealth{ std::make_shared<dae::GameObject>() };
	const auto healthComp{ new HealthComponent(pGO.get(), 1) };
	pHealth->AddComponent(healthComp);

	healthComp->GetSubject()->AddObserver(cont);
	pGO->AddComponent<TankComponent>()->GetSubject()->AddObserver(healthComp);

	scene.Add(pHealth);

	const auto AIControllers = scene.GetGameObject("AI");

	for (const auto& controller : AIControllers)
	{
		controller->GetComponent<AIController>()->AddTarget(pGO.get());
	}

	return pGO;
}
