#include "Cheat.hpp"

Cheat::Cheat(const wchar_t *moduleName)
{
    this->moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandleW(moduleName));

    this->player = *reinterpret_cast<Entity **>(this->moduleBase + STATIC_PLAYER_POINTER_OFFSET);

    this->intersect_function = (intersectClosest)(this->moduleBase + INTERSECTDIST_FUNCTION_OFFSET);

    this->init_cheat_state();

    this->init_capture_keys();

    this->load_original_codes();

    this->printCheat();
}

Cheat::~Cheat()
{
    delete[] this->originalHealthCode;
    delete[] this->originalAmmoCode;
    delete[] this->originalRapidFireCode;
    delete[] this->originalKickbackRightLeftCode1;
    delete[] this->originalKickbackRightLeftCode2;
    delete[] this->originalKickbackBackForwardCode1;
    delete[] this->originalKickbackBackForwardCode2;
    delete[] this->originalKickbackUpDownCode1;
    delete[] this->originalKickbackUpDownCode2;
}

void Cheat::run()
{
    while (true)
    {
        this->handle_keys_capture();
        this->handle_makeemjump();
        this->handle_auto_shoot();
    }
}

void Cheat::handle_keys_capture()
{
    for (Key *key : this->keys_capture)
    {
        key->captureKey();
        if (key->isPressed())
            this->handle_key_capture(key);
    }
}

void Cheat::handle_key_capture(Key *key)
{
    switch (key->getKey())
    {
    case VK_F4:
        this->freezeHealth = !this->freezeHealth;
        this->handle_freeze_health();
        break;

    case VK_F5:
        this->freezeAmmo = !this->freezeAmmo;
        this->handle_freeze_ammo();
        break;

    case VK_F6:
        this->rapidFire = !this->rapidFire;
        this->handle_rapid_fire();
        break;

    case VK_F7:
        this->kickback_force = !this->kickback_force;
        this->handle_kickbackForce();
        break;

    case VK_F8:
        this->makeemjump = !this->makeemjump;
        break;

    case VK_F9:
        this->auto_shoot = !this->auto_shoot;
        break;

    default:
        break;
    }
#ifdef __DEBUG
    this->printCheat();
#endif
}

void Cheat::init_cheat_state()
{
    this->freezeHealth = false;
    this->freezeAmmo = false;
    this->rapidFire = false;
    this->makeemjump = false;
    this->auto_shoot = false;
    this->kickback_force = false;
}

void Cheat::init_capture_keys()
{
    for (auto key : keysToCapture)
        keys_capture.push_back(new Key(key));
}

void Cheat::init_code_buffers()
{
    this->originalHealthCode = new BYTE[HEALTH_CODE_BYTES_COUNT];
    this->originalAmmoCode = new BYTE[AMMO_CODE_BYTES_COUNT];
    this->originalRapidFireCode = new BYTE[RAPID_FIRE_BYTES_COUNT];

    this->originalKickbackRightLeftCode1 = new BYTE[KICKBACK_RIGHT_LEFT_1_BYTES];
    this->originalKickbackRightLeftCode2 = new BYTE[KICKBACK_RIGHT_LEFT_2_BYTES];

    this->originalKickbackBackForwardCode1 = new BYTE[KICKBACK_BACK_FORWARD_1_BYTES];
    this->originalKickbackBackForwardCode2 = new BYTE[KICKBACK_BACK_FORWARD_2_BYTES];

    this->originalKickbackUpDownCode1 = new BYTE[KICKBACK_UP_DOWN_1_BYTES];
    this->originalKickbackUpDownCode2 = new BYTE[KICKBACK_UP_DOWN_2_BYTES];
}

void Cheat::load_original_codes()
{
    this->init_code_buffers();

    this->load_original_health_code();
    this->load_original_ammo_code();
    this->load_original_rapid_fire_code();
    this->load_original_Kickback_force_code();
}

void Cheat::load_original_health_code()
{
    this->healthCodeStart = this->moduleBase + HEALTH_CODE_OFFSET;
    memcpy(this->originalHealthCode, (void *)this->healthCodeStart, HEALTH_CODE_BYTES_COUNT);
}

