#include "globals.hpp"

const std::vector<unsigned char> keysToCapture = {
    VK_F5, // freeze ammo
    VK_F6, // rapid fire
    VK_F7, // kickback force
    VK_F8, // make'em jump
    VK_F9, // change entity type finder offset
    VK_F10, // kaki
};
std::vector<Key*> keys;

Entity* player = NULL;

// cheat state
bool freezeAmmo = false;
bool rapidFire = false;
bool kickbackForce = false;
bool makeemjump = false;
bool auto_shoot = false;

int* type_offset = new int();