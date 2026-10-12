#include "wgl.h"

LRESULT __stdcall Wnd_Proc_Hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (Menu::IsOpen)
    {
        ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

        return 1;
    }
    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}


BOOL __stdcall hWglSwapBuffer(HDC device)
{
    if (!IsImGuiInit)
    {
        window = WindowFromDC(device);
        if (window)
        {
            oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Wnd_Proc_Hook)));

            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;



            ImGui_ImplWin32_Init(window);
            ImGui_ImplOpenGL2_Init();

            IsImGuiInit = true;
        }
    }

    if (IsImGuiInit)
    {
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            Menu::IsOpen = !Menu::IsOpen;
        }
        if(Menu::IsOpen)
            Menu::Render();

        EntityManager::Get().Update();
        vis::Update();
        Aim::Update();
        ImGui::Render();
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    }
    return oWglSwapBuffer(device);

}

void ReleaseImGui()
{
    if (!IsImGuiInit)
        return;

    IsImGuiInit = false;

    if (window && oWndProc)
    {
        SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(oWndProc));
        oWndProc = nullptr;
    }

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    window = nullptr;
}