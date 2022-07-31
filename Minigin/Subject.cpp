#include "MiniginPCH.h"
#include "Subject.h"

#include <algorithm>

void Subject::AddObserver(Observer* pObserver)
{
	m_pObservers.push_back(pObserver);
}

void Subject::RemoveObserver(Observer* pObserver)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(),pObserver));
}

void Subject::Notify(const dae::GameObject& gameObject, EEvent event)
{
	for (size_t i = 0; i < m_pObservers.size(); i++)
	{
		if(!m_pObservers[i])
		{
			m_pObservers.erase(std::ranges::remove(m_pObservers, m_pObservers[i]).begin());
		}
		else
		{
			m_pObservers[i]->Notify(gameObject, event);
		}
	}
}
