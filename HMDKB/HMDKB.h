#pragma once

#include "resource.h"

//���z�L�[�{�[�h����
void KeyAction_Set(vtukey_t vtukey) {
    int counter = 0;
    while (vtukey.key_pressing[counter] != vtukey.endpoint) {
        KeyAction(vtukey.key_data[counter], vtukey.key_pressing[counter]);
        counter++;
    }
    return;
}