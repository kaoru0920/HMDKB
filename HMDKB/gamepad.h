#pragma once

#pragma comment (lib, "xinput.lib")
#include <Xinput.h>
#include <windows.h>

#define XINPUT_GAMEPAD_DPAD_UP          0x0001
#define XINPUT_GAMEPAD_DPAD_DOWN        0x0002
#define XINPUT_GAMEPAD_DPAD_LEFT        0x0004
#define XINPUT_GAMEPAD_DPAD_RIGHT       0x0008
#define XINPUT_GAMEPAD_START            0x0010
#define XINPUT_GAMEPAD_BACK             0x0020
#define XINPUT_GAMEPAD_LEFT_THUMB       0x0040
#define XINPUT_GAMEPAD_RIGHT_THUMB      0x0080
#define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
#define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
#define XINPUT_GAMEPAD_A                0x1000
#define XINPUT_GAMEPAD_B                0x2000
#define XINPUT_GAMEPAD_X                0x4000
#define XINPUT_GAMEPAD_Y                0x8000

//�c���f�[�^
struct stick2d{
    int horizontal;
    int vertical;
};

//������
void initButton(XINPUT_STATE now_state, XINPUT_STATE before_state) {
    ZeroMemory(&now_state, sizeof(XINPUT_STATE));
    ZeroMemory(&before_state, sizeof(XINPUT_STATE));
}

//�Q�[���p�b�h�̏�Ԃ��X�V
void updatePad(XINPUT_STATE *state,int controller) {
    XInputGetState(
        controller,       // DWORD         dwUserIndex
        state); // XINPUT_STATE* pState
}

//�������u��
bool releaseButton(int button_id,XINPUT_STATE now_state,XINPUT_STATE before_state) {
    if (before_state.Gamepad.wButtons != button_id) {
        if (now_state.Gamepad.wButtons == button_id) {
            return true;
        }
    }
    return false;
}

//�������u��
bool pushButton(int button_id, XINPUT_STATE now_state, XINPUT_STATE before_state) {
    if (before_state.Gamepad.wButtons != button_id) {
        if (now_state.Gamepad.wButtons == button_id) {
            return true;
        }
    }
    return false;
}

//�����Ă����
bool pushingButton(int button_id, XINPUT_STATE now_state, XINPUT_STATE before_state) {
    if (before_state.Gamepad.wButtons == button_id) {
        if (now_state.Gamepad.wButtons == button_id) {
            return true;
        }
    }
    return false;
}

//�����Ă��邩�`�F�b�N
bool checkButton(int button_id, XINPUT_STATE now_state) {
    if (now_state.Gamepad.wButtons == button_id) {
        return true;
    }
    return false;
}

//�f�b�h�]�[��
XINPUT_STATE checkDeadzone(XINPUT_STATE now_state) {
    if ((now_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
        now_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
        (now_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
            now_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
    {
        now_state.Gamepad.sThumbLX = 0;
        now_state.Gamepad.sThumbLY = 0;
    }
    if ((now_state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
        now_state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
        (now_state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
            now_state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
    {
        now_state.Gamepad.sThumbRX = 0;
        now_state.Gamepad.sThumbRY = 0;
    }
    return now_state;
}

//�c���f�[�^����
stick2d numRStick(XINPUT_STATE now_state) {
    stick2d now_stick;
    now_state = checkDeadzone(now_state);
    now_stick.horizontal = now_state.Gamepad.sThumbRX;
    now_stick.vertical = now_state.Gamepad.sThumbRY;
    return now_stick;
}

//�c���f�[�^����
stick2d numLStick(XINPUT_STATE now_state) {
    stick2d now_stick;
    now_state = checkDeadzone(now_state);
    now_stick.horizontal = now_state.Gamepad.sThumbLX;
    now_stick.vertical = now_state.Gamepad.sThumbLY;
    return now_stick;
}

//�������Ă��邩�`�F�b�N
bool checkRStick(XINPUT_STATE now_state) {
    now_state = checkDeadzone(now_state);
    if (now_state.Gamepad.sThumbRX == 0 && now_state.Gamepad.sThumbRY == 0) {
        return false;
    }
    return true;
}

//�������Ă��邩�`�F�b�N
bool checkLStick(XINPUT_STATE now_state) {
    now_state = checkDeadzone(now_state);
    if (now_state.Gamepad.sThumbLX == 0 && now_state.Gamepad.sThumbLY == 0) {
        return false;
    }
    return true;
}

//�������u��
bool releaseRTrigger(int num, XINPUT_STATE now_state, XINPUT_STATE before_state) {
    if (before_state.Gamepad.bRightTrigger >= num) {
        if (now_state.Gamepad.bRightTrigger < num) {
            return true;
        }
    }
    return false;
}

//�������u��
bool pushRTrigger(int num, XINPUT_STATE now_state, XINPUT_STATE before_state) {
    if (before_state.Gamepad.bRightTrigger < num) {
        if (now_state.Gamepad.bRightTrigger >= num) {
            return true;
        }
    }
    return false;
}

//�����Ă����
bool pushingRTrigger(int num, XINPUT_STATE now_state, XINPUT_STATE before_state) {
    if (before_state.Gamepad.bRightTrigger >= num) {
        if (now_state.Gamepad.bRightTrigger >= num) {
            return true;
        }
    }
    return false;
}

//�����Ă��邩�`�F�b�N
bool checkRTrigger(int num, XINPUT_STATE now_state) {
    if (now_state.Gamepad.bRightTrigger >= num) {
        return true;
    }
    return false;
}

//�������u��
bool releaseLTrigger(int num, XINPUT_STATE now_state, XINPUT_STATE before_state) {
    if (before_state.Gamepad.bLeftTrigger >= num) {
        if (now_state.Gamepad.bLeftTrigger < num) {
            return true;
        }
    }
    return false;
}

//�������u��
bool pushLTrigger(int num, XINPUT_STATE now_state, XINPUT_STATE before_state) {
    if (before_state.Gamepad.bLeftTrigger < num) {
        if (now_state.Gamepad.bLeftTrigger >= num) {
            return true;
        }
    }
    return false;
}

//�����Ă����
bool pushingLTrigger(int num, XINPUT_STATE now_state, XINPUT_STATE before_state) {
    if (before_state.Gamepad.bLeftTrigger >= num) {
        if (now_state.Gamepad.bLeftTrigger >= num) {
            return true;
        }
    }
    return false;
}

//�����Ă��邩�`�F�b�N
bool checkLTrigger(int num, XINPUT_STATE now_state) {
    if (now_state.Gamepad.bRightTrigger >= num) {
        return true;
    }
    return false;
}

