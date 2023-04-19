#include "cheat.hpp"

Cheat::Cheat(const wchar_t* moduleName) {
    this->moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandleW(moduleName));
    this->initCodeBuffers();
    this->loadOriginalAmmoCode();
    this->loadOriginalRapidFireCode();

#ifdef __DEBUG
    std::cout << "Loaded original ammo code: ";
    this->printBytes(this->originalAmmoCode, AMMO_CODE_BYTES_COUNT);
#endif

}

Cheat::~Cheat() {
    delete[] this->originalAmmoCode;
    delete[] this->originalRapidFireCode;
}

void Cheat::initCodeBuffers() {
    this->originalAmmoCode = new BYTE[AMMO_CODE_BYTES_COUNT];
    this->originalRapidFireCode = new BYTE[RAPID_FIRE_BYTES_COUNT];
}

void Cheat::loadOriginalAmmoCode() {
    this->ammoCodeStart = this->moduleBase + AMMO_CODE_OFFSET;
    memcpy(this->originalAmmoCode, (void*)this->ammoCodeStart, AMMO_CODE_BYTES_COUNT);
}

void Cheat::loadOriginalRapidFireCode() {
    this->rapidFireStart = this->moduleBase + RAPID_FIRE_OFFSET;
    memcpy(this->originalRapidFireCode, (void*)this->rapidFireStart, RAPID_FIRE_BYTES_COUNT);
}

#ifdef __DEBUG
void Cheat::printBytes(BYTE* bytes, size_t size) {
    for (size_t idx = 0; idx < size; idx++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[idx]) << " ";
    }
    std::cout << std::endl;
}
#endif

void Cheat::freezeAmmo(bool enabled) {
    DWORD oldProtection;

    VirtualProtect((void*)ammoCodeStart, AMMO_CODE_BYTES_COUNT, PAGE_EXECUTE_READWRITE, &oldProtection);

    if (enabled)
        memset((void*)ammoCodeStart, 0x90, AMMO_CODE_BYTES_COUNT);
    else
        memcpy((void*)ammoCodeStart, this->originalAmmoCode, AMMO_CODE_BYTES_COUNT);

    VirtualProtect((void*)ammoCodeStart, AMMO_CODE_BYTES_COUNT, oldProtection, NULL);
}

void Cheat::rapidFire(bool enabled) {
    DWORD oldProtection;

    VirtualProtect((void*)rapidFireStart, RAPID_FIRE_BYTES_COUNT, PAGE_EXECUTE_READWRITE, &oldProtection);

    if (enabled)
        memset((void*)rapidFireStart, 0x90, RAPID_FIRE_BYTES_COUNT);
    else
        memcpy((void*)rapidFireStart, this->originalRapidFireCode, RAPID_FIRE_BYTES_COUNT);

    VirtualProtect((void*)rapidFireStart, RAPID_FIRE_BYTES_COUNT, oldProtection, NULL);
}