#include <iostream>
#include <Windows.h>
#include <vector>
#include "Key.hpp"
#include "globals.hpp"
#include "cheat.hpp"

#define GAME_MODULE L"sauerbraten.exe"
Cheat* cheat;

void initKeys();
void makeIntersectedEntityJump();
void captureKeys();

DWORD WINAPI InternalMain(HMODULE hMod) {

#ifdef __DEBUG
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
#endif

    initKeys();

    cheat = new Cheat(GAME_MODULE);

    while (true) {
        if (makeemjump)
            makeIntersectedEntityJump();

        captureKeys();
    }

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

void initKeys() {
    for (auto key : keysToCapture)
        keys.push_back(new Key(key));
}

void makeIntersectedEntityJump() {
    Entity* ent = cheat->getIntersectEntity();
    if (ent) {
#ifdef __DEBUG
        std::cout << "\nEntity Address: " << std::hex << ent <<
            //"\nEntity 0x01C8 Address: " << ((uintptr_t)ent + 0x1C8) <<
            "\nEntity 0x01C8 Value: " << *((int32_t*)((uintptr_t)ent + 0x1C8)) <<
            "\nEntity 0x0077 Value:" << *((char*)((uintptr_t)ent + 0x77)) << std::endl;
#endif
        ent->kick_force_up_down = 100;
    }
}

void captureKeys() {
    for (Key* key : keys) {
        key->captureKey();
        if (key->isPressed()) {
            switch (key->getKey()) {
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
                case VK_F8: // make'em jump
#ifdef __DEBUG
                    std::cout << "F8 Pressed" << std::endl;
#endif
                    makeemjump = !makeemjump;
                    break;
            }
        }
    }
}