#pragma once
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

		std::string GetName()const { return m_Name; }

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter; 
	};

}
