#include <cstdint>

#pragma once

class Entity {
   public:
    char pad_0000[8];                  // 0x0000
    float N00000050;                   // 0x0008
    float Kick_force_right_left;       // 0x000C
    float Kick_force_back_forward;     // 0x0010
    float kick_force_up_down;          // 0x0014
    char pad_0018[8];                  // 0x0018
    float gravity_force;               // 0x0020
    char pad_0024[12];                 // 0x0024
    float XPos;                        // 0x0030
    float ZPos;                        // 0x0034
    float YPos;                        // 0x0038
    float XCam;                        // 0x003C
    float YCam;                        // 0x0040
    float ZCam;                        // 0x0044
    char pad_0048[304];                // 0x0048
    int32_t Health;                    // 0x0178
    int32_t max_health;                // 0x017C
    int32_t armor;                     // 0x0180
    int32_t armor_type;                // 0x0184
    int32_t quad_damage_timer;         // 0x0188
    int32_t equipped_weapon;           // 0x018C
    int32_t reload_delay;              // 0x0190
    char pad_0194[4];                  // 0x0194
    int32_t shotgun_ammo;              // 0x0198
    int32_t minigun_ammo;              // 0x019C
    int32_t rocket_launcher_ammo;      // 0x01A0
    int32_t sniper_ammo;               // 0x01A4
    int32_t grenade_launcher_ammo;     // 0x01A8
    int32_t pistol_ammo;               // 0x01AC
    int32_t fire_balls_ammo;           // 0x01B0
    int32_t blue_balls_ammo;           // 0x01B4
    int32_t green_balls_ammo;          // 0x01B8
    char pad_01BC[16];                 // 0x01BC
    int32_t N0000008A;                 // 0x01CC
    char pad_01D0[36];                 // 0x01D0
    int32_t N0000008F;                 // 0x01F4
    int32_t last_attack_gun;           // 0x01F8
    bool shoot;                        // 0x01FC
    char pad_01FD[71];                 // 0x01FD
    int32_t total_damage;              // 0x0244
    int32_t total_dmg_and_missed_dmg;  // 0x0248
};                                     // Size: 0x0438