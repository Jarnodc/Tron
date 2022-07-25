#include "pch.h"
#include "BulletManager.h"

#include <algorithm>

#include "SceneManager.h"
#include "Scene.h"

#include "Bullet.h"

void BulletManager::AddBullet(const std::shared_ptr<dae::GameObject>& bullet)
{
	m_pBullets.emplace_back(bullet);
	dae::SceneManager::GetInstance().GetScene().Add(bullet);
}

void BulletManager::RemoveBullet(const std::shared_ptr<dae::GameObject>& bullet)
{
	dae::SceneManager::GetInstance().GetScene().Remove(bullet);
	m_pBullets.erase(std::ranges::remove(m_pBullets,bullet).begin());
}

void BulletManager::Update()
{
	for (size_t i = 0; i < m_pBullets.size(); ++i)
	{
		if (m_pBullets[i]->GetComponent<Bullet>()->IsDead())
		{
			RemoveBullet(m_pBullets[i]);
			return;
		}
	}
}
