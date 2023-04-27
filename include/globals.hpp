#pragma once

#include <vector>
#include <Windows.h>
#include "Key.hpp"
#include "Entity.hpp"

extern const std::vector<unsigned char> keysToCapture;
extern std::vector<Key*> keys;

extern Entity* player;

extern bool freezeAmmo;
extern bool rapidFire;
extern bool kickbackForce;
extern bool makeemjump;

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