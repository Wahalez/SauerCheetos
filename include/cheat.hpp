#pragma once
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <vector>
#include "globals.hpp"
#include "Key.hpp"
#include "Entity.hpp"

typedef Entity *(__cdecl *intersectClosest)(Entity *, void *, Entity *, float *);

class Cheat
{
public:
    Cheat(const wchar_t *);
    ~Cheat();
    void run();

private:
    void init_cheat_state();
    void init_capture_keys();
    void init_code_buffers();
    void load_original_codes();
    void load_original_health_code();
    void load_original_ammo_code();
    void load_original_Kickback_force_code();
    void load_original_rapid_fire_code();
    void handle_keys_capture();
    void handle_key_capture(Key *);
    void alter_code_with_nop_bytes(bool enabled, uintptr_t code_offset, size_t bytes_count, BYTE *original_code);
    void handle_freeze_health();
    void handle_freeze_ammo();
    void handle_rapid_fire();
    void handle_kickbackForce();
    void handle_makeemjump();
    void handle_auto_shoot();
    Entity *getIntersectEntity();
    bool is_monster_type(std::string);

#ifdef __DEBUG
    void printCheat();
    void printBytes(BYTE *bytes, size_t size);
#endif

private:
    // cheat state
    bool freezeHealth;
    bool freezeAmmo;
    bool rapidFire;
    bool makeemjump;
    bool auto_shoot;
    bool kickback_force;

private:
    std::vector<Key *> keys_capture;

    Entity *player;

    uintptr_t moduleBase;

    // health code responsible for subtracting health when hit
    uintptr_t healthCodeStart;
    BYTE *originalHealthCode;

    // ammo code responsible for subtracting ammo when shooting
    uintptr_t ammoCodeStart;
    BYTE *originalAmmoCode;

    // code responsible for time delay between shots
    uintptr_t rapidFireStart;
    BYTE *originalRapidFireCode;

    // code responsible for kickback force when shooting
    uintptr_t kickbackRightLeft1;
    uintptr_t kickbackRightLeft2;
    uintptr_t kickbackBackForward1;
    uintptr_t kickbackBackForward2;
    uintptr_t kickbackUpDown1;
    uintptr_t kickbackUpDown2;
    BYTE *originalKickbackRightLeftCode1;
    BYTE *originalKickbackRightLeftCode2;
    BYTE *originalKickbackBackForwardCode1;
    BYTE *originalKickbackBackForwardCode2;
    BYTE *originalKickbackUpDownCode1;
    BYTE *originalKickbackUpDownCode2;

    intersectClosest intersect_function;
};