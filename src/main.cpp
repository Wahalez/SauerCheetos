#include <iostream>
#include <Windows.h>
#include <vector>
#include "Key.hpp"
#include "globals.hpp"
#include "cheat.hpp"

#define GAME_MODULE L"sauerbraten.exe"
Cheat *cheat;

void initKeys();
void makeIntersectedEntityJump();
void autoShootEnemies();
void captureKeys();

DWORD WINAPI InternalMain(HMODULE hMod)
{

#ifdef __DEBUG
    AllocConsole();
    FILE *f;

    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONIN$", "r", stdin);

    std::cout << "---------CHEAT---------\n"
              << "F5: Freeze Ammo\n"
              << "F6: Rapid Fire\n"
              << "F7: KickBack Force\n"
              << "F8: Make'em Jump\n"
              << "F9: Auto Shoot Enemies\n"
                 "-----------------------"
              << std::endl;
#endif

    initKeys();

    cheat = new Cheat(GAME_MODULE);

    while (true)
    {
        if (makeemjump)
            makeIntersectedEntityJump();

        if (autoShoot)
            autoShootEnemies();

        captureKeys();
        Sleep(50);
    }

#ifdef __DEBUG
    FreeConsole();
#endif

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        HANDLE tHandle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InternalMain, hModule, 0, 0);
        if (tHandle)
            CloseHandle(tHandle);
        else
            return FALSE;
        break;
    }
    return TRUE;
}

void initKeys()
{
    for (auto key : keysToCapture)
        keys.push_back(new Key(key));
}

void autoShootEnemies()
{
    static bool isEnabled = false;

    if (isEnabled)
    {
        player->shoot = false;
        isEnabled = false;
    }

    Entity *ent = cheat->getIntersectEntity();
    if (ent)
    {
        uintptr_t first_middle_man_pointer_address = (uintptr_t)ent + 0xD8;
        uintptr_t *first_middle_man_pointer = (uintptr_t *)first_middle_man_pointer_address;

        if (first_middle_man_pointer == nullptr)
            return;

        uintptr_t second_middle_man_pointer_address = *first_middle_man_pointer + 0x18;

        uintptr_t *second_middle_man_pointer = (uintptr_t *)second_middle_man_pointer_address;

        if (second_middle_man_pointer == nullptr)
            return;

        const char *object_str_type = (const char *)*second_middle_man_pointer;

        if (object_str_type == nullptr)
            return;

#ifdef __DEBUG
        std::cout << "object str type: " << object_str_type << std::endl;
#endif

        const char *type_monster = "monster";
        const char *type_ogro = "ogro";

        if (strstr(object_str_type, type_monster) != nullptr || strstr(object_str_type, type_ogro) != nullptr)
        {
            player->shoot = true;
            isEnabled = true;
        }
    }
}

void makeIntersectedEntityJump()
{
    static Entity *previous_ent = nullptr;
    Entity *ent = cheat->getIntersectEntity();
    if (ent)
    {
#ifdef __DEBUG
        if (ent != previous_ent)
        {
            previous_ent = ent;
            std::cout << "\nEntity Address: " << std::hex << ent << std::endl;
        }
#endif
        ent->kick_force_up_down = 100;
    }
}

void captureKeys()
{
    for (Key *key : keys)
    {
        key->captureKey();
        if (key->isPressed())
        {
            switch (key->getKey())
            {
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
            case VK_F9: // auto shoot enemies
#ifdef __DEBUG
                std::cout << "F9 Pressed" << std::endl;
#endif
                autoShoot = !autoShoot;
                break;
            }
        }
    }
}