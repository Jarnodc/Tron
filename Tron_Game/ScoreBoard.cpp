#include "pch.h"
#include "ScoreBoard.h"
#include <fstream>

#include "GameObject.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "TimerInfo.h"

void ScoreBoard::Update()
{
	m_CurTime += dae::TimerInfo::GetInstance().deltaTime;

	if(m_CurTime >= m_MaxTime)
	{
		dae::SceneManager::GetInstance().LoadScene("MainScene");
	}
}

void ScoreBoard::Render() const
{
	const size_t len{ m_HighScores.size() };
	int top{ 50 };
	for (size_t i = 0; i < len; ++i)
	{
		const std::string line{ std::to_string(i + 1) + ": " + std::to_string(m_HighScores[i])};
		dae::Renderer::GetInstance().RenderText(line, top ,dae::Renderer::HorAllignment::Mid,{dae::Renderer::HorAllignment::Mid,dae::Renderer::VerAllignment::Top },"Lingua.otf",40);
		top += 40;
	}
}

void ScoreBoard::ReadScores()
{
	std::ifstream stream{ "../Data/HighScore.SIIUUU", std::ios::in };
	if (stream)
	{
		std::string line;
		while (std::getline(stream, line))
		{
			const int idx = std::stoi(line.substr(line.find('[') + 1));
			line = line.substr(line.find(']') + 1);
			m_HighScores[idx] = std::stoi(line);
		}
		stream.close();
	}

	stream.close();
}
