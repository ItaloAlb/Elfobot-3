#include "drawing.h"


LPCSTR Drawing::lpWindowName = GUI::NAME;
ImVec2 Drawing::vWindowSize = { GUI::WIDTH, GUI::HEIGHT };
ImGuiWindowFlags Drawing::WindowFlags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
bool Drawing::bDraw = true;
char* Drawing::target_window = GUI::TARGET_WINDOW;

HWND hTargetWindow = nullptr;
HWND hOverlayWindow = nullptr;

bool teamBuilderWindow = false;
bool fishingWindow = false;

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

        Auto::UpdateCooldowns(ImGui::GetIO().DeltaTime);

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

            if (ImGui::Checkbox("auto_fishing", &Auto::controller_fishing)) {
                Auto::Callback(&Auto::Fishing, std::ref(Auto::controller_fishing));
            }
            ImGui::Spacing();
            ImGui::PushItemWidth(100);
            ImGui::SliderInt("fishing_rod_container", &Auto::controller_fishing_rod_container, 64, 69);
            ImGui::SliderInt("fishing_rod_id", &Auto::controller_fishing_rod_id, 0, 3);
            ImGui::SliderInt("fishing_cooldown", &Auto::controller_fishing_cooldown, 3, 30);
            ImGui::SliderInt("fishing_wild_pokemon_threshold", &Auto::controller_fishing_wild_pokemon_threshold, 1, 9);
            ImGui::PopItemWidth();


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
            ImGui::SameLine();
            if (ImGui::Checkbox("top_hunt", &Auto::top_hunt)) {
                //
            }
            ImGui::Spacing();
            if (ImGui::Button("fishing", ImVec2(100, 25)))
            {
                fishingWindow = true;
            }
        }
        ImGui::End();

        if (fishingWindow) {
            ImGui::SetNextWindowSize(ImVec2(600, 800));
            ImGui::Begin("Fishing", &fishingWindow, WindowFlags);

            if (Auto::moveset.size() != 12) {
                Auto::moveset.resize(12);
                for (size_t i = 0; i < Auto::moveset.size(); ++i) {
                    // Assign default name as m1, m2, etc.
                    Auto::moveset[i].name = "m" + std::to_string(i + 1);
                }
            }

            // Render each move's properties
            for (size_t i = 0; i < Auto::moveset.size(); i++) {
                Ability& ability = Auto::moveset[i];

                // Display the move name as a static label ("m1", "m2", ...)
                ImGui::Text("%s :", ability.name.c_str());

                // Edit cooldown
                ImGui::PushItemWidth(25); // Define a largura para 50 pixels
                ImGui::InputInt(("Cooldown##" + std::to_string(i)).c_str(), &ability.cooldown, 0);
                ImGui::PopItemWidth();

                // Edit tags: using checkboxes for a fixed set of tags.
                static const char* tagOptions[] = { "deffensive buff", "offensive buff", "single target", "AoE", "heal" };
                bool tagSelections[5] = { false, false, false, false, false };

                // Pre-check the tags that are already selected
                for (size_t t = 0; t < 5; t++) {
                    if (std::find(ability.tags.begin(), ability.tags.end(), tagOptions[t]) != ability.tags.end()) {
                        tagSelections[t] = true;
                    }
                }

                for (size_t t = 0; t < 5; t++) {
                    if (ImGui::Checkbox((std::string(tagOptions[t]) + "##" + std::to_string(i) + "_" + std::to_string(t)).c_str(), &tagSelections[t])) {
                        // Update the tags vector based on user selection
                        if (tagSelections[t]) {
                            if (std::find(ability.tags.begin(), ability.tags.end(), tagOptions[t]) == ability.tags.end())
                                ability.tags.push_back(tagOptions[t]);
                        }
                        else {
                            ability.tags.erase(std::remove(ability.tags.begin(), ability.tags.end(), tagOptions[t]), ability.tags.end());
                        }
                    }
                    ImGui::SameLine();
                }
                ImGui::NewLine();
            }

            // Button to save the moveset to INI file
            if (ImGui::Button("Save Moveset")) {
                std::ofstream file("moveset.ini");
                if (!file.is_open()) {
                    // Handle file open error
                    return;
                }

                for (const auto& ability : Auto::moveset) {
                    // Section header: use the move name (or a unique identifier)
                    file << "[" << ability.name << "]\n";

                    // Save tags as a comma-separated list
                    file << "tags=";
                    for (size_t i = 0; i < ability.tags.size(); ++i) {
                        file << ability.tags[i];
                        if (i < ability.tags.size() - 1) {
                            file << ",";
                        }
                    }
                    file << "\n";

                    // Save cooldown
                    file << "cooldown=" << ability.cooldown << "\n\n";
                }

                file.close();
            }

            if (ImGui::Button("Load Moveset")) {
                std::ifstream file("moveset.ini");
                if (!file.is_open()) {
                    // File couldn't be opened (maybe it doesn't exist)
                    return;
                }
                Auto::moveset.clear();

                std::string line;
                Ability current;
                while (std::getline(file, line)) {
                    if (line.empty())
                        continue;

                    // Check if the line is a section header.
                    if (line.front() == '[' && line.back() == ']') {
                        // If a move is in progress, add it to the moveset.
                        if (!current.name.empty()) {
                            Auto::moveset.push_back(current);
                            current = Ability();
                        }
                        // Remove the '[' and ']' to get the move name.
                        current.name = line.substr(1, line.size() - 2);
                    }
                    else {
                        // Look for key=value pairs.
                        size_t pos = line.find('=');
                        if (pos != std::string::npos) {
                            std::string key = line.substr(0, pos);
                            std::string value = line.substr(pos + 1);
                            if (key == "cooldown") {
                                current.cooldown = std::stoi(value);
                            }
                            else if (key == "tags") {
                                current.tags.clear();
                                std::istringstream iss(value);
                                std::string tag;
                                // Split by comma.
                                while (std::getline(iss, tag, ',')) {
                                    // Trim whitespace.
                                    tag.erase(tag.begin(), std::find_if(tag.begin(), tag.end(), [](unsigned char ch) {
                                        return !std::isspace(ch);
                                        }));
                                    tag.erase(std::find_if(tag.rbegin(), tag.rend(), [](unsigned char ch) {
                                        return !std::isspace(ch);
                                        }).base(), tag.end());
                                    if (!tag.empty()) {
                                        current.tags.push_back(tag);
                                    }
                                }
                            }
                        }
                    }
                }
                // Add the last move if present.
                if (!current.name.empty()) {
                    Auto::moveset.push_back(current);
                }
                file.close();

                // Ensure there are exactly 12 moves. If there are fewer, initialize the rest.
                while (Auto::moveset.size() < 12) {
                    Ability newAbility;
                    newAbility.name = "m" + std::to_string(Auto::moveset.size() + 1);
                    Auto::moveset.push_back(newAbility);
                }
            }
            
            ImGui::End();
        }

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
