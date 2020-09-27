#pragma once

#include <windows.h>

//1•¶Žš“ü—Í
void KeyAction(WORD VirtualKey, BOOL bKeepPressing)
{
    INPUT input[1];
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = VirtualKey;
    input[0].ki.wScan = MapVirtualKey(input[0].ki.wVk, 0);
    input[0].ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
    input[0].ki.time = 0;
    input[0].ki.dwExtraInfo = ::GetMessageExtraInfo();
    ::SendInput(1, input, sizeof(INPUT));
    if (!bKeepPressing)
    {
        input[0].ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP;
        ::SendInput(1, input, sizeof(INPUT));
    }
}

void moveWheel(int w) {
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, w, 0);
}