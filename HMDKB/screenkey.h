#pragma once

#include <windows.h>

//記号定数
#define pointer_x 9
#define pointer_y 4
#define allowance_x 10
#define allowance_y 10
#define width 50
#define height 50
#define rw 10
#define rh 10

struct vtukey_t {
    int key_data[10];
    int key_pressing[10];
    int endpoint;
};

struct keyb_t {
    char name[20];
    wchar_t positioning[60];
    int horizontal;
    int vertical;
    vtukey_t vtukey[60];
    int imemode;
};

struct n2d_t{
    LONG x;
    LONG y;
};

//キー配置
static keyb_t US_L = { "US_L",L"1234567890QWERTYUIOPASDFGHJKL@ZXCVBNM:;!",10,4,
    {{{'1'},{0},1},{{'2'},{0},1},{{'3'},{0},1},{{'4'},{0},1},{{'5'},{0},1},{{'6'},{0},1},{{'7'},{0},1},{{'8'},{0},1},{{'9'},{0},1},{{'0'},{0},1},
    {{VK_SHIFT,'Q',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'W',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'E',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'R',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'T',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'Y',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'U',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'I',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'O',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'P',VK_SHIFT},{1,0,0},3},
    {{VK_SHIFT,'A',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'S',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'D',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'F',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'G',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'H',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'J',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'K',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'L',VK_SHIFT},{1,0,0},3},{{VK_OEM_3},{0},1},
    {{VK_SHIFT,'Z',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'X',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'C',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'V',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'B',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'N',VK_SHIFT},{1,0,0},3},{{VK_SHIFT,'M',VK_SHIFT},{1,0,0},3},{{VK_OEM_1},{0},1},{{VK_OEM_PLUS},{0},1},{{VK_SHIFT,'1',VK_SHIFT},{1,0,0},3},1}
};
static keyb_t US_S = { "US_S",L"1234567890qwertyuiopasdfghjkl'zxcvbnm,.?",10,4,
    {{{'1'},{0},1},{{'2'},{0},1},{{'3'},{0},1},{{'4'},{0},1},{{'5'},{0},1},{{'6'},{0},1},{{'7'},{0},1},{{'8'},{0},1},{{'9'},{0},1},{{'0'},{0},1},
    {{'Q'},{0},1},{{'W'},{0},1},{{'E'},{0},1},{{'R'},{0},1},{{'T'},{0},1},{{'Y'},{0},1},{{'U'},{0},1},{{'I'},{0},1},{{'O'},{0},1},{{'P'},{0},1},
    {{'A'},{0},1},{{'S'},{0},1},{{'D'},{0},1},{{'F'},{0},1},{{'G'},{0},1},{{'H'},{0},1},{{'J'},{0},1},{{'K'},{0},1},{{'L'},{0},1},{{VK_SHIFT,VK_OEM_3,VK_SHIFT},{1,0,0},3},
    {{'Z'},{0},1},{{'X'},{0},1},{{'C'},{0},1},{{'V'},{0},1},{{'B'},{0},1},{{'N'},{0},1},{{'M'},{0},1},{{VK_OEM_COMMA},{0},1},{{VK_OEM_PERIOD},{0},1},{{VK_SHIFT,VK_OEM_2,VK_SHIFT},{1,0,0},3},1}
};
static keyb_t JIS_L = { "JIS_L",L"あかさたなはまやらわいきしちにひみゆりをうくすつぬふむよるんえけせてねへめ　れーおこそとのほも　ろ変",10,5 ,
    {{{'A'},{0},1},{{'K','A'},{0},2},{{'S','A'},{0},2},{{'T','A'},{0},2},{{'N','A'},{0},2},{{'H','A'},{0},2},{{'M','A'},{0},2},{{'Y','A'},{0},2},{{'R','A'},{0},2},{{'W','A'},{0},2},
    {{'I'},{0},1},{{'K','I'},{0},2},{{'S','I'},{0},2},{{'T','I'},{0},2},{{'N','I'},{0},2},{{'H','I'},{0},2},{{'M','I'},{0},2},{{'Y','U'},{0},2},{{'R','I'},{0},2},{{'W','O'},{0},2},
    {{'U'},{0},1},{{'K','U'},{0},2},{{'S','U'},{0},2},{{'T','U'},{0},2},{{'N','U'},{0},2},{{'H','U'},{0},2},{{'M','U'},{0},2},{{'Y','O'},{0},2},{{'R','U'},{0},2},{{'N','N'},{0},2},
    {{'E'},{0},1},{{'K','E'},{0},2},{{'S','E'},{0},2},{{'T','E'},{0},2},{{'N','E'},{0},2},{{'H','E'},{0},2},{{'M','E'},{0},2},{{0},{0},0},{{'R','E'},{0},2},{{VK_OEM_MINUS},{0},1},
    {{'O'},{0},1},{{'K','O'},{0},2},{{'S','O'},{0},2},{{'T','O'},{0},2},{{'N','O'},{0},2},{{'H','O'},{0},2},{{'M','O'},{0},2},{{0},{0},0},{{'R','O'},{0},2},{{VK_SPACE},{0},1},1}
};

