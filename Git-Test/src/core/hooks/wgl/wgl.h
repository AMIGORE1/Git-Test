#pragma once
#include <Windows.h>
#include <GL/gl.h>
#include "../../../../ext/imgui/imgui_impl_win32.h"
#include "../../../../ext/imgui/imgui_impl_opengl2.h"
#include "../../../../ext/imgui/imgui.h"

#include "../../../sdk/entityManager/entityManager.h"
#include "../../features/aim/aim.h"
#include "../../features/visual/visual.h"
#include "../../../sdk/mem/mem.h"
#include "../../menu/menu.h"


inline WNDPROC oWndProc = nullptr;
inline HWND window = nullptr;
inline bool IsImGuiInit = false;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWid, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall Wnd_Proc_Hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

typedef BOOL(__stdcall* tWglSwapBuffer)(HDC device);
inline tWglSwapBuffer oWglSwapBuffer = nullptr;
BOOL __stdcall hWglSwapBuffer(HDC device);

void ReleaseImGui();