#include "pch.h"
#include "ScoreComponent.h"

#include "EEvent.h"
#include "TankComponent.h"
#include <algorithm>
#include <fstream>

#include "TextComponent.h"

void ScoreComponent::Notify(const dae::GameObject& pObject, EEvent event)
{
	switch (event)
	{
	case EEvent::Kill:
		if(const auto tankComp = pObject.GetComponent<TankComponent>())
		{
			m_curScore += tankComp->GetValue();
			if (const auto textComp = GetGameObject()->GetComponent<dae::TextComponent>())
			{
				textComp->SetText(std::to_string(m_curScore));
			}
		}
		break;
	case EEvent::Lose:
		SaveScore();
		m_curScore = 0;
		if (const auto textComp = GetGameObject()->GetComponent<dae::TextComponent>())
		{
			textComp->SetText(std::to_string(m_curScore));
		}
		break;
	}
}

void ScoreComponent::SaveScore()
{
	std::ranges::sort(m_HighScores, std::greater <>());

	for (int& score : m_HighScores)
	{
		if (score < m_curScore)
		{
			const int tempScore{ score };
			score = m_curScore;
			m_curScore = tempScore;
		}
	}
	
	if(std::ofstream stream{ "../Data/HighScore.SIIUUU" })
	{
		for (size_t i = 0; i < m_HighScores.size(); ++i)
		{
			stream << "[" << i << "]" << m_HighScores[i] << std::endl;
		}
		stream.close();
	}
}

void ScoreComponent::ReadScores()
{
	std::ifstream stream{ "../Data/HighScore.SIIUUU", std::ios::in };
	if(stream)
	{
		std::string line;
		while(std::getline(stream,line))
		{
			const int idx =std::stoi(line.substr(line.find('[') + 1));
			line = line.substr(line.find(']') + 1);
			m_HighScores[idx] = std::stoi(line);
		}
		stream.close();
	}

	stream.close();
}