static keyb_t JIS_S = { "JIS_S",L"がざだばぱぁゃぎじぢびぴぃゅぐずづぶぷぅょげぜでべぺぇっごぞどぼぽぁ変",7,5,
    {{{'G','A'},{0},2},{{'Z','A'},{0},2},{{'D','A'},{0},2},{{'B','A'},{0},2},{{'P','A'},{0},2},{{'X','A'},{0},2},{{'X','Y','A'},{0},3},
    {{'G','I'},{0},2},{{'Z','I'},{0},2},{{'D','I'},{0},2},{{'B','I'},{0},2},{{'P','I'},{0},2},{{'X','I'},{0},2},{{'X','Y','U'},{0},3},
    {{'G','U'},{0},2},{{'Z','U'},{0},2},{{'D','U'},{0},2},{{'B','U'},{0},2},{{'P','U'},{0},2},{{'X','U'},{0},2},{{'X','Y','O'},{0},3},
    {{'G','E'},{0},2},{{'Z','E'},{0},2},{{'D','E'},{0},2},{{'B','E'},{0},2},{{'P','E'},{0},2},{{'X','E'},{0},2},{{'X','T','U'},{0},3},
    {{'G','O'},{0},2},{{'Z','O'},{0},2},{{'D','O'},{0},2},{{'B','O'},{0},2},{{'P','O'},{0},2},{{'X','O'},{0},2},{{VK_SPACE},{0},1},1}
};

//キーボード変更
keyb_t ChangeKey(int key_number) {
    keyb_t key_tmp = US_S;
    switch (key_number) {
    case 0:
        key_tmp = US_S;
        break;
    case 1:
        key_tmp = US_L;
        break;
    case 2:
        key_tmp = JIS_L;
        break;
    case 3:
        key_tmp = JIS_S;
        break;
    }
    return key_tmp;
}

//カーソル位置計算
int MoveCursor(int direction, keyb_t key_type, int key_location) {

    int tmp = key_location;
    int x_cell = key_type.horizontal;
    int y_cell = key_type.vertical;

    switch (direction) {
    case 0://上に移動
        tmp = tmp - x_cell;
        if (tmp < 0) {
            tmp = key_location + x_cell * (y_cell - 1);
        }
        break;
    case 1://右に移動
        tmp++;
        if (tmp % x_cell == 0) {
            tmp = tmp - x_cell;
        }
        break;
    case 2://下に移動
        tmp = tmp + x_cell;
        if (tmp > x_cell * y_cell - 1) {
            tmp = key_location - x_cell * (y_cell - 1);
        }
        break;
    case 3://左に移動
        tmp--;
        if (tmp < 0 || (tmp + 1) % x_cell == 0) {
            tmp = tmp + x_cell;
        }
        break;
    }

    key_location = tmp;
    return key_location;
}

