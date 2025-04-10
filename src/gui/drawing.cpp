#include "drawing.h"
#include "constant.h"
#include "auto.h"
#include "packet.h"
#include "map.h"
#include "util.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "config.h"
#include "ui.h"


LPCSTR Drawing::lpWindowName = GUI::NAME;
ImVec2 Drawing::vWindowSize = { GUI::WIDTH, GUI::HEIGHT };
ImGuiWindowFlags Drawing::WindowFlags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
bool Drawing::bDraw = true;
char* Drawing::target_window = GUI::TARGET_WINDOW;

HWND hTargetWindow = nullptr;
HWND hOverlayWindow = nullptr;

bool teamBuilderWindow = false;

static bool     showDetails[6] = { true, true, true, true, true, true };

const int MIN_AOE = 2;
const int MAX_AOE = 4;

float cooldownRemaining[6] = { 0, 0, 0, 0, 0, 0 };

void UpdateWindowHandles() {
    if (!hTargetWindow) {
        hTargetWindow = FindWindowA(nullptr, "PokeBRO"); // Nome da janela do .exe
    }
    if (!hOverlayWindow) {
        hOverlayWindow = FindWindowA(nullptr, GUI::NAME); // Nome da janela do ImGui
    }
}

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
        UpdateWindowHandles();

        bool isTargetActive = (GetForegroundWindow() == hTargetWindow);

        if (hOverlayWindow && hTargetWindow) {
            SetWindowPos(
                hOverlayWindow,
                isTargetActive ? HWND_TOPMOST : HWND_NOTOPMOST,
                0, 0, 0, 0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE
            );
        }

        ImGui::SetNextWindowSize(vWindowSize);
        ImGui::SetNextWindowBgAlpha(1.0f);

        ImGui::Begin(lpWindowName, nullptr, WindowFlags);
        {
            if (ImGui::Checkbox("auto_targeting", &Auto::controller_targeting)) {
                Auto::Callback(&Auto::Targeting, std::ref(Auto::controller_targeting));
            }
            ImGui::SameLine(150);
            if (ImGui::Checkbox("auto_attacking", &Auto::controller_attacking)) {
                Auto::Callback(&Auto::Attacking, std::ref(Auto::controller_attacking));
            }
            if (ImGui::Checkbox("auto_loving", &Auto::controller_loving)) {
                Auto::Callback(&Auto::Loving, std::ref(Auto::controller_loving));
            }
            ImGui::SameLine(150);
            if (ImGui::Checkbox("auto_egg_loving", &Auto::controller_egg_loving)) {
                Auto::Callback(&Auto::Egg_Loving, std::ref(Auto::controller_egg_loving));
            }
            if (ImGui::Checkbox("wasd_move", &Auto::is_wasd_move)) {

            }
            ImGui::SameLine(150);
            if (ImGui::Checkbox("auto_connecting", &Auto::controller_connecting)) {
                Auto::Callback(&Auto::Connecting, std::ref(Auto::controller_connecting));
            }

            //if (ImGui::Button("full_attack", ImVec2(100, 25)))
            //{
            //    
            //}

            //if (ImGui::Button("balanced", ImVec2(100, 25)))
            //{
            //    *POINTER::FIGHTING_MODE = 2;
            //    SendPacket::FightMode(*POINTER::FIGHTING_MODE, 0, 0);
            //}
            //
            //if (ImGui::Button("full_defensive", ImVec2(100, 25)))
            //{
            //    *POINTER::FIGHTING_MODE = 3;
            //    SendPacket::FightMode(*POINTER::FIGHTING_MODE, 0, 0);
            //}
            ImGui::Spacing();
            for (int i = 0; i < 6; i++) {
                if (Auto::cooldownActive[i]) {
                    float dt = ImGui::GetIO().DeltaTime;
                    Auto::cooldownRemaining[i] -= dt;
                    if (Auto::cooldownRemaining[i] <= 0.0f) {
                        Auto::cooldownRemaining[i] = 0.0f;
                        Auto::cooldownActive[i] = false;
                    }

                    float progress = Auto::cooldownRemaining[i] / Auto::iCooldown[i];
                    //ImGui::ProgressBar(progress, ImVec2(200, 0));
                    ImGui::SameLine();
                    ImGui::Text("pkm %d cd: %.1f s", i + 1, Auto::cooldownRemaining[i]);
                }
            }

            ImGui::Spacing();
            if (ImGui::Button("team_builder", ImVec2(100, 25)))
            {
                teamBuilderWindow = true;
            }
            ImGui::SameLine();
            if (ImGui::Button("team_update", ImVec2(100, 25)))
            {
                for (int i = 0; i < 6; i++) {
                    Auto::slot[i] = Util::GetValueFromOffsetChain(ADDRESS::POKEMON_SLOT, OFFSET::POKEMON_SLOT[i]);
                }
            }
            ImGui::Spacing();
            if (ImGui::Checkbox("top_hunt", &Auto::top_hunt)) {
                //
            }
        }
        ImGui::End();

        if (teamBuilderWindow) {
            ImGui::SetNextWindowSize(ImVec2(350, 500));
            ImGui::Begin("Team Builder", &teamBuilderWindow, WindowFlags);
            if (ImGui::BeginTable("PokemonsTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
            {
                // Precisamos de 3 linhas para exibir 6 pokemons (2 por linha)
                for (int row = 0; row < 3; row++)
                {
                    ImGui::TableNextRow();
                    for (int col = 0; col < 2; col++)
                    {
                        ImGui::TableSetColumnIndex(col);

                        int i = row * 2 + col; // Índice do pokemon (0 a 5)

                        // Usamos PushID/PopID para isolar IDs dentro deste "slot" de Pokémon
                        ImGui::PushID(i);

                        // Botão de "seta". Se clicado, alterna a flag de expandir/colapsar
                        if (ImGui::ArrowButton("arrow", showDetails[i] ? ImGuiDir_Down : ImGuiDir_Right))
                        {
                            showDetails[i] = !showDetails[i];
                        }
                        ImGui::SameLine();

                        // Título do Pokémon
                        ImGui::Text("Pokemon %d", i + 1);

                        // Se estiver expandido, mostramos os campos
                        if (showDetails[i])
                        {
                            // Para facilitar a formatação, podemos criar espaçamentos ou usar colunas internas
                            // mas aqui faremos de forma simples, linha a linha.

                            // Linha "buff"
                            ImGui::Text("buff");
                            ImGui::SameLine(80); // Ajuste o espaçamento como preferir
                            ImGui::PushItemWidth(50);
                            ImGui::InputText("##buff", Auto::buff[i], IM_ARRAYSIZE(Auto::buff[i]));
                            ImGui::PopItemWidth();

                            // Linha "protect"
                            ImGui::Text("protect");
                            ImGui::SameLine(80);
                            ImGui::PushItemWidth(50);
                            ImGui::InputText("##protect", Auto::protect[i], IM_ARRAYSIZE(Auto::protect[i]));
                            ImGui::PopItemWidth();

                            for (int j = 0; j < Auto::aoeCount[i]; j++) {
                                ImGui::Text("aoe%d", j + 1);
                                ImGui::SameLine(80);
                                ImGui::PushItemWidth(50);
                                ImGui::InputText(("##aoe" + std::to_string(j + 1)).c_str(), Auto::aoe[i][j], IM_ARRAYSIZE(Auto::aoe[i][j]));
                                ImGui::PopItemWidth();
                            }

                            // Botão "cooldown"
                            ImGui::Text("cooldown");
                            ImGui::SameLine(80);
                            ImGui::PushItemWidth(50);
                            if (ImGui::InputText("##cooldown", Auto::cooldown[i], IM_ARRAYSIZE(Auto::cooldown[i]))) {
                                try {
                                    Auto::iCooldown[i] = std::stoi(Auto::cooldown[i]);
                                }
                                catch (...) {
                                    Auto::iCooldown[i] = 0;
                                }
                            }
                            ImGui::PopItemWidth();

                            if (ImGui::Button("add") && Auto::aoeCount[i] < MAX_AOE) {
                                Auto::aoeCount[i]++;
                            }
                            ImGui::SameLine();
                            if (ImGui::Button("remove") && Auto::aoeCount[i] > MIN_AOE) {
                                Auto::aoeCount[i]--;
                            }
                        }

                        ImGui::PopID(); // Fim do ID para este Pokémon
                    }
                }
                ImGui::EndTable();
            }
            ImGui::Spacing();
            if (ImGui::Button("save", ImVec2(165, 25)))
            {
                std::ofstream file("config.ini");
                if (file.is_open())
                {
                    // Iterate over each Pokemon
                    for (int i = 0; i < 6; i++)
                    {
                        file << "[Pokemon" << i + 1 << "]\n";
                        file << "buff=" << Auto::buff[i] << "\n";
                        file << "protect=" << Auto::protect[i] << "\n";
                        // Save each AOE entry according to the current count.
                        for (int j = 0; j < Auto::aoeCount[i]; j++)
                        {
                            file << "aoe" << j + 1 << "=" << Auto::aoe[i][j] << "\n";
                        }
                        file << "cooldown=" << Auto::cooldown[i] << "\n\n";
                    }
                    file.close();
                }
                else
                {
                    ImGui::OpenPopup("Erro ao salvar");
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("load", ImVec2(160, 25)))
            {
                std::ifstream file("config.ini");
                if (file.is_open())
                {
                    std::string line;
                    int currentIndex = -1;
                    // Reset each Pokemon's aoeCount to the minimum value.
                    for (int i = 0; i < 6; i++)
                    {
                        Auto::aoeCount[i] = MIN_AOE;
                    }
                    while (std::getline(file, line))
                    {
                        if (line.empty())
                            continue;
                        // A section header, e.g. [Pokemon1]
                        if (line[0] == '[')
                        {
                            size_t pos = line.find("Pokemon");
                            if (pos != std::string::npos)
                            {
                                size_t pos2 = line.find("]", pos);
                                if (pos2 != std::string::npos)
                                {
                                    std::string numStr = line.substr(pos + 7, pos2 - pos - 7);
                                    currentIndex = std::stoi(numStr) - 1;
                                }
                            }
                        }
                        else
                        {
                            // Key-value pair, e.g. key=value
                            size_t eqPos = line.find('=');
                            if (eqPos != std::string::npos && currentIndex >= 0 && currentIndex < 6)
                            {
                                std::string key = line.substr(0, eqPos);
                                std::string value = line.substr(eqPos + 1);

                                if (key == "buff")
                                {
                                    strncpy_s(Auto::buff[currentIndex], sizeof(Auto::buff[currentIndex]), value.c_str(), _TRUNCATE);
                                }
                                else if (key == "protect")
                                {
                                    strncpy_s(Auto::protect[currentIndex], sizeof(Auto::protect[currentIndex]), value.c_str(), _TRUNCATE);
                                }
                                else if (key == "cooldown")
                                {
                                    strncpy_s(Auto::cooldown[currentIndex], sizeof(Auto::cooldown[currentIndex]), value.c_str(), _TRUNCATE);
                                    try {
                                        Auto::iCooldown[currentIndex] = std::stoi(Auto::cooldown[currentIndex]);
                                    }
                                    catch (...) {
                                        Auto::iCooldown[currentIndex] = 0;
                                    }
                                }
                                else if (key.rfind("aoe", 0) == 0)
                                {
                                    // The key starts with "aoe". Extract the index number.
                                    int idx = std::stoi(key.substr(3)) - 1; // "aoe1" -> idx 0, etc.
                                    if (idx >= 0 && idx < MAX_AOE)
                                    {
                                        strncpy_s(Auto::aoe[currentIndex][idx], sizeof(Auto::aoe[currentIndex][idx]), value.c_str(), _TRUNCATE);
                                        // Adjust aoeCount if necessary.
                                        if (idx + 1 > Auto::aoeCount[currentIndex])
                                            Auto::aoeCount[currentIndex] = idx + 1;
                                    }
                                }
                            }
                        }
                    }
                    file.close();
                }
                else
                {
                    ImGui::OpenPopup("Erro ao carregar");
                }
            }
            ImGui::End(); // Fim da janela
        }
    }

	#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
	#endif
}
