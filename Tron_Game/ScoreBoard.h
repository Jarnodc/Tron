#pragma once
#include <Component.h>
class ScoreBoard final:  public Component
{
public:
	ScoreBoard(dae::GameObject* pGO) :Component(pGO)
	{
		m_HighScores.resize(10);
		ReadScores();
	}
	~ScoreBoard() override = default;

	ScoreBoard(const ScoreBoard& other) = delete;
	ScoreBoard(ScoreBoard&& other) noexcept = delete;
	ScoreBoard& operator=(const ScoreBoard& other) = delete;
	ScoreBoard& operator=(ScoreBoard&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override{}
	void Render() const override;

private:
	void ReadScores();

	std::vector<int> m_HighScores{};

	float m_MaxTime{ 5 };
	float m_CurTime{};
};

