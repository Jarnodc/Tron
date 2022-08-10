#include "MiniginPCH.h"
#include "SceneManager.h"

#include <functional>

#include "Scene.h"


void dae::SceneManager::Update() const
{
	//for(auto& scene : m_Scenes)
	if (m_pActiveScene)
	{
		m_pActiveScene->Update();
	}
}

void dae::SceneManager::FixedUpdate() const
{
	//for (auto& scene : m_Scenes)
	if (m_pActiveScene)
	{
		m_pActiveScene->FixedUpdate();
	}
}

void dae::SceneManager::Render() const
{
	//for (const auto& scene : m_Scenes)
	if(m_pActiveScene)
	{
		m_pActiveScene->Render();
	}
}

void dae::SceneManager::LoadScene(const std::string& name)
{
	if(!m_LevelFunc.contains(name))
		return;
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	if (m_pActiveScene && m_LevelFunc[name].first) // .first holds boolean if the default needs to be hold
	{
		const auto objects{ m_pActiveScene->GetDefaultGameObject() };
		for (const auto& obj : objects)
		{
			scene->AddDefault(obj);
		}
	}
	m_LevelFunc[name].second(*scene);

	m_pActiveScene = scene;
	//m_Scenes.emplace_back(scene);
}

void dae::SceneManager::SetSpawnLevelFunc(std::function<void(Scene&)> func, const std::string& LevelName, bool keepDefault)
{
	m_LevelFunc[LevelName] = std::pair(keepDefault,func);
}