//キーボード表示更新
void UpdateKey(HWND hWnd, keyb_t key_type, int key_location) {

    //変数初期化
    int reader = 0;
    int x1 = 0;
    int y1 = 0;
    int x2 = width + x1;
    int y2 = height + y1;
    int x_cell = key_type.horizontal;
    int y_cell = key_type.vertical;
    wchar_t Buff1[10];

    HDC hDC = GetDC(hWnd);

    // ペンとブラシの作成と選択
    SelectObject(hDC, GetStockObject(DC_PEN));
    SelectObject(hDC, GetStockObject(DC_BRUSH));

    //色指定
    SetTextColor(hDC, RGB(0x00, 0x00, 0xff));
    SetBkMode(hDC, TRANSPARENT);

    //仮想キーボード生成
    for (int var_1 = 0; var_1 < y_cell; var_1++) {
        for (int var_0 = 0; var_0 < x_cell; var_0++) {
            if (reader == key_location) {
                SetDCPenColor(hDC, RGB(0x00, 0x99, 0x66));
                SetDCBrushColor(hDC, RGB(0x00, 0xFF, 0xCC));
            }
            else {
                SetDCPenColor(hDC, RGB(0x99, 0x66, 0x00));
                SetDCBrushColor(hDC, RGB(0xFF, 0xCC, 0x00));
            }
            RoundRect(hDC, x1, y1, x2, y2, rw, rh);
            wsprintf(Buff1, L" %c", key_type.positioning[reader]);
            TextOut(hDC, x1, y1, Buff1, wcslen(Buff1));
            x1 = x1 + width + allowance_x;
            x2 = width + x1;
            reader++;
        }
        x1 = 0;
        x2 = width + x1;
        y1 = y1 + height + allowance_y;
        y2 = height + y1;
    }
    ReleaseDC(hWnd, hDC);
    return;
}

n2d_t GetDisplaySize(HWND hWnd) {
    HDC hDC = GetDC(hWnd);
    n2d_t data;
    data.x = GetDeviceCaps(hDC, HORZRES);
    data.y = GetDeviceCaps(hDC, VERTRES);
    ReleaseDC(hWnd, hDC);
    return data;
}

n2d_t GetwDisplaySize() {
    RECT rc;
    n2d_t data;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);
    data.x = rc.right;
    data.y = rc.bottom;
    return data;
}

n2d_t CalcKBSize(HWND hWnd, keyb_t key_type) {
    n2d_t data;
    LONG sx, sy;
    RECT rc1, rc2;
    GetWindowRect(hWnd, &rc1);
    GetClientRect(hWnd, &rc2);
    sx = (height + allowance_y) * key_type.horizontal - 10;
    sy = (width + allowance_x) * key_type.vertical - 10;
    sx += ((rc1.right - rc1.left) - (rc2.right - rc2.left));
    sy += ((rc1.bottom - rc1.top) - (rc2.bottom - rc2.top));
    data.x = sx;
    data.y = sy;
    return data;
}

n2d_t CalcKBPosition(HWND hWnd,keyb_t key_type) {
    n2d_t data = GetDisplaySize(hWnd);
    n2d_t key = CalcKBSize(hWnd, key_type);
    int sx = data.x;
    int sy = data.y;
    return data;
}

//ウィンドウのサイズ調整
void SetKBSize(HWND hWnd, keyb_t key_type) {
    n2d_t data = CalcKBSize(hWnd, key_type);
    SetWindowPos(hWnd, NULL, 0, 0, data.x, data.y, (SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE));
    return;
}

//ウィンドウの位置を移動
void SetKBPosition(HWND hWnd,keyb_t key_type,int mx,int my) {
    n2d_t data=CalcKBSize(hWnd,key_type);
    MoveWindow(hWnd, mx, my, data.x,data.y, TRUE);
    return;
}

//自動位置調整
void AutoKBMove(HWND hWnd,keyb_t key_type) {
    n2d_t display=GetwDisplaySize();
    n2d_t window=CalcKBSize(hWnd,key_type);
    int x = (display.x / 2) - (window.x / 2);
    int y = display.y - window.y;
    SetKBPosition(hWnd, key_type, x, y);
    return;
}