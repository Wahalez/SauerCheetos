#pragma once

#include "windows.h"
#include "globals.hpp"
#include "Entity.hpp"
#include <iostream>
#include <iomanip>

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