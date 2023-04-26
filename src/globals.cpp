#include "globals.hpp"

const std::vector<unsigned char> keysToCapture = { VK_F5, VK_F6, VK_F7 };
std::vector<Key*> keys;

// cheat state
bool freezeAmmo = false;
bool rapidFire = false;
bool kickbackForce = false;