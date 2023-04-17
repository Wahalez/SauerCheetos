#pragma once

#include <iostream>
#include <Windows.h>

class Key {
private:
    unsigned char key;
    int count;
public:
    Key(unsigned char key);
    void captureKey();
    bool isPressed();
    bool isDown();
    unsigned char getKey();
};