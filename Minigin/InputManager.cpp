#include "MiniginPCH.h"
#include "InputManager.h"

#include <algorithm>

#include "SceneManager.h"
#include "UIManager.h"

bool dae::InputManager::ProcessInput()
{
	if (SDL_PollEvent(&m_Event)) 
	{
		if (m_Event.type == SDL_QUIT)
		{
			return false;
		}
		if (m_Event.button.button == SDL_BUTTON_LEFT)
		{
			const auto mousePos = glm::vec2{ m_Event.button.x,m_Event.button.y };
			if (m_Event.button.type == SDL_MOUSEBUTTONDOWN)
			{
				UIManager::GetInstance().HandleButtons(EInputState::Down, mousePos);
			}
			else if (m_Event.button.type == SDL_MOUSEBUTTONUP)
			{
				UIManager::GetInstance().HandleButtons(EInputState::Up, mousePos);
			}
		}
	}

	Update();
	for (const auto& val : m_ConsoleCommands)
	{
		switch (val->state)
		{
		case EInputState::Down:
			if (IsDownThisFrame(val->controllerButton, val->playerIdx))
				val->command->Execute();
			break;
		case EInputState::Pressed:
			if (IsPressed(val->controllerButton, val->playerIdx))
				val->command->Execute();
			break;
		case EInputState::Up:
			if (IsUpThisFrame(val->controllerButton, val->playerIdx))
				val->command->Execute();
			break;
		}
	}

	for (const auto& val : m_KeyBoardCommands)
	{
		switch (val->state)
		{
		case EInputState::Down:
			if (IsDownThisFrame(val->keyBoardButton, val->playerIdx))
				val->command->Execute();
			break;
		case EInputState::Pressed:
			if (IsPressed(val->keyBoardButton, val->playerIdx))
				val->command->Execute();
			break;
		case EInputState::Up:
			if (IsUpThisFrame(val->keyBoardButton, val->playerIdx))
				val->command->Execute();
			break;
		}
	}
	return true;
}

void dae::InputManager::Update() const
{
	for (const auto& controller : m_pControllers)
	{
		controller->Update();
	}
	for (const auto& kb : m_pKeyBoards)
	{
		kb->Update();
	}
}

PlayerIndex dae::InputManager::AddPlayer(bool IsKeyBoard)
{
	if(IsKeyBoard)
	{
		PlayerIndex idx = static_cast<int>(m_pKeyBoards.size());
		m_pKeyBoards.push_back(std::make_unique<KeyBoardController>(idx));
		return idx;		
	}
	PlayerIndex idx = static_cast<int>(m_pControllers.size());
	m_pControllers.push_back(std::make_unique<Xbox360Controller>(idx));
	return idx;
}

void dae::InputManager::RemovePlayer(PlayerIndex idx, bool IsKeyBoard)
{
	if(IsKeyBoard)
	{
		if (idx < m_pKeyBoards.size())
		{
			for (size_t i = 0; i < m_KeyBoardCommands.size(); ++i)
			{
				if(m_KeyBoardCommands[i]->playerIdx == idx)
				{
					m_KeyBoardCommands.erase(std::ranges::remove(m_KeyBoardCommands, m_KeyBoardCommands[i]).begin());
				}
			}
			m_pKeyBoards.erase(m_pKeyBoards.begin() + idx);
		}
		else
			std::cout << "Idx is too high" << std::endl;
	}
	else
	{
		if (idx < m_pControllers.size())
		{
			for (size_t i = 0; i < m_pKeyBoards.size(); ++i)
			{
				if (m_ConsoleCommands[i]->playerIdx == idx)
				{
					m_ConsoleCommands.erase(std::ranges::remove(m_ConsoleCommands, m_ConsoleCommands[i]).begin());
				}
			}
			m_pControllers.erase(m_pControllers.begin() + idx);
		}
		else
			std::cout << "Idx is too high" << std::endl;
	}

}

