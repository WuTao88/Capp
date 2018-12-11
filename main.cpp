
#include <windows.h>
#include <tchar.h>
#include <string.h>

#include "resource.h"
using  namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static TCHAR szWindowClass[] = _T("win32app");
static TCHAR szTitle[] =_T("my app");


int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE hprevinstance,LPSTR ipCmdLine,int nCmdShow){

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hinstance;
    wcex.hIcon          = LoadIcon(hinstance, MAKEINTRESOURCE(ICON));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(ICON));


    if(!RegisterClassEx(&wcex)){
        MessageBox(NULL,
                   _T("Call to CreateWindow failed!"),
                   _T("Win32 Guided Tour"),
                   NULL);
        return 1;
    }

    HWND hWnd = CreateWindow(
            szWindowClass,
            szTitle,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            500, 400,
            NULL,
            NULL,
            hinstance,
            NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
                   _T("Call to CreateWindow failed!"),
                   _T("Win32 Guided Tour"),
                   NULL);

        return 1;
    }

    ShowWindow(hWnd,
               nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam){
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;
    POINT p;
    switch (message) {
        case WM_LBUTTONDOWN: {
            GetCursorPos(&p);

            for (int i = 0; i <100 ; ++i) {
                SetCursorPos(p.x+i,p.y+i);
                _sleep(1);
            }
        }
            break;
        case WM_CREATE:
        {
            HWND hwndButton = CreateWindow("BUTTON","你好！",
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                    200,
                    180,
                    100,
                    50,
                    hwnd,
                    (HMENU)IDB_BTN,
                    (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
                    NULL);
        }
            break;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            HBITMAP hbmp;
            HDC mdc = CreateCompatibleDC(hdc);


            hbmp = (HBITMAP) LoadImage(
                    NULL,
                    "D:\\BG.bmp",
                    IMAGE_BITMAP,
                    1100,
                    750,
                    LR_LOADFROMFILE
            );

            SelectObject(mdc, hbmp);


            BitBlt(hdc, 0, 0, 1100, 750, mdc, 0, 0, SRCCOPY);
            DeleteObject(hbmp);
            DeleteDC(mdc);
            EndPaint(hwnd, &ps);
        }
            break;
        case WM_DESTROY:
        PostQuitMessage(0);
            break;
        default:
            return  DefWindowProc(hwnd,message,wparam,lparam);
    }
    return 0;

}