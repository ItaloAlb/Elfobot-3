#include "drawing.h"
#include "constant.h"
#include "auto.h"
#include "packet.h"
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
            if (ImGui::SliderInt("fishing rod id", &Auto::controller_fishing_rod_id, 0x0, 0x3)) {
                //
            }
            if (ImGui::Checkbox("auto_fishing", &Auto::controller_fishing)) {
                Auto::Callback(&Auto::Fishing, std::ref(Auto::controller_fishing));
            }
            if (ImGui::Checkbox("auto_attacking", &Auto::controller_attacking)) {
                Auto::Callback(&Auto::Attacking, std::ref(Auto::controller_attacking));
            }

            // Dentro da função Drawing::Draw():
            static char message[256] = ""; // Buffer para o texto
            static int channel = 1;        // Canal padrão (ex: 1 = "Default")

            ImGui::InputText("Message", message, sizeof(message));

            ImGui::InputInt("Channel", &channel);

            // Botão para enviar a mensagem
            if (ImGui::Button("Send Message"))
            {
                if (strlen(message) > 0)
                {
                    SendPacket::Say(message, channel);
                    message[0] = '\0'; // Limpa o campo após enviar
                }
            }
        }
        ImGui::End();
    }

//void Drawing::Draw()
//{
//	if (isActive())
//	{
//		ImGui::SetNextWindowSize(vWindowSize);
//		ImGui::SetNextWindowBgAlpha(1.0f);
//
//		ImGui::Begin(lpWindowName, &bDraw, WindowFlags);
//		{
//			
//			if (ImGui::Checkbox("auto_targeting", &Auto::controller_targeting)) {
//				Auto::Callback(&Auto::Targeting, std::ref(Auto::controller_targeting));
//			}//
//			}
//			if (ImGui::SliderInt("fishing rod id", &Auto::controller_fishing_rod_id, 0x0, 0x3)) {
//				//
//			}
//			if (ImGui::Checkbox("auto_fishing", &Auto::controller_fishing)) {
//				Auto::Callback(&Auto::Fishing, std::ref(Auto::controller_fishing));
//			}
//			if (ImGui::Checkbox("auto_attacking", &Auto::controller_attacking)) {
//				Auto::Callback(&Auto::Attacking, std::ref(Auto::controller_attacking));
//			}
//		}
//		ImGui::End();
//	}

	#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
	#endif
}
