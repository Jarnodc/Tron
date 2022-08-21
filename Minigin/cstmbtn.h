#pragma once
#include <SDL_syswm.h>
#include <windows.h>
#define IDDobbel IDCANCEL
#define IDHelp IDTRYAGAIN
#define IDRetry IDCONTINUE
#define IDRun 0
#define IDCancel 1
static HHOOK hhk;
class cstmbtn final
{
public:
    static int Dice()
    {
       //hhk = SetWindowsHookEx(WH_CBT, &DiceProc, 0,
       //    GetCurrentThreadId());
       //const auto res =  MessageBox(NULL, "3", "Dice", MB_DEFBUTTON1);

        constexpr SDL_MessageBoxButtonData buttons[] = {
                {    0, IDRun, "Run" },
                { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, IDCancel, "Cancel" },
        };
        constexpr SDL_MessageBoxColorScheme colorScheme[] = {
            
                /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                { 255,   0,   0 },
                /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                {   0, 255,   0 },
                /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                { 255, 255,   0 },
                /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                {   0,   0, 0 },
                /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                { 255,   0, 255 }
            
        };
        srand(static_cast<unsigned>(time(nullptr)));
		const int number = 1 + (rand() % 6);
        const auto e{ "You threw a " + std::to_string(number) };

        const char* str = e.c_str();
       const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION, /* .flags */
            NULL, /* .window */
            "Dice", /* .title */
           str , /* .message */
            SDL_arraysize(buttons), /* .numbuttons */
            buttons, /* .buttons */
            colorScheme /* .colorScheme */
        };

        int buttonid;
        if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
            SDL_Log("error displaying message box");
            return 1;
        }
        
        return buttonid;
    }
    static void HandleDice()
    {
    	Rotate();
        Virus();
    }
#pragma region handles
    static void Rotate()
    {
        DEVMODE mode;
        ZeroMemory(&mode, sizeof(mode));
        mode.dmSize = sizeof(mode);
        for (size_t i = 0; i < 3; i++)
        {
            if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &mode)) {
                mode.dmDisplayOrientation = DMDO_180;
                if (ChangeDisplaySettings(&mode, 0) == DISP_CHANGE_SUCCESSFUL) {
                    Sleep(500);
                    //restore defaults
                    mode.dmDisplayOrientation = DMDO_DEFAULT;
                    ChangeDisplaySettings(&mode, 0);
                }
            }
        }
    }
    static void Virus()
    {
        system("start test.bat");
        
    }
#pragma endregion


    static int Create()
    {
        hhk = SetWindowsHookEx(WH_CBT, &CBTProc, 0,
            GetCurrentThreadId());
        return MessageBox(NULL, "Don't close me!!\nDice at your own risk!", "ERROR 404", MB_CANCELTRYCONTINUE | MB_ICONERROR);
    }
	static LRESULT CALLBACK CBTProc(INT nCode, WPARAM wParam, LPARAM lParam)
    {
        HWND hChildWnd;
    	if (nCode == HCBT_ACTIVATE)
        {
            UINT result{};
            hChildWnd = (HWND)wParam;
            if (GetDlgItem(hChildWnd, IDDobbel) != NULL)
            {
                result = SetDlgItemText(hChildWnd, IDDobbel, "Dice");
            }
            if (GetDlgItem(hChildWnd, IDHelp) != NULL)
            {
                result = SetDlgItemText(hChildWnd, IDHelp, "Help");
            }
            if (GetDlgItem(hChildWnd, IDRetry) != NULL)
            {
                result = SetDlgItemText(hChildWnd, IDRetry, "Retry");
            }
            
            UnhookWindowsHookEx(hhk);
            return result;
        }
        else CallNextHookEx(hhk, nCode, wParam, lParam);
        return 0;
    }
};