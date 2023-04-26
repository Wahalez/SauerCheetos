#pragma once

#include "windows.h"
#include "globals.hpp"
#include "Entity.hpp"
#include <iostream>
#include <iomanip>

#define __DEBUG

#define AMMO_CODE_BYTES_COUNT 8
#define AMMO_CODE_OFFSET 0x1DB5E0

#define RAPID_FIRE_BYTES_COUNT 7
#define RAPID_FIRE_OFFSET 0x1DBA02

#define KICKBACK_RIGHT_LEFT_1_OFFSET 0x1DB759
#define KICKBACK_RIGHT_LEFT_1_BYTES 6
#define KICKBACK_RIGHT_LEFT_2_OFFSET 0x1DB76F
#define KICKBACK_RIGHT_LEFT_2_BYTES 6

#define KICKBACK_BACK_FORWARD_1_OFFSET 0x1DB763
#define KICKBACK_BACK_FORWARD_1_BYTES 6
#define KICKBACK_BACK_FORWARD_2_OFFSET 0x1DB775
#define KICKBACK_BACK_FORWARD_2_BYTES 6

#define KICKBACK_UP_DOWN_1_OFFSET 0x1DB769
#define KICKBACK_UP_DOWN_1_BYTES 6
#define KICKBACK_UP_DOWN_2_OFFSET 0x1DB77B
#define KICKBACK_UP_DOWN_2_BYTES 6

#define STATIC_PLAYER_POINTER_OFFSET 0x2A2560

#define WORLDPOS_OFFSET 0x32BEF8
#define INTERSECTDIST_OFFSET 0x26E54C

#define INTERSECTDIST_FUNCTION_OFFSET 0x1DB2A0

class Cheat {
private:
    uintptr_t moduleBase;

    void initCodeBuffers();

    // ammo code responsible for subtracting ammo when shooting
    uintptr_t ammoCodeStart;
    BYTE* originalAmmoCode;
    void loadOriginalAmmoCode();

    // code responsible for time delay between shots
    uintptr_t rapidFireStart;
    BYTE* originalRapidFireCode;
    void loadOriginalRapidFireCode();

    // code responsible for kickback force when shooting
    uintptr_t kickbackRightLeft1;
    uintptr_t kickbackRightLeft2;
    uintptr_t kickbackBackForward1;
    uintptr_t kickbackBackForward2;
    uintptr_t kickbackUpDown1;
    uintptr_t kickbackUpDown2;
    BYTE* originalKickbackRightLeftCode1;
    BYTE* originalKickbackRightLeftCode2;
    BYTE* originalKickbackBackForwardCode1;
    BYTE* originalKickbackBackForwardCode2;
    BYTE* originalKickbackUpDownCode1;
    BYTE* originalKickbackUpDownCode2;
    void loadOriginalKickbackForceCode();

    void alterCode_nop(bool enabled, uintptr_t code_offset, size_t bytes, BYTE* originalCode);

#ifdef __DEBUG
    void printBytes(BYTE* bytes, size_t size);
#endif

public:
    Cheat(const wchar_t*);
    ~Cheat();
    void freezeAmmo(bool enabled);
    void rapidFire(bool enabled);
    void kickbackForce(bool enabled);
    Entity* getIntersectEntity();
};