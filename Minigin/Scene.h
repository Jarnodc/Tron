#pragma once
#include "GameObject.h"
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
		friend void SceneManager::LoadScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);
		void Remove(const std::shared_ptr<GameObject>& object);

		void Update() const;
		void FixedUpdate() const;
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;

		Scene& operator=(const Scene& other) = delete;

		Scene& operator=(Scene&& other) = delete;

		std::vector<std::shared_ptr<GameObject>> GetObjects() const;
		template<typename T>
		std::vector<dae::GameObject*> GetGameObject() const;
		std::vector<dae::GameObject*> GetGameObject(const Tag& tag) const;
		template<typename T>
		std::vector<dae::GameObject*> GetGameObject(const Tag& tag) const;

		std::string GetName()const { return m_Name; }

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter; 
	};

	template<typename T>
	inline std::vector<dae::GameObject*> Scene::GetGameObject() const
	{
		std::vector<dae::GameObject*> objects{};
		for (size_t i = 0; i < m_Objects.size(); ++i)
		{
			if(m_Objects[i].get()->GetComponent<T>() != nullptr)
			{
				objects.emplace_back(m_Objects[i].get());
			}
		}
		return objects;
	}

	inline std::vector<dae::GameObject*> Scene::GetGameObject(const Tag& tag) const
	{
		std::vector<dae::GameObject*> objects{};
		for (size_t i = 0; i < m_Objects.size(); ++i)
		{
			if (m_Objects[i].get()->GetTag() == tag)
			{
				objects.emplace_back(m_Objects[i].get());
			}
		}
		return objects;
	}

	template<typename T>
	inline std::vector<dae::GameObject*> Scene::GetGameObject(const Tag& tag) const
	{
		std::vector<dae::GameObject*> objects{};
		for (size_t i = 0; i < m_Objects.size(); ++i)
		{
			if (m_Objects[i].get()->GetTag() == tag)
			{
				if (m_Objects[i].get()->GetComponent<T>() != nullptr)
				{
					objects.emplace_back(m_Objects[i].get());
				}
			}
		}
		return objects;
	}
}
