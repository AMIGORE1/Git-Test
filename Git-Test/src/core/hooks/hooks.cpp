#include "hooks.h"

bool hooks::Init()
{
    if (MH_Initialize() != MH_OK)
        return false;
    if (!Init_Hooks())
        return false;


    MH_EnableHook(MH_ALL_HOOKS);
    return true;
}


bool hooks::Init_Hooks()
{

    uint8_t* openGlBase = (uint8_t*)GetModuleHandle("opengl32.dll");
    uint8_t* WglAddrs = openGlBase + 0x407D0;

    if (MH_CreateHook(WglAddrs, &hWglSwapBuffer, reinterpret_cast<LPVOID*>(&oWglSwapBuffer)) != MH_OK) {
        return false;
    }
    return true;
}


void hooks::Release()
{
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
    ReleaseImGui();
}