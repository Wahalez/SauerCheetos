#include "cheat.hpp"

#define modName L"sauerbraten.exe"

uintptr_t moduleBase;

BYTE originalAmmoCode[8];


void initCheat() {
    initModuleAddress();
    //test();
}

void initModuleAddress() {
    moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandleW(modName));
    //std::cout << std::hex << moduleBase << std::endl;
}

// void test() {
//     uintptr_t ammoCode = moduleBase + 0x1DB5E0;
//     std::cout << std::hex << ammoCode << std::endl;
//     BYTE code[8];
//     memcpy(code, (void*)ammoCode, 8);

//     for (auto c : code) {
//         std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c << " ";
//     }
//     std::cout << std::endl;
// }