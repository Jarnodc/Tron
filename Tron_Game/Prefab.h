#pragma once
#include <GameObject.h>

#include "Scene.h"

class AIController;
std::shared_ptr<dae::GameObject> BulletPrefab(dae::GameObject* parent, const glm::vec3& direction);

std::shared_ptr<dae::GameObject> BlueTankPrefab(dae::Scene& scene);

std::shared_ptr<dae::GameObject> BluePlayerTankPrefab(dae::Scene& scene);

std::shared_ptr<dae::GameObject> RedTankPrefab(dae::Scene& scene);

std::shared_ptr<dae::GameObject> GreenTankPrefab(dae::Scene& scene);