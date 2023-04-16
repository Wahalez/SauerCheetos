#include <Windows.h>
#include <iostream>

#define __DEBUG
#define __DEBUG_CHECK_RUN

DWORD WINAPI InternalMain(HMODULE hMod) {

#ifdef __DEBUG
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
#endif

#ifdef __DEBUG_CHECK_RUN
    while (true) {
        std::cout << "running" << std::endl;
    }
#endif

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