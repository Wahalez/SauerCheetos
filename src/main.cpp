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
    freopen_s(&f, "CONIN$", "r", stdin);

    std::cout << "---------CHEAT---------\n" <<
        "F5: Freeze Ammo\n" <<
        "F6: Rapid Fire\n" <<
        "F7: KickBack Force\n" <<
        "F8: Make'em Jump & entity type finder\n" <<
        "F9: Change Entity type finder offset\n" <<
        "-----------------------" << std::endl;
#endif

    initKeys();

    cheat = new Cheat(GAME_MODULE);

    while(true) {
        if(makeemjump)
            makeIntersectedEntityJump();

        captureKeys();
    }

#ifdef __DEBUG
    FreeConsole();
#endif

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

void makeIntersectedEntityJump() {
    static Entity* previous_ent = nullptr;
    Entity* ent = cheat->getIntersectEntity();
    if(ent) {
#ifdef __DEBUG
        if(ent != previous_ent) {
            previous_ent = ent;
            std::cout << "\nEntity Address: " << std::hex << ent <<
                "\nEntity " << *type_offset << " Value: " <<
                *((int32_t*)((uintptr_t)ent + *type_offset)) << std::endl;
        }
#endif
        ent->kick_force_up_down = 100;
    }
}

void captureKeys() {
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
                case VK_F8: // make'em jump
#ifdef __DEBUG
                    std::cout << "F8 Pressed" << std::endl;
#endif
                    makeemjump = !makeemjump;
                    break;
                case VK_F9: // entity type finder offset change
#ifdef __DEBUG
                    std::cout << "F9 Pressed" << std::endl;
#endif
                    std::cin >> std::hex >> *type_offset;
                    break;
            }
        }
    }
}