#pragma once
#include <Component.h>

#include "Observer.h"
#include "TextComponent.h"

class ScoreComponent final : public Component, public Observer
{
public:
	ScoreComponent(dae::GameObject* pGO) :Component(pGO), Observer()
	{
		m_HighScores.resize(10);
		ReadScores();
		if (const auto textComp = GetGameObject()->GetComponent<dae::TextComponent>())
		{
			textComp->SetText(std::to_string(m_curScore));
		}
	}
	~ScoreComponent() override { SaveScore(); }

	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) noexcept = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) noexcept = delete;

	void Update() override {}
	void FixedUpdate() override {}
	void Render() const override {}

	void Notify(const dae::GameObject& pObject, EEvent event) override;

	int GetScore()const { return m_curScore; }
private:
	void SaveScore();
	void ReadScores();


	int m_curScore{};
	std::vector<int> m_HighScores{};
};

