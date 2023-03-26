#include "drawing.h"
#include "constant.h"
#include "auto.h"
#include "map.h"

LPCSTR Drawing::lpWindowName = GUI::NAME;
ImVec2 Drawing::vWindowSize = { GUI::WIDTH, GUI::HEIGHT };
ImGuiWindowFlags Drawing::WindowFlags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
bool Drawing::bDraw = true;
char* Drawing::target_window = GUI::TARGET_WINDOW;

void Drawing::Active()
{
	bDraw = true;
}

bool Drawing::isActive()
{
	return bDraw == true;
}

void Drawing::Draw()
{
	if (isActive())
	{
		ImGui::SetNextWindowSize(vWindowSize);
		ImGui::SetNextWindowBgAlpha(1.0f);

		ImGui::Begin(lpWindowName, &bDraw, WindowFlags);
		{
			
			if (ImGui::Checkbox("auto_targeting", &Auto::controller_targeting)) {
				Auto::Callback(&Auto::Targeting, std::ref(Auto::controller_targeting));
			}
			if (ImGui::SliderInt("fishing rod container", &Auto::controller_fishing_rod_container, 0x40, 0x45)) {
				//
			}
			if (ImGui::SliderInt("fishing rod id", &Auto::controller_fishing_rod_id, 0x0, 0x3)) {
				//
			}
			if (ImGui::Checkbox("auto_fishing", &Auto::controller_fishing)) {
				Auto::Callback(&Auto::Fishing, std::ref(Auto::controller_fishing));
			}
			if (ImGui::Checkbox("auto_attacking", &Auto::controller_attacking)) {
				Auto::Callback(&Auto::Attacking, std::ref(Auto::controller_attacking));
			}
		}
		ImGui::End();
	}

	#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
	#endif
}
