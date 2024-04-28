#include <iostream>
#include <Windows.h>
#include <vector>
#include "globals.hpp"
#include "Cheat.hpp"

#ifdef __DEBUG
void init_console() {
    AllocConsole();
    FILE* f;

    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONIN$", "r", stdin);
}
#endif

DWORD WINAPI InternalMain(HMODULE hMod) {
#ifdef __DEBUG
    init_console();
#endif

    cheat_handler = new Cheat(GAME_MODULE);
    cheat_handler->run();

#ifdef __DEBUG
    FreeConsole();
#endif

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            HANDLE tHandle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InternalMain, hModule, 0, 0);
            if (tHandle) CloseHandle(tHandle);
            else return FALSE;
            break;
    }
    return TRUE;
}