#include "pch.h"
#include "SkipLevelButton.h"

#include "EEvent.h"
#include "GameManager.h"
#include "Renderer.h"
#include "Scene.h"
#include "SceneManager.h"

void SkipLevelButton::Render() const
{
	UIButton::Render();
	const auto offset{ m_DstRect.w / 10 };
	const SDL_Rect offsetRect{ m_DstRect.x + offset,m_DstRect.y + offset,m_DstRect.w - 2 * offset, m_DstRect.h - 2 * offset };
	dae::Renderer::GetInstance().RenderText("Skip Level", offsetRect);
}

void SkipLevelButton::OnButtonUp()
{
	const auto objs = dae::SceneManager::GetInstance().GetScene().GetGameObject<GameManager>();
	if(!objs.empty())
	{
		objs.front()->GetComponent<GameManager>()->Notify(*GetGameObject(),EEvent::SwitchLevel);
	}
}
