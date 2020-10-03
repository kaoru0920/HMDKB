﻿//HMDKB v1.2.0 by chocotaiyaki
//

#include <windows.h>
#include "framework.h"
#include "gamepad.h"
#include "screenkey.h"
#include "virtualoutput.h"
#include "HMDKB.h"

//記号定数
#define SCREEN_STYLE        (WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME|WS_MAXIMIZEBOX))
#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名
HANDLE hThread;

//スレッド用データ
typedef struct _PARAM {
    HWND    hWnd;
    BOOL    bFlag;
} PARAM, * LPPARAM;

PARAM Param;

//スレッド関数
DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter) {

    POINT cursor;
    UINT  uState;
    HMENU hMenu;
    MENUITEMINFO menuInfo;
    XINPUT_STATE now_pad, before_pad;
    int RStick_Speed=0;
    int LStick_Speed=0;
    bool click_flag_0=false;
    bool click_flag_1=false;
    bool windowsize_flag=false;
    bool switchTrigger = false;

    HWND hWnd = ((LPPARAM)lpParameter)->hWnd;
    hMenu = GetMenu(hWnd);
    menuInfo.cbSize = sizeof(MENUITEMINFO);
    menuInfo.fState = MFS_UNCHECKED;

    ZeroMemory(&now_pad, sizeof(XINPUT_STATE));
    ZeroMemory(&before_pad, sizeof(XINPUT_STATE));

    while (((LPPARAM)lpParameter)->bFlag) {
        before_pad = now_pad;
        updatePad(&now_pad);
        uState = GetMenuState(hMenu, IDM_LStickL, MF_BYCOMMAND);
        if (uState & MFS_CHECKED) {
            LStick_Speed = 600;
        }
        uState = GetMenuState(hMenu, IDM_LStickM, MF_BYCOMMAND);
        if (uState & MFS_CHECKED) {
            LStick_Speed = 1200;
        }
        uState = GetMenuState(hMenu, IDM_LStickS, MF_BYCOMMAND);
        if (uState & MFS_CHECKED) {
            LStick_Speed = 2400;
        }
        uState = GetMenuState(hMenu, IDM_RStickL, MF_BYCOMMAND);
        if (uState & MFS_CHECKED) {
            RStick_Speed = 500;
        }
        uState = GetMenuState(hMenu, IDM_RStickM, MF_BYCOMMAND);
        if (uState & MFS_CHECKED) {
            RStick_Speed = 1000;
        }
        uState = GetMenuState(hMenu, IDM_RStickS, MF_BYCOMMAND);
        if (uState & MFS_CHECKED) {
            RStick_Speed = 2000;
        }
        uState = GetMenuState(hMenu, IDM_SWTG, MF_BYCOMMAND);
        if (uState & MFS_CHECKED) {
            switchTrigger = true;
        }
        else {
            switchTrigger = false;
        }
        if (switchTrigger==false) {
            if (pushRTrigger(50, now_pad, before_pad) == true) {
                if (click_flag_0 == 0) {
                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                    click_flag_0 = 1;
                }
            }
            else if (checkRTrigger(50, now_pad) == false) {
                if (click_flag_0 == 1) {
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                    click_flag_0 = 0;
                }
            }
            if (pushLTrigger(50, now_pad, before_pad) == true) {
                if (click_flag_1 == 0) {
                    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                    click_flag_1 = 1;
                }
            }
            else if (checkLTrigger(50, now_pad) == false) {
                if (click_flag_1 == 1) {
                    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                    click_flag_1 = 0;
                }
            }
        }
        else {
            if (pushButton(XINPUT_GAMEPAD_RIGHT_SHOULDER, now_pad, before_pad) == true) {
                if (click_flag_0 == 0) {
                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                    click_flag_0 = 1;
                }
            }
            else if (checkButton(XINPUT_GAMEPAD_RIGHT_SHOULDER, now_pad) == false) {
                if (click_flag_0 == 1) {
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                    click_flag_0 = 0;
                }
            }
            if (pushButton(XINPUT_GAMEPAD_LEFT_SHOULDER, now_pad, before_pad) == true) {
                if (click_flag_1 == 0) {
                    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                    click_flag_1 = 1;
                }
            }
            else if (checkButton(XINPUT_GAMEPAD_LEFT_SHOULDER, now_pad) == false) {
                if (click_flag_1 == 1) {
                    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                    click_flag_1 = 0;
                }
            }
        }
        if (checkRStick(now_pad) == true) {
            stick2d now_rstick = numRStick(now_pad);
            if (checkButton(XINPUT_GAMEPAD_RIGHT_THUMB, now_pad)) {
                moveWheel((now_rstick.vertical) / RStick_Speed);
            }
            else {
                moveWheel((now_rstick.vertical) / (RStick_Speed * 2));
            }
        }
        if (checkLStick(now_pad) == true) {
            stick2d now_lstick = numLStick(now_pad);
            GetCursorPos(&cursor);
            if (checkButton(XINPUT_GAMEPAD_LEFT_THUMB, now_pad)) {
                cursor.x = cursor.x + (now_lstick.horizontal) / LStick_Speed;
                cursor.y = cursor.y - (now_lstick.vertical) / LStick_Speed;
            }
            else {
                cursor.x = cursor.x + (now_lstick.horizontal) / (LStick_Speed*2);
                cursor.y = cursor.y - (now_lstick.vertical) / (LStick_Speed*2);
            }
            SetCursorPos(cursor.x, cursor.y);
        }
        Sleep(5);
    }
    ExitThread(0);
}

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HMDKB, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HMDKB));

    MSG msg;

    // メイン メッセージ ループ:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HMDKB));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HMDKB);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, SCREEN_STYLE,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hDC;
    PAINTSTRUCT ps;
    static HMENU hMenu;
    static MENUITEMINFO menuInfo;
    UINT uState;
    static XINPUT_STATE now_pad;
    static XINPUT_STATE before_pad;
    static keyb_t key_tmp;
    static int key_location = 0;
    static int key_number = 0;
    static bool switchTrigger=false;

    switch (message)
    {
    case WM_CREATE:
        {
            key_location = 0;
            key_number = 0;
            key_tmp = US_S;
            hMenu=GetMenu(hWnd);
            menuInfo.cbSize = sizeof(MENUITEMINFO);
            menuInfo.fState = MFS_UNCHECKED;
            ZeroMemory(&now_pad, sizeof(XINPUT_STATE));
            ZeroMemory(&before_pad, sizeof(XINPUT_STATE));
            CheckMenuRadioItem(hMenu, IDM_RStickL, IDM_RStickS,IDM_RStickM, MF_BYCOMMAND);
            CheckMenuRadioItem(hMenu, IDM_LStickL, IDM_LStickS,IDM_LStickM, MF_BYCOMMAND);
            initButton(now_pad, before_pad);//Pad初期化
            SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, (SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW));
            SetTimer(hWnd, 1, 1, NULL); 
            Param.hWnd = hWnd;
            Param.bFlag = TRUE;//スレッド起動
            hThread = CreateThread(NULL, 0, ThreadProc, (LPVOID)&Param, 0, NULL);
            InvalidateRect(hWnd, NULL, FALSE);
            AutoKBMove(hWnd, key_tmp);
            return 0;
        }
    case WM_PAINT:
        {
            hDC = BeginPaint(hWnd, &ps);
            UpdateKey(hWnd, key_tmp, key_location);
            EndPaint(hWnd, &ps);
            return 0;
        }
    case WM_TIMER:
        {
            before_pad = now_pad;
            updatePad(&now_pad);
            if (pushButton(XINPUT_GAMEPAD_A, now_pad, before_pad) == true) {
                KeyAction_Set(key_tmp.vtukey[key_location]);
            }
            else if (pushButton(XINPUT_GAMEPAD_B, now_pad, before_pad) == true) {
                KeyAction(VK_SPACE, 0);
            }
            else if (pushButton(XINPUT_GAMEPAD_X, now_pad, before_pad) == true) {
                KeyAction(VK_BACK, 0);
            }
            else if (pushButton(XINPUT_GAMEPAD_Y, now_pad, before_pad) == true) {
                if (IsIconic(hWnd)==TRUE) {
                    ShowWindow(hWnd,SW_RESTORE);
                }
                else {
                    ShowWindow(hWnd, SW_MINIMIZE);
                }
            }
            
            else if (pushButton(XINPUT_GAMEPAD_START, now_pad, before_pad) == true) {
                KeyAction(VK_RETURN, 0);
            }
            else if (pushButton(XINPUT_GAMEPAD_BACK, now_pad, before_pad) == true) {
                KeyAction(VK_OEM_AUTO, 0);
            }
            else if (pushButton(XINPUT_GAMEPAD_DPAD_LEFT, now_pad, before_pad) == true) {
                key_location = MoveCursor(3, key_tmp, key_location);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            else if (pushButton(XINPUT_GAMEPAD_DPAD_RIGHT, now_pad, before_pad) == true) {
                key_location = MoveCursor(1, key_tmp, key_location);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            else if (pushButton(XINPUT_GAMEPAD_DPAD_UP, now_pad, before_pad) == true) {
                key_location = MoveCursor(0, key_tmp, key_location);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            else if (pushButton(XINPUT_GAMEPAD_DPAD_DOWN, now_pad, before_pad) == true) {
                key_location = MoveCursor(2, key_tmp, key_location);
                InvalidateRect(hWnd, NULL, FALSE);
            }
            if (switchTrigger==true) {
                if (pushRTrigger(50, now_pad, before_pad) == true) {
                    key_number++;
                    if (key_number > 3) {
                        key_number = 0;
                    }
                    key_location = 0;
                    key_tmp = ChangeKey(key_number);
                    SetKBSize(hWnd, key_tmp);
                    AutoKBMove(hWnd, key_tmp);
                    InvalidateRect(hWnd, NULL, FALSE);
                }
                else if (pushLTrigger(50, now_pad, before_pad) == true) {
                    key_number--;
                    if (key_number < 0) {
                        key_number = 3;
                    }
                    key_location = 0;
                    key_tmp = ChangeKey(key_number);
                    SetKBSize(hWnd, key_tmp);
                    AutoKBMove(hWnd, key_tmp);
                    InvalidateRect(hWnd, NULL, FALSE);
                }
            }
            else {
                if (pushButton(XINPUT_GAMEPAD_RIGHT_SHOULDER, now_pad, before_pad) == true) {
                key_number++;
                if (key_number > 3) {
                    key_number = 0;
                }
                key_location = 0;
                key_tmp = ChangeKey(key_number);
                SetKBSize(hWnd, key_tmp);
                AutoKBMove(hWnd, key_tmp);
                InvalidateRect(hWnd, NULL, FALSE);
            }
                else if (pushButton(XINPUT_GAMEPAD_LEFT_SHOULDER, now_pad, before_pad) == true) {
                    key_number--;
                    if (key_number < 0) {
                        key_number = 3;
                    }
                    key_location = 0;
                    key_tmp = ChangeKey(key_number);
                    SetKBSize(hWnd, key_tmp);
                    AutoKBMove(hWnd, key_tmp);
                    InvalidateRect(hWnd, NULL, FALSE);
                }
            }
        }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDM_RStickS:
            case IDM_RStickM:
            case IDM_RStickL:
                CheckMenuRadioItem(hMenu, IDM_RStickL,IDM_RStickS,LOWORD(wParam), MF_BYCOMMAND);
                break;
            case IDM_LStickS:
            case IDM_LStickM:
            case IDM_LStickL:
                CheckMenuRadioItem(hMenu, IDM_LStickL, IDM_LStickS, LOWORD(wParam), MF_BYCOMMAND);
                break;
            case IDM_SWTG:
                uState = GetMenuState(hMenu, IDM_SWTG, MF_BYCOMMAND);
                if (uState & MFS_CHECKED) {
                    //チェックされてたからチェックはずす
                    CheckMenuItem(hMenu, IDM_SWTG, MF_BYCOMMAND | MFS_UNCHECKED);
                    switchTrigger = false;
                }
                else {
                    //チェックされてなかったからチェックする
                    CheckMenuItem(hMenu, IDM_SWTG, MF_BYCOMMAND | MFS_CHECKED);
                    switchTrigger = true;
                }
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
        }
    case WM_DESTROY:
        CloseHandle(hThread);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
