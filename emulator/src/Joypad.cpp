//
// Created by gyorgy on 28/10/18.
//

#include "../include/Joypad.h"
#include "../include/Helper.h"
#include "../include/SDL2/SDL_scancode.h"
#include <SDL2/SDL_events.h>

uint8 Joypad::joypadReg = UINT8_MAX;
uint8 *Joypad::keyboardArray = nullptr;
bool  Joypad::isDirectionKeys = false;

Joypad::Joypad() { }

Joypad::~Joypad() { }

bool Joypad::WriteToRegister(uint8 value)
{
    isDirectionKeys = !Helper::IsBitSet(value, 4);

    if (isDirectionKeys) {
        Helper::SetBit(&joypadReg, 5);
        Helper::ClearBit(&joypadReg, 4);
    }
    else {
        Helper::SetBit(&joypadReg, 4);
        Helper::ClearBit(&joypadReg, 5);
    }
    return true;
}

uint8 Joypad::ReadRegister()
{
    SDL_PumpEvents();
    keyboardArray = const_cast<uint8 *>(SDL_GetKeyboardState(NULL));

    int bit3KeyCode;
    int bit2KeyCode;
    int bit1KeyCode;
    int bit0KeyCode;
    if (isDirectionKeys) {
        bit3KeyCode = SDL_SCANCODE_DOWN;
        bit2KeyCode = SDL_SCANCODE_UP;
        bit1KeyCode = SDL_SCANCODE_LEFT;
        bit0KeyCode = SDL_SCANCODE_RIGHT;
    }
    else {
        bit3KeyCode = SDL_SCANCODE_SPACE;
        bit2KeyCode = SDL_SCANCODE_RETURN;
        bit1KeyCode = SDL_SCANCODE_A;
        bit0KeyCode = SDL_SCANCODE_D;
    }

    if (keyboardArray[bit3KeyCode]) Helper::ClearBit(&joypadReg, 3);
    else                            Helper::SetBit(&joypadReg, 3);

    if (keyboardArray[bit2KeyCode]) Helper::ClearBit(&joypadReg, 2);
    else                            Helper::SetBit(&joypadReg, 2);

    if (keyboardArray[bit1KeyCode]) Helper::ClearBit(&joypadReg, 1);
    else                            Helper::SetBit(&joypadReg, 1);

    if (keyboardArray[bit0KeyCode]) Helper::ClearBit(&joypadReg, 0);
    else                            Helper::SetBit(&joypadReg, 0);

    return joypadReg;
}
