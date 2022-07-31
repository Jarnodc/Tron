#include "pch.h"
#include "Prefab.h"

#include "AIController.h"
#include "BoxCollider.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "HealthComponent.h"
#include "HorizontalSpriteList.h"
#include "MoveComponent.h"
#include "RigidBody.h"
#include "SpriteComponent.h"
#include "TankComponent.h"


std::shared_ptr<dae::GameObject> BulletPrefab(dae::GameObject* parent, const glm::vec3& direction)
{
	const auto pGO{ std::make_shared<dae::GameObject>("Bullet")};
	pGO->AddComponent(new Bullet(pGO.get(), parent, direction));
	pGO->AddComponent(new BoxCollider(pGO.get(), 10));
	pGO->AddComponent(new SpriteComponent(pGO.get(), SpriteComponent::SourcePart("TronSpriteSheet.png", 1, 1, { 32 * 6,0,10,10 }), { 0,0,10,10 }));
	pGO->AddComponent(new RigidBody(pGO.get(), { 40,40,40 }));

	return pGO;
}

std::shared_ptr<dae::GameObject> BlueTankPrefab(dae::Scene& scene)
{
	const auto pGO{ std::make_shared<dae::GameObject>("AI") };

	pGO->AddComponent(new BoxCollider(pGO.get(), 25));
	pGO->AddComponent(new SpriteComponent(pGO.get(), SpriteComponent::SourcePart("TronSpriteSheet.png", 1, 1, { 32 * 9,0,32,32 }), { 0,0,25,25 }));
	const auto tankComp{ new TankComponent(pGO.get(),{16,16,448,416},100) };
	pGO->AddComponent<MoveComponent>();
	pGO->AddComponent(new RigidBody(pGO.get(),{10,10,10 })); 
	pGO->AddComponent(tankComp);
	pGO->AddComponent<BulletManager>();

	const auto controller{ pGO->AddComponent<AIController>()};

	const auto pHealth{ std::make_shared<dae::GameObject>() };
	const auto healthComp{ new HealthComponent(pGO.get(), 1) };
	pHealth->AddComponent(healthComp);

	healthComp->GetSubject()->AddObserver(controller);

	tankComp->GetSubject()->AddObserver(healthComp);

	scene.Add(pHealth);

	return pGO;
}
#include "InputManager.h"
#include "ICommand.h"
#include "ScoreComponent.h"
#include "TextComponent.h"
#include "GameManager.h"
std::shared_ptr<dae::GameObject> RedTankPrefab(dae::Scene& scene)
{
	const auto pGO{ std::make_shared<dae::GameObject>("Player")};

	const auto cont{ pGO->AddComponent<Controller>() };
	const auto contID{ dae::InputManager::GetInstance().AddPlayer() };
	const auto kbID{ dae::InputManager::GetInstance().AddPlayer(true) };

	// -- Attack --
	dae::InputManager::GetInstance().AddCommand(dae::Xbox360Controller::ControllerButton::ButtonA, std::make_shared<AttackCommand>(pGO.get()), contID,dae::EInputState::Pressed);
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_E, std::make_shared<AttackCommand>(pGO.get()), kbID, dae::EInputState::Pressed);

	// -- RotateCW --
	dae::InputManager::GetInstance().AddCommand(dae::Xbox360Controller::ControllerButton::ButtonRightShoulder, std::make_shared<RotateCommand>(pGO.get(),true), contID, dae::EInputState::Down);
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_X, std::make_shared<RotateCommand>(pGO.get(),true), kbID, dae::EInputState::Down);

	// -- RotateCCW --
	dae::InputManager::GetInstance().AddCommand(dae::Xbox360Controller::ControllerButton::ButtonLeftShoulder, std::make_shared<RotateCommand>(pGO.get()), contID, dae::EInputState::Down);
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_C, std::make_shared<RotateCommand>(pGO.get()), kbID, dae::EInputState::Down);

	// -- MoveLeft --
	dae::InputManager::GetInstance().AddCommand(dae::Xbox360Controller::ControllerButton::ButtonDPADLeft, std::make_shared<MoveCommand>(pGO.get(), glm::vec3{-1,0,0}), contID, dae::EInputState::Down);
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_A, std::make_shared<MoveCommand>(pGO.get(), glm::vec3{ -1,0,0 }), kbID, dae::EInputState::Down);
	
	// -- MoveRight --
	dae::InputManager::GetInstance().AddCommand(dae::Xbox360Controller::ControllerButton::ButtonDPADRight, std::make_shared<MoveCommand>(pGO.get(),glm::vec3{1,0,0}), contID, dae::EInputState::Down);
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_D, std::make_shared<MoveCommand>(pGO.get(), glm::vec3{ 1,0,0 }), kbID, dae::EInputState::Down);

	// -- MoveUp --
	dae::InputManager::GetInstance().AddCommand(dae::Xbox360Controller::ControllerButton::ButtonDPADUp, std::make_shared<MoveCommand>(pGO.get(),glm::vec3{ 0,-1,0}), contID, dae::EInputState::Down);
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_W, std::make_shared<MoveCommand>(pGO.get(), glm::vec3{ 0,-1,0 }), kbID, dae::EInputState::Down);
	
	// -- MoveDown --
	dae::InputManager::GetInstance().AddCommand(dae::Xbox360Controller::ControllerButton::ButtonDPADDown, std::make_shared<MoveCommand>(pGO.get(),glm::vec3{ 0,1,0}), contID, dae::EInputState::Down);
	dae::InputManager::GetInstance().AddCommand(SDL_SCANCODE_S, std::make_shared<MoveCommand>(pGO.get(), glm::vec3{ 0,1,0 }), kbID, dae::EInputState::Down);


	pGO->AddComponent(new BoxCollider(pGO.get(), 25));
	pGO->AddComponent(new SpriteComponent(pGO.get(), SpriteComponent::SourcePart("TronSpriteSheet.png", 1, 1, { 32 * 11,0,32,32 }), { 0,0,25,25 }));
	const auto tankComp{ new TankComponent(pGO.get(),{16,16,448,416},250) };
	pGO->AddComponent<MoveComponent>();
	pGO->AddComponent(new RigidBody(pGO.get(), { 20,20,20 }));
	pGO->AddComponent(tankComp);
	pGO->AddComponent<BulletManager>();

	//HealthCompp
	const auto pHealth{ std::make_shared<dae::GameObject>() };
	const auto healthComp{ new HealthComponent(pHealth.get(), 1) };
	pHealth->AddComponent(healthComp);
	pHealth->AddComponent(new HorizontalSpriteList(pHealth.get(),new SpriteComponent(pHealth.get(), SpriteComponent::SourcePart("TronSpriteSheet.png", 1, 1, { 32 * 11,0,32,32 }), { 10,0,30,30 }),3));
	pHealth->SetPosition(500, 20);
	healthComp->GetSubject()->AddObserver(cont);
	tankComp->GetSubject()->AddObserver(healthComp);

	scene.AddDefault(pHealth);

	//ScoreComp
	const auto pScore{ std::make_shared<dae::GameObject>() };
	pScore->SetPosition(500, 80);
	pScore->AddComponent<dae::TextComponent>();
	const auto scoreComp = pScore->AddComponent<ScoreComponent>();
	cont->GetSubject()->AddObserver(scoreComp);
	scene.AddDefault(pScore);

	//GameManager
	const auto gm = scene.GetGameObject<GameManager>().front();
	cont->GetSubject()->AddObserver(gm->GetComponent<GameManager>());

	return pGO;
}