void Cheat::load_original_ammo_code()
{
    this->ammoCodeStart = this->moduleBase + AMMO_CODE_OFFSET;
    memcpy(this->originalAmmoCode, (void *)this->ammoCodeStart, AMMO_CODE_BYTES_COUNT);
}

void Cheat::load_original_Kickback_force_code()
{
    this->kickbackRightLeft1 = this->moduleBase + KICKBACK_RIGHT_LEFT_1_OFFSET;
    memcpy(this->originalKickbackRightLeftCode1, (void *)this->kickbackRightLeft1, KICKBACK_RIGHT_LEFT_1_BYTES);

    this->kickbackRightLeft2 = this->moduleBase + KICKBACK_RIGHT_LEFT_2_OFFSET;
    memcpy(this->originalKickbackRightLeftCode2, (void *)this->kickbackRightLeft2, KICKBACK_RIGHT_LEFT_2_BYTES);

    this->kickbackBackForward1 = this->moduleBase + KICKBACK_BACK_FORWARD_1_OFFSET;
    memcpy(this->originalKickbackBackForwardCode1, (void *)this->kickbackBackForward1, KICKBACK_BACK_FORWARD_1_BYTES);

    this->kickbackBackForward2 = this->moduleBase + KICKBACK_BACK_FORWARD_2_OFFSET;
    memcpy(this->originalKickbackBackForwardCode2, (void *)this->kickbackBackForward2, KICKBACK_BACK_FORWARD_2_BYTES);

    this->kickbackUpDown1 = this->moduleBase + KICKBACK_UP_DOWN_1_OFFSET;
    memcpy(this->originalKickbackUpDownCode1, (void *)this->kickbackUpDown1, KICKBACK_UP_DOWN_1_BYTES);

    this->kickbackUpDown2 = this->moduleBase + KICKBACK_UP_DOWN_2_OFFSET;
    memcpy(this->originalKickbackUpDownCode2, (void *)this->kickbackUpDown2, KICKBACK_UP_DOWN_2_BYTES);
}

void Cheat::load_original_rapid_fire_code()
{
    this->rapidFireStart = this->moduleBase + RAPID_FIRE_OFFSET;
    memcpy(this->originalRapidFireCode, (void *)this->rapidFireStart, RAPID_FIRE_BYTES_COUNT);
}

void Cheat::handle_freeze_health()
{
    this->alter_code_with_nop_bytes(this->freezeHealth, this->healthCodeStart, HEALTH_CODE_BYTES_COUNT, this->originalHealthCode);
}

void Cheat::handle_freeze_ammo()
{
    this->alter_code_with_nop_bytes(this->freezeAmmo, this->ammoCodeStart, AMMO_CODE_BYTES_COUNT, this->originalAmmoCode);
}

void Cheat::handle_rapid_fire()
{
    this->alter_code_with_nop_bytes(this->rapidFire, this->rapidFireStart, RAPID_FIRE_BYTES_COUNT, this->originalRapidFireCode);
}

void Cheat::alter_code_with_nop_bytes(bool enabled, uintptr_t code_offset, size_t bytes, BYTE *originalCode)
{
    DWORD oldProtection;

    VirtualProtect((void *)code_offset, bytes, PAGE_EXECUTE_READWRITE, &oldProtection);

    if (enabled)
        memset((void *)code_offset, 0x90, bytes);
    else
        memcpy((void *)code_offset, originalCode, bytes);

    VirtualProtect((void *)code_offset, bytes, oldProtection, NULL);
}

