#include "pch.h"
#include "LoadGameMode.h"

#include "Renderer.h"
#include "SceneManager.h"
#include "UIManager.h"

void LoadGameMode::Render() const
{
	UIButton::Render();
	const auto offset{ m_DstRect.w / 10 };
	const SDL_Rect offsetRect{ m_DstRect.x + offset,m_DstRect.y + offset,m_DstRect.w - 2 * offset, m_DstRect.h - 2 * offset };
	dae::Renderer::GetInstance().RenderText(m_LevelName, offsetRect);
}

void LoadGameMode::OnButtonUp()
{
	dae::SceneManager::GetInstance().LoadScene(m_LevelName);
}
