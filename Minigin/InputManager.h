#pragma once
#include "Command.h"
#include "KeyBoardController.h"
#include "Singleton.h"
#include "Xbox360Controller.h"
#define PlayerIndex unsigned int
namespace dae
{
	enum class EMouseButton
	{
		Left,Middle,Right
	};
	enum class EInputState
	{
		Down,
		Pressed,
		Up
	};
	struct PlayerCommand
	{
		EInputState state{};
		std::shared_ptr<Command> command{};
		PlayerIndex playerIdx{};
		virtual ~PlayerCommand() = default;
	};
	struct ControllerCommand final : public PlayerCommand
	{
		ControllerCommand() = default;
		~ControllerCommand() override = default;
		Xbox360Controller::ControllerButton controllerButton{};
	};
	struct KeyBoardCommand final : public PlayerCommand
	{
		KeyBoardCommand() = default;
		~KeyBoardCommand() override = default;
		SDL_Scancode keyBoardButton{};
		bool isPrevFrameDown{ false };
	};
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager() = default;
		bool ProcessInput();
		void Update() const;

		PlayerIndex AddPlayer(bool IsKeyBoard = false);
		void RemovePlayer(PlayerIndex idx, bool IsKeyBoard = false);

		bool IsPressed(Xbox360Controller::ControllerButton button, PlayerIndex playerIdx) const;
		bool IsPressed(SDL_Scancode scancode, PlayerIndex playerIdx) const;

		bool IsDownThisFrame(Xbox360Controller::ControllerButton button, PlayerIndex playerIdx) const;
		bool IsDownThisFrame(SDL_Scancode scancode, PlayerIndex playerIdx) const;

		bool IsUpThisFrame(Xbox360Controller::ControllerButton button, PlayerIndex playerIdx) const;
		bool IsUpThisFrame(SDL_Scancode scancode, PlayerIndex playerIdx) const;
		

		void AddCommand(Xbox360Controller::ControllerButton button, std::shared_ptr<Command> command, PlayerIndex playerIdx, EInputState state = EInputState::Down);
		void AddCommand(SDL_Scancode keyBoardKey, std::shared_ptr<Command> command, PlayerIndex playerIdx, EInputState state = EInputState::Down);

		void RemoveCommand(Xbox360Controller::ControllerButton button, std::shared_ptr<Command> command, PlayerIndex playerIdx, EInputState state = EInputState::Down);
		void RemoveCommand(SDL_Scancode keyBoardKey, std::shared_ptr<Command> command, PlayerIndex playerIdx, EInputState state = EInputState::Down);


		void ResetManager()
		{
			for (size_t i = 0; i < m_KeyBoardCommands.size(); ++i)
			{
				delete m_KeyBoardCommands[i];
				m_KeyBoardCommands[i] = nullptr;
			}
			for (size_t i = 0; i < m_ConsoleCommands.size(); ++i)
			{
				delete m_ConsoleCommands[i];
				m_ConsoleCommands[i] = nullptr;
			}
			m_ConsoleCommands.clear();
			m_KeyBoardCommands.clear();
			m_pControllers.clear();
			m_pKeyBoards.clear();

		}
	private:
		std::vector<KeyBoardCommand*> m_KeyBoardCommands{};
		std::vector<ControllerCommand*> m_ConsoleCommands{};

		std::vector<std::unique_ptr<Xbox360Controller>> m_pControllers{};
		std::vector<std::unique_ptr<KeyBoardController>> m_pKeyBoards{};

		SDL_Event m_Event{};

	};

}
