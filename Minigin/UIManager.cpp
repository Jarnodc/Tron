#include "MiniginPCH.h"
#include "UIManager.h"

void UIManager::HandleButtons(dae::EInputState inputState, const glm::vec2& mousePos)
{
	for (size_t i = 0; i < m_Buttons.size(); ++i)
	{
		switch (inputState)
		{
		case dae::EInputState::Down:
			m_Buttons[i]->ButtonDown(mousePos);
			break;
		case dae::EInputState::Up:
			m_Buttons[i]->ButtonUp(mousePos);
			break;
		}
	}
}
