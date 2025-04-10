//#include "ui.h"
//
//#ifdef _WINDLL
//
//BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
//{
//    if (fdwReason == DLL_PROCESS_ATTACH)
//    {
//        DisableThreadLibraryCalls(hinstDLL);
//        CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)UI::Render, nullptr, NULL, nullptr);
//        return TRUE;
//    }
//
//    return TRUE;
//}
//
//#else
//
//
//int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
//{
//    UI::Render();
//
//    return 0;
//}
//
//#endif

#include "ui.h"
#include "map.h"
#include <windows.h>
#include "util.h"
#include "packet.h"
#include "constant.h"
#include <iostream>
#include <thread>
#include <cstdint>
#include <string>
#include "auto.h"

#ifdef _WINDLL

DWORD WINAPI DebugConsole(LPVOID lpParam) {
    // Allocate and attach a console
    //AllocConsole();

    // Redireciona a sa�da padr�o para o console
    //FILE* fp;
    //freopen_s(&fp, "CONOUT$", "w", stdout);
    // Print debug information 
    while (true) {
        Sleep(32);
        if (Auto::is_wasd_move) {
            if (GetAsyncKeyState('W') & 1) {
                SendPacket::Step(STEP::UP);
            }
            if (GetAsyncKeyState('A') & 1) {
                SendPacket::Step(STEP::LEFT);
            }
            if (GetAsyncKeyState('S') & 1) {
                SendPacket::Step(STEP::DOWN);
            }
            if (GetAsyncKeyState('D') & 1) {
                SendPacket::Step(STEP::RIGHT);
            }
        }
        //if (GetAsyncKeyState('E') & 1) {
        //    std::cout << ADDRESS::EXHAUSTED << std::endl;
        //    std::cout << *(int*)ADDRESS::EXHAUSTED << std::endl;
        //}

        if (GetAsyncKeyState(VK_XBUTTON1) & 1) {
            *POINTER::FIGHTING_MODE = 1;
            SendPacket::FightMode(*POINTER::FIGHTING_MODE, 0, 0);
        }

        if (GetAsyncKeyState(VK_XBUTTON2) & 1) {
            *POINTER::FIGHTING_MODE = 3;
            SendPacket::FightMode(*POINTER::FIGHTING_MODE, 0, 0);
        }

        if (Auto::top_hunt) {
            for (int i = 0; i < 6; i++) {
                // Check if key '1' + i is pressed.
                // GetAsyncKeyState returns a short, so we test the least significant bit.
                if ((GetAsyncKeyState('1' + i) & 1) && !Auto::cooldownActive[i]) {
                    std::string cmd = std::string(COMMANDS::THROW) + " " + std::to_string(Auto::slot[i]);
                    SendPacket::Say(cmd.c_str(), 1);

                    Sleep(COOLDOWN::SEND_PACKET);
                    SendPacket::Say(COMMANDS::LOVE, 1);

                    // Send buff text
                    if (Auto::buff[i][0] != '\0' && Auto::buff[i][0] == 'm') {
                        SendPacket::Say(Auto::buff[i], 1);
                        SendPacket::Say(Auto::buff[i], 1);
                        Sleep(COOLDOWN::SEND_PACKET);
                    }
                    // Send protect text
                    if (Auto::protect[i][0] != '\0' && Auto::protect[i][0] == 'm') {

                        SendPacket::Say(Auto::protect[i], 1);
                        SendPacket::Say(Auto::protect[i], 1);
                        Sleep(COOLDOWN::SEND_PACKET);
                    }

                    *POINTER::FIGHTING_MODE = 1;
                    SendPacket::FightMode(1, 0, 0);

                    // Send each AOE text based on the current count for this Pokemon
                    for (int j = 0; j < Auto::aoeCount[i]; j++) {
                        if (Auto::aoe[i][j][0] != '\0' && Auto::aoe[i][j][0] == 'm') {
                            SendPacket::Say(Auto::aoe[i][j], 1);
                            SendPacket::Say(Auto::aoe[i][j], 1);
                        }
                    }

                    *POINTER::FIGHTING_MODE = 3;
                    SendPacket::FightMode(3, 0, 0);

                    Auto::cooldownActive[i] = true;
                    Auto::cooldownRemaining[i] = Auto::iCooldown[i];
                }
            }
        }
    }

    //FreeConsole();

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinstDLL);

        // Create the UI thread
        CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)UI::Render, nullptr, NULL, nullptr);

        // Create the debugging console thread
        CreateThread(nullptr, NULL, DebugConsole, nullptr, NULL, nullptr);

        return TRUE;
    }

    return TRUE;
}

#else

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
    UI::Render();
    return 0;
}

#endif