void Cheat::handle_kickbackForce()
{
    this->alter_code_with_nop_bytes(this->kickback_force, this->kickbackRightLeft1, KICKBACK_RIGHT_LEFT_1_BYTES, this->originalKickbackRightLeftCode1);
    this->alter_code_with_nop_bytes(this->kickback_force, this->kickbackRightLeft2, KICKBACK_RIGHT_LEFT_2_BYTES, this->originalKickbackRightLeftCode2);
    this->alter_code_with_nop_bytes(this->kickback_force, this->kickbackBackForward1, KICKBACK_BACK_FORWARD_1_BYTES, this->originalKickbackBackForwardCode1);
    this->alter_code_with_nop_bytes(this->kickback_force, this->kickbackBackForward2, KICKBACK_BACK_FORWARD_2_BYTES, this->originalKickbackBackForwardCode2);
    this->alter_code_with_nop_bytes(this->kickback_force, this->kickbackUpDown1, KICKBACK_UP_DOWN_1_BYTES, this->originalKickbackUpDownCode1);
    this->alter_code_with_nop_bytes(this->kickback_force, this->kickbackUpDown2, KICKBACK_UP_DOWN_2_BYTES, this->originalKickbackUpDownCode2);
}

void Cheat::handle_makeemjump()
{
    // static Entity* previous_entity = nullptr;
    if (this->makeemjump)
    {
        Entity *current_entity = this->getIntersectEntity();
        if (current_entity
            //&& current_entity != previous_entity
        )
        {
            // previous_entity = current_entity;
            current_entity->kick_force_up_down = 100;
        }
    }
}

void Cheat::handle_auto_shoot()
{
    static bool found_monster_before = false;
    if (this->auto_shoot)
    {
        Entity *current_entity = this->getIntersectEntity();
        if (current_entity)
        {
            uintptr_t p = *(uintptr_t *)((uintptr_t)current_entity + MODEL_OFFSET);
            if (p != NULL)
            {
                char *model_string = (char *)(*(uintptr_t *)(p + MODEL_STRING_OFFSET));
                if (model_string != nullptr)
                {
                    std::string entity_type{model_string};
                    if (is_monster_type(entity_type))
                    {
                        this->player->shoot = true;
                        found_monster_before = true;
                    }
                }
            }
        }
        else if (found_monster_before)
        {
            found_monster_before = false;
            this->player->shoot = false;
        }
    }
}

Entity *Cheat::getIntersectEntity()
{
    void *worldpos{(void *)(this->moduleBase + WORLDPOS_OFFSET)};
    float *intersectDist{(float *)(this->moduleBase + INTERSECTDIST_OFFSET)};

    return intersect_function(player, worldpos, player, intersectDist);
}

#ifdef __DEBUG
void Cheat::printBytes(BYTE *bytes, size_t size)
{
    for (size_t idx = 0; idx < size; idx++)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[idx]) << " ";
    }
    std::cout << std::endl;
}

bool Cheat::is_monster_type(std::string model_string)
{
    if (model_string.find("monster") != std::string::npos ||
        model_string.find("ogro") != std::string::npos)
        return true;
    return false;
}

void Cheat::printCheat()
{
    std::string cheat_menu =
        "---------CHEAT---------\n"
        "F4: Freeze Health\n"
        "F5: Freeze Ammo\n"
        "F6: Rapid Fire\n"
        "F7: KickBack Force\n"
        "F8: Make'em Jump & entity type finder"
        "F9: Auto Shoot"
        "\n\n";

    if (this->freezeHealth)
        cheat_menu += "[+] Freeze Health";
    else
        cheat_menu += "[-] Freeze Health";
    cheat_menu += "\n";

    if (this->freezeAmmo)
        cheat_menu += "[+] Freeze Ammo";
    else
        cheat_menu += "[-] Freeze Ammo";
    cheat_menu += "\n";

    if (this->rapidFire)
        cheat_menu += "[+] Rapid Fire";
    else
        cheat_menu += "[-] Rapid Fire";
    cheat_menu += "\n";

    if (this->kickback_force)
        cheat_menu += "[+] Remove Kickback Force";
    else
        cheat_menu += "[-] Remove Kickback Force";
    cheat_menu += "\n";

    if (this->makeemjump)
        cheat_menu += "[+] Make Entities Jump";
    else
        cheat_menu += "[-] Make Entities Jump";
    cheat_menu += "\n";

    if (this->auto_shoot)
        cheat_menu += "[+] Auto Shoot";
    else
        cheat_menu += "[-] Auto Shoot";
    cheat_menu += "\n";

    system("cls");
    std::cout << cheat_menu << std::endl;
}
#endif