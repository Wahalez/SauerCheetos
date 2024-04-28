#include "Key.hpp"

Key::Key(unsigned char key) : key{key} {}

void Key::captureKey()
{
    if (GetAsyncKeyState(key) & 0x8000)
        count++;
    else
        count = 0;
}

bool Key::isPressed()
{
    return count == 1;
}

bool Key::isDown()
{
    return count > 0;
}

unsigned char Key::getKey()
{
    return this->key;
}