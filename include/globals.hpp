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