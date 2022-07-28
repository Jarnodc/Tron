#include "MiniginPCH.h"
#include "KeyBoardController.h"

class KeyBoardController::KeyBoardControllerImpl final
{
	bool m_CurrentState[256]{};
	bool m_PreviousState[256]{};
	
	int m_ControllerIdx{};
public:
	explicit KeyBoardControllerImpl(int controllerIdx)
		:m_ControllerIdx(controllerIdx)
	{
		ZeroMemory(&m_CurrentState, sizeof(bool) * 256);
		ZeroMemory(&m_PreviousState, sizeof(bool) * 256);
	}
	~KeyBoardControllerImpl() = default;

	void Update()
	{
		CopyMemory(&m_CurrentState,&m_PreviousState, sizeof(bool) * 256);
		ZeroMemory(&m_PreviousState, sizeof(bool) * 256);

		const Uint8* pState = SDL_GetKeyboardState(nullptr);
		for (size_t i = 0; i < 256; ++i)
		{
			m_CurrentState[i] = pState[i];
		}
	}

	bool IsDown(SDL_Scancode scancode)const
	{
		return m_CurrentState[scancode];
	}
	bool IsUp(SDL_Scancode scancode)const
	{
		return m_PreviousState[scancode] && !m_CurrentState[scancode];
	}
	bool IsPressed(SDL_Scancode scancode)const
	{
		return !m_PreviousState[scancode] && m_CurrentState[scancode];
	}


};

KeyBoardController::KeyBoardController(int controllerIdx)
	:m_pImpl(new KeyBoardControllerImpl(controllerIdx))
{
}

KeyBoardController::~KeyBoardController()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}

void KeyBoardController::Update() const
{
	m_pImpl->Update();
}

bool KeyBoardController::IsDown(SDL_Scancode scancode) const
{
	return m_pImpl->IsDown(scancode);
}

bool KeyBoardController::IsUp(SDL_Scancode scancode) const
{
	return m_pImpl->IsUp(scancode);
}

bool KeyBoardController::IsPressed(SDL_Scancode scancode) const
{
	return m_pImpl->IsPressed(scancode);
}
