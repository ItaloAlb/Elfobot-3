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
#include <iostream>
#include <thread>

#ifdef _WINDLL

DWORD WINAPI DebugConsole(LPVOID lpParam) {
    // Allocate and attach a console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    Map map = Map();

    // Print debug information
    while (true) {
        Sleep(64);

        // Exit if "0" is pressed
        if (GetAsyncKeyState(0x30) & 0x8000) {
            break;
        }

    }

    // Cleanup
    if (f) fclose(f);
    FreeConsole();

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