std::shared_ptr<dae::GameObject> GreenTankPrefab(dae::Scene& scene)
{
	const auto pGO{ std::make_shared<dae::GameObject>() };
	pGO->AddComponent(new BoxCollider(pGO.get(), 30));
	pGO->AddComponent(new SpriteComponent(pGO.get(), SpriteComponent::SourcePart("TronSpriteSheet.png", 1, 1, { 32 * 8,0,32,32 }), { 0,0,30,30 }));
	const auto tankComp{ new TankComponent(pGO.get(),{16,16,448,416},250) };
	pGO->AddComponent(new RigidBody(pGO.get(), { 20,20,20 }));
	pGO->AddComponent<MoveComponent>();
	pGO->AddComponent(tankComp);
	pGO->AddComponent<BulletManager>();

	const auto cont{ pGO->AddComponent<Controller>() };

	const auto pHealth{ std::make_shared<dae::GameObject>() };
	const auto healthComp{ new HealthComponent(pGO.get(), 1) };
	pHealth->AddComponent(healthComp);

	healthComp->GetSubject()->AddObserver(cont);
	tankComp->GetSubject()->AddObserver(healthComp);

	scene.Add(pHealth);

	const auto AIControllers = scene.GetGameObject("AI");

	for (const auto& controller : AIControllers)
	{
		controller->GetComponent<AIController>()->AddTarget(pGO.get());
	}

	return pGO;
}
