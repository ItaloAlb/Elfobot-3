#include "drawing.h"
#include "control_variable.h"
#include "callback.h"
#include "auto.h"
#include "constant.h"

LPCSTR Drawing::lpWindowName = "Elfobot 3";
ImVec2 Drawing::vWindowSize = { GUI::WIDTH, GUI::HEIGHT };
ImGuiWindowFlags Drawing::WindowFlags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
bool Drawing::bDraw = true;

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
			if (ImGui::Checkbox("auto_targeting", &auto_targeting)) {
				Callback::Call(Auto::Targeting, std::ref(auto_targeting));
			}

			if (ImGui::Checkbox("auto_fishing", &auto_fishing)) {
				//Callback::Call(Auto::Fishing, std::ref(map), std::ref(auto_fishing));
			}

			if (ImGui::Checkbox("auto_attacking", &auto_attacking)) {
				Callback::Call(Auto::Attacking, std::ref(auto_attacking));
			}
		}
		ImGui::End();
	}

	#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
	#endif
}
