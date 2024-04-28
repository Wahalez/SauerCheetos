#include "globals.hpp"

const std::vector<unsigned char> keysToCapture = {
    VK_DELETE, // exit cheat
    VK_F4,     // freeze health
    VK_F5,     // freeze ammo
    VK_F6,     // rapid fire
    VK_F7,     // kickback force
    VK_F8,     // make'em jump
    VK_F9,     // auto shoot
};

Cheat *cheat_handler = nullptr;
