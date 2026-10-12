#include "menu.h"
#include "../../../ext/imgui/imgui.h"

bool Aimbot = false;
void Menu::Render()
{
	ImGui::SetNextWindowSize({ 460, 500 }, ImGuiCond_Once);
	ImGuiWindowFlags window_flags =
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse;

	if (ImGui::Begin("Agyzak", &IsOpen, window_flags))
	{
		ImGui::Checkbox("AimBot", &Aimbot);
	}
	ImGui::End();
}