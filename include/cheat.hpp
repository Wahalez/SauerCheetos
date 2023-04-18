#pragma once

#include "windows.h"
#include "globals.hpp"
#include <iostream>
#include <iomanip>

#define __DEBUG

#define AMMO_CODE_BYTES_COUNT 8
#define AMMO_CODE_OFFSET 0x1DB5E0

class Cheat {
private:
    uintptr_t moduleBase;

    uintptr_t ammoCodeStart;
    BYTE* originalAmmoCode;
    void loadOriginalAmmoCode();

#ifdef __DEBUG
    void printBytes(BYTE* bytes, size_t size);
#endif

public:
    Cheat(const wchar_t*);
    ~Cheat();
    void freezeAmmo(bool enabled);
};