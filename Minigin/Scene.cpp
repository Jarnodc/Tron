#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <algorithm>

using namespace dae;

std::vector<std::shared_ptr<GameObject>> dae::Scene::GetObjects() const
{
	return m_Objects;
}

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;


void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.emplace_back(object);
}

void dae::Scene::AddDefault(const std::shared_ptr<GameObject>& object)
{
	m_DefaultObjects.emplace_back(object);
}

void dae::Scene::Remove( std::shared_ptr<GameObject> object)
{
	m_Objects.erase(std::ranges::remove(m_Objects, object).begin());
}

void dae::Scene::RemoveDefault(std::shared_ptr<GameObject> object)
{
	m_DefaultObjects.erase(std::ranges::remove(m_DefaultObjects, object).begin());
}

void Scene::Update() const
{
	/*for(const auto& object : m_Objects)
	{
		object->Update();
	}*/
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Update();
	}
	for (size_t i = 0; i < m_DefaultObjects.size(); i++)
	{
		m_DefaultObjects[i]->Update();
	}
}
void Scene::FixedUpdate() const
{
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->FixedUpdate();
	}
	for (size_t i = 0; i < m_DefaultObjects.size(); i++)
	{
		m_DefaultObjects[i]->FixedUpdate();
	}
	/*for(const auto& object : m_Objects)
	{
		object->FixedUpdate();
	}*/
}

void Scene::Render() const
{
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Render();
	}
	for (size_t i = 0; i < m_DefaultObjects.size(); i++)
	{
		m_DefaultObjects[i]->Render();
	}
	/*for (const auto& object : m_Objects)
	{
		object->Render();
	}*/
}

