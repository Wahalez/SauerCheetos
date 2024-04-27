#include "cheat.hpp"

typedef Entity *(__cdecl *intersectClosest)(Entity *, void *, Entity *, float *);

intersectClosest intersectFunc{nullptr};

Cheat::Cheat(const wchar_t *moduleName)
{
    this->moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandleW(moduleName));

    this->initCodeBuffers();
    this->loadOriginalAmmoCode();
    this->loadOriginalRapidFireCode();
    this->loadOriginalKickbackForceCode();

    player = *reinterpret_cast<Entity **>(this->moduleBase + STATIC_PLAYER_POINTER_OFFSET);

    intersectFunc = (intersectClosest)(this->moduleBase + INTERSECTDIST_FUNCTION_OFFSET);

#ifdef __DEBUG
    std::cout << "Loaded original ammo code: ";
    this->printBytes(this->originalAmmoCode, AMMO_CODE_BYTES_COUNT);

    std::cout << "\nPlayer address: " << player << std::endl;
    std::cout << "\n---Check player object---\nPistol ammo: " << std::dec << player->pistol_ammo << std::endl;
#endif
}

Cheat::~Cheat()
{
    delete[] this->originalAmmoCode;
    delete[] this->originalRapidFireCode;
    delete[] this->originalKickbackRightLeftCode1;
    delete[] this->originalKickbackRightLeftCode2;
    delete[] this->originalKickbackBackForwardCode1;
    delete[] this->originalKickbackBackForwardCode2;
    delete[] this->originalKickbackUpDownCode1;
    delete[] this->originalKickbackUpDownCode2;
}

void Cheat::initCodeBuffers()
{
    this->originalAmmoCode = new BYTE[AMMO_CODE_BYTES_COUNT];
    this->originalRapidFireCode = new BYTE[RAPID_FIRE_BYTES_COUNT];

    this->originalKickbackRightLeftCode1 = new BYTE[KICKBACK_RIGHT_LEFT_1_BYTES];
    this->originalKickbackRightLeftCode2 = new BYTE[KICKBACK_RIGHT_LEFT_2_BYTES];

    this->originalKickbackBackForwardCode1 = new BYTE[KICKBACK_BACK_FORWARD_1_BYTES];
    this->originalKickbackBackForwardCode2 = new BYTE[KICKBACK_BACK_FORWARD_2_BYTES];

    this->originalKickbackUpDownCode1 = new BYTE[KICKBACK_UP_DOWN_1_BYTES];
    this->originalKickbackUpDownCode2 = new BYTE[KICKBACK_UP_DOWN_2_BYTES];
}

void Cheat::loadOriginalAmmoCode()
{
    this->ammoCodeStart = this->moduleBase + AMMO_CODE_OFFSET;
    memcpy(this->originalAmmoCode, (void *)this->ammoCodeStart, AMMO_CODE_BYTES_COUNT);
}

void Cheat::loadOriginalRapidFireCode()
{
    this->rapidFireStart = this->moduleBase + RAPID_FIRE_OFFSET;
    memcpy(this->originalRapidFireCode, (void *)this->rapidFireStart, RAPID_FIRE_BYTES_COUNT);
}

void Cheat::loadOriginalKickbackForceCode()
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

#ifdef __DEBUG
void Cheat::printBytes(BYTE *bytes, size_t size)
{
    for (size_t idx = 0; idx < size; idx++)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[idx]) << " ";
    }
    std::cout << std::endl;
}
#endif

void Cheat::freezeAmmo(bool enabled)
{
    this->alterCode_nop(enabled, this->ammoCodeStart, AMMO_CODE_BYTES_COUNT, this->originalAmmoCode);
}

void Cheat::rapidFire(bool enabled)
{
    this->alterCode_nop(enabled, this->rapidFireStart, RAPID_FIRE_BYTES_COUNT, this->originalRapidFireCode);
}

void Cheat::alterCode_nop(bool enabled, uintptr_t code_offset, size_t bytes, BYTE *originalCode)
{
    DWORD oldProtection;

    VirtualProtect((void *)code_offset, bytes, PAGE_EXECUTE_READWRITE, &oldProtection);

    if (enabled)
        memset((void *)code_offset, 0x90, bytes);
    else
        memcpy((void *)code_offset, originalCode, bytes);

    VirtualProtect((void *)code_offset, bytes, oldProtection, NULL);
}

void Cheat::kickbackForce(bool enabled)
{
    this->alterCode_nop(enabled, this->kickbackRightLeft1, KICKBACK_RIGHT_LEFT_1_BYTES, this->originalKickbackRightLeftCode1);
    this->alterCode_nop(enabled, this->kickbackRightLeft2, KICKBACK_RIGHT_LEFT_2_BYTES, this->originalKickbackRightLeftCode2);
    this->alterCode_nop(enabled, this->kickbackBackForward1, KICKBACK_BACK_FORWARD_1_BYTES, this->originalKickbackBackForwardCode1);
    this->alterCode_nop(enabled, this->kickbackBackForward2, KICKBACK_BACK_FORWARD_2_BYTES, this->originalKickbackBackForwardCode2);
    this->alterCode_nop(enabled, this->kickbackUpDown1, KICKBACK_UP_DOWN_1_BYTES, this->originalKickbackUpDownCode1);
    this->alterCode_nop(enabled, this->kickbackUpDown2, KICKBACK_UP_DOWN_2_BYTES, this->originalKickbackUpDownCode2);
}

Entity *Cheat::getIntersectEntity()
{
    void *worldpos{(void *)(this->moduleBase + WORLDPOS_OFFSET)};
    float *intersectDist{(float *)(this->moduleBase + INTERSECTDIST_OFFSET)};

    return intersectFunc(player, worldpos, player, intersectDist);
}