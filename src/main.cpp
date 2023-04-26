#include <iostream>
#include <Windows.h>
#include <vector>
#include "Key.hpp"
#include "globals.hpp"
#include "cheat.hpp"

#define GAME_MODULE L"sauerbraten.exe"

void initKeys();

DWORD WINAPI InternalMain(HMODULE hMod) {

#ifdef __DEBUG
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
#endif

    initKeys();

    Cheat* cheat = new Cheat(GAME_MODULE);

    while(true) {
        Entity* ent = cheat->getIntersectEntity();
        if(ent)
            ent->kick_force_up_down = 100;
        for(Key* key : keys) {
            key->captureKey();
            if(key->isPressed()) {
                switch(key->getKey()) {
                    case VK_F5: // freeze ammo
#ifdef __DEBUG
                        std::cout << "F5 Pressed" << std::endl;
#endif
                        freezeAmmo = !freezeAmmo;
                        cheat->freezeAmmo(freezeAmmo);
                        break;
                    case VK_F6: // rapid fire
#ifdef __DEBUG
                        std::cout << "F6 Pressed" << std::endl;
#endif                  
                        rapidFire = !rapidFire;
                        cheat->rapidFire(rapidFire);
                        break;
                    case VK_F7: // kickback force
#ifdef __DEBUG
                        std::cout << "F7 Pressed" << std::endl;
#endif
                        kickbackForce = !kickbackForce;
                        cheat->kickbackForce(kickbackForce);
                        break;
                }
            }
        }
    }

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch(ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            HANDLE tHandle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InternalMain, hModule, 0, 0);
            if(tHandle) CloseHandle(tHandle);
            else return FALSE;
            break;
    }
    return TRUE;
}

void initKeys() {
    for(auto key : keysToCapture)
        keys.push_back(new Key(key));
}