bool dae::InputManager::IsPressed(Xbox360Controller::ControllerButton button, PlayerIndex playerIdx) const
{
	return m_pControllers[playerIdx]->IsPressed(button);
}

bool dae::InputManager::IsPressed(SDL_Scancode scancode, PlayerIndex playerIdx) const
{
	return m_pKeyBoards[playerIdx]->IsPressed(scancode);
}

bool dae::InputManager::IsDownThisFrame(Xbox360Controller::ControllerButton button, PlayerIndex playerIdx) const
{
	return m_pControllers[playerIdx]->IsDown(button);
}

bool dae::InputManager::IsDownThisFrame(SDL_Scancode scancode, PlayerIndex playerIdx) const
{
	return m_pKeyBoards[playerIdx]->IsDown(scancode);
}

bool dae::InputManager::IsUpThisFrame(Xbox360Controller::ControllerButton button, PlayerIndex playerIdx) const
{
	return m_pControllers[playerIdx]->IsUp(button);
}

bool dae::InputManager::IsUpThisFrame(SDL_Scancode scancode, PlayerIndex playerIdx) const
{
	return m_pKeyBoards[playerIdx]->IsUp(scancode);
}

void dae::InputManager::AddCommand(Xbox360Controller::ControllerButton button, std::shared_ptr<Command> command, PlayerIndex playerIdx, EInputState state)
{
	if(playerIdx > m_pControllers.size())
	{
		std::cout << "You are adding a command to an no existing player" << std::endl; 
		return;
	}
	ControllerCommand* cc = new ControllerCommand;
	cc->command = command;
	cc->controllerButton = button;
	cc->state = state;
	cc->playerIdx = playerIdx;
	m_ConsoleCommands.emplace_back(cc);
}

void dae::InputManager::AddCommand(SDL_Scancode keyBoardKey, std::shared_ptr<Command> command, PlayerIndex playerIdx, EInputState state)
{
	if (playerIdx > m_pKeyBoards.size())
	{
		std::cout << "You are adding a command to an no existing player" << std::endl;
		return;
	}
	KeyBoardCommand* kc= new KeyBoardCommand();
	kc->keyBoardButton = keyBoardKey;
	kc->command = command;
	kc->state = state;
	kc->playerIdx = playerIdx;
	m_KeyBoardCommands.emplace_back(kc);
}

void dae::InputManager::RemoveCommand(Xbox360Controller::ControllerButton button, std::shared_ptr<Command> command, PlayerIndex playerIdx, EInputState state)
{
	const auto len{ m_ConsoleCommands.size() };
	for (size_t i = 0; i < len; ++i)
	{
		const ControllerCommand* temp =m_ConsoleCommands[i];
		if (temp != nullptr)
		{
			if (temp->controllerButton == button)
			{
				if (typeid(*temp->command) == typeid(*command))
				{
					if (temp->state == state)
					{
						if (temp->playerIdx == playerIdx)
						{
							m_ConsoleCommands.erase(std::ranges::remove(m_ConsoleCommands, m_ConsoleCommands[i]).begin());
							return;
						}
					}
				}
			}
		}
	}
}

void dae::InputManager::RemoveCommand(SDL_Scancode keyBoardKey, std::shared_ptr<Command> command, PlayerIndex playerIdx, EInputState state)
{
	const auto len{ m_KeyBoardCommands.size() };
	for (size_t i = 0; i < len; ++i)
	{
		const KeyBoardCommand* temp =m_KeyBoardCommands[i];
		if (temp != nullptr)
		{
			if (temp->keyBoardButton == keyBoardKey)
			{
				if (typeid(*temp->command) == typeid(*command))
				{
					if (temp->state == state)
					{
						if (temp->playerIdx == playerIdx)
						{
							m_KeyBoardCommands.erase(std::ranges::remove(m_KeyBoardCommands, m_KeyBoardCommands[i]).begin());
							return;
						}
					}
				}
			}
		}
	}
}
