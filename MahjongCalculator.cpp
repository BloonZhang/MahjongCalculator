// MahjongCalculator.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "MahjongCalculator.h"
#include "Storage.hpp"
#include <map>
#include <vector>
#include <string>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
Storage myStorage;                              // Storage class
std::map<const wchar_t*, HBITMAP> bitmapMap;    // contains bitmaps for all tiles
std::vector<const wchar_t*> tilesInHand;        // contains tiles in hand

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
// helper functions
VOID                CreateTileButton(HWND, HMENU, const wchar_t*, int, int);
VOID                CreateButtons(HWND);
VOID                DrawTileBitmap(HDC, const wchar_t*, int);
BOOL                AddTileToHand(const wchar_t*);
VOID                Reset(HDC);
VOID                PrintText(HDC, std::wstring);
VOID                LoadBitmapMap();
VOID                DeleteBitmapMap();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MAHJONGCALCULATOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    // Load bitmaps
    LoadBitmapMap();

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MAHJONGCALCULATOR));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAHJONGCALCULATOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MAHJONGCALCULATOR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 885, 610, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        CreateButtons(hWnd);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            // Tiles
            case TILE_1M:
                if (AddTileToHand(L"1m")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_2M:
                if (AddTileToHand(L"2m")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_3M:
                if (AddTileToHand(L"3m")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_4M:
                if (AddTileToHand(L"4m")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_5M:
                if (AddTileToHand(L"5m")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_6M:
                if (AddTileToHand(L"6m")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_7M:
                if (AddTileToHand(L"7m")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_8M:
                if (AddTileToHand(L"8m")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_9M:
                if (AddTileToHand(L"9m")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_1P:
                if (AddTileToHand(L"1p")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_2P:
                if (AddTileToHand(L"2p")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_3P:
                if (AddTileToHand(L"3p")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_4P:
                if (AddTileToHand(L"4p")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_5P:
                if (AddTileToHand(L"5p")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_6P:
                if (AddTileToHand(L"6p")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_7P:
                if (AddTileToHand(L"7p")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_8P:
                if (AddTileToHand(L"8p")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_9P:
                if (AddTileToHand(L"9p")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_1S:
                if (AddTileToHand(L"1s")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_2S:
                if (AddTileToHand(L"2s")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_3S:
                if (AddTileToHand(L"3s")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_4S:
                if (AddTileToHand(L"4s")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_5S:
                if (AddTileToHand(L"5s")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_6S:
                if (AddTileToHand(L"6s")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_7S:
                if (AddTileToHand(L"7s")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_8S:
                if (AddTileToHand(L"8s")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_9S:
                if (AddTileToHand(L"9s")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_EW:
                if (AddTileToHand(L"ew")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_SW:
                if (AddTileToHand(L"sw")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_WW:
                if (AddTileToHand(L"ww")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_NW:
                if (AddTileToHand(L"nw")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_WD:
                if (AddTileToHand(L"wd")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_GD:
                if (AddTileToHand(L"gd")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_RD:
                if (AddTileToHand(L"rd")) {
                    RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE);
                }
                break;
            case TILE_RESET:
                myStorage.Reset();
                Reset(GetDC(hWnd));
                RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE);
                break;
            case TILE_CALCULATE:
            {
                std::wstring message;
                myStorage.Calculate(message);

                MessageBox(hWnd, message.c_str(), nullptr, MB_OK);
                //PrintText(GetDC(hWnd), message);
            }
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            int count = 0;
            for (const wchar_t* tile : tilesInHand)
            {
                DrawTileBitmap(hdc, tile, count);
                ++count;
            }
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        DeleteBitmapMap();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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


//
//  FUNCTION: CreateTileButton(HWND, HMENU, const wchar_t*, const wchar_t*, int, int)
//
//  PURPOSE: Creates a button at the specified x and y
//
VOID CreateTileButton(HWND hWnd, HMENU identifier, const wchar_t* tile, int x, int y)
{
    HWND myButton;
    myButton = CreateWindowW(L"BUTTON", tile,
        WS_VISIBLE | WS_CHILD | BS_BITMAP,
        x, y, 55, 88,
        hWnd, identifier, nullptr, nullptr);
    SendMessageW(myButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmapMap[tile]);
}
//
//  FUNCTION: CreateButtons(HWND)
//
//  PURPOSE: Sets up buttons for all tiles
//
VOID CreateButtons(HWND hWnd)
{
    CreateWindowW(L"BUTTON", L"RESET",
        WS_VISIBLE | WS_CHILD,
        750, 10, 90, 50,
        hWnd, (HMENU)TILE_RESET, nullptr, nullptr);
    CreateWindowW(L"BUTTON", L"CALCULATE",
        WS_VISIBLE | WS_CHILD,
        750, 100, 90, 50,
        hWnd, (HMENU)TILE_CALCULATE, nullptr, nullptr);
    int startingX = 20;
    int incrementX = 60;
    int startingY = 10;
    int incrementY = 90;
    CreateTileButton(hWnd, (HMENU)TILE_1M, L"1m", startingX, startingY);
    CreateTileButton(hWnd, (HMENU)TILE_2M, L"2m", startingX + 1 * incrementX, startingY);
    CreateTileButton(hWnd, (HMENU)TILE_3M, L"3m", startingX + 2 * incrementX, startingY);
    CreateTileButton(hWnd, (HMENU)TILE_4M, L"4m", startingX + 3 * incrementX, startingY);
    CreateTileButton(hWnd, (HMENU)TILE_5M, L"5m", startingX + 4 * incrementX, startingY);
    CreateTileButton(hWnd, (HMENU)TILE_6M, L"6m", startingX + 5 * incrementX, startingY);
    CreateTileButton(hWnd, (HMENU)TILE_7M, L"7m", startingX + 6 * incrementX, startingY);
    CreateTileButton(hWnd, (HMENU)TILE_8M, L"8m", startingX + 7 * incrementX, startingY);
    CreateTileButton(hWnd, (HMENU)TILE_9M, L"9m", startingX + 8 * incrementX, startingY);
    CreateTileButton(hWnd, (HMENU)TILE_1P, L"1p", startingX, startingY + 1 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_2P, L"2p", startingX + 1 * incrementX, startingY + 1 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_3P, L"3p", startingX + 2 * incrementX, startingY + 1 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_4P, L"4p", startingX + 3 * incrementX, startingY + 1 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_5P, L"5p", startingX + 4 * incrementX, startingY + 1 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_6P, L"6p", startingX + 5 * incrementX, startingY + 1 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_7P, L"7p", startingX + 6 * incrementX, startingY + 1 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_8P, L"8p", startingX + 7 * incrementX, startingY + 1 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_9P, L"9p", startingX + 8 * incrementX, startingY + 1 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_1S, L"1s", startingX, startingY + 2 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_2S, L"2s", startingX + 1 * incrementX, startingY + 2 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_3S, L"3s", startingX + 2 * incrementX, startingY + 2 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_4S, L"4s", startingX + 3 * incrementX, startingY + 2 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_5S, L"5s", startingX + 4 * incrementX, startingY + 2 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_6S, L"6s", startingX + 5 * incrementX, startingY + 2 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_7S, L"7s", startingX + 6 * incrementX, startingY + 2 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_8S, L"8s", startingX + 7 * incrementX, startingY + 2 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_9S, L"9s", startingX + 8 * incrementX, startingY + 2 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_EW, L"ew", startingX, startingY + 3 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_SW, L"sw", startingX + 1 * incrementX, startingY + 3 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_WW, L"ww", startingX + 2 * incrementX, startingY + 3 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_NW, L"nw", startingX + 3 * incrementX, startingY + 3 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_WD, L"wd", startingX + 4 * incrementX, startingY + 3 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_GD, L"gd", startingX + 5 * incrementX, startingY + 3 * incrementY);
    CreateTileButton(hWnd, (HMENU)TILE_RD, L"rd", startingX + 6 * incrementX, startingY + 3 * incrementY);


}
//
//  FUNCTION: DrawTileBitmap(hdc, const wchar_t*, int)
//
//  PURPOSE: Draws a tile bitmap at the position corresponding to the number
//
VOID DrawTileBitmap(HDC hdc, const wchar_t* tile, int pos)
{
    int startingX = 20;
    int incrementX = 60;
    int Y = 450;
    HDC hdcMem = CreateCompatibleDC(hdc);
    BITMAP bitmapInfo;
    HBITMAP bitmap = bitmapMap[tile];
    HBITMAP bitmapOld = (HBITMAP)SelectObject(hdcMem, bitmap);
    GetObject(bitmap, sizeof(bitmapInfo), &bitmapInfo);
    BitBlt(hdc, startingX + pos * incrementX, Y, bitmapInfo.bmWidth, bitmapInfo.bmHeight, hdcMem, 0, 0, SRCCOPY);

    SelectObject(hdcMem, bitmapOld); DeleteDC(hdcMem);
}
//
//  FUNCTION: AddTileToHand(const wchar_t*)
//
//  PURPOSE: Adds a tile to the hand
//  RETURN:  true if success, false if fail
//
BOOL AddTileToHand(const wchar_t* tile)
{
    if (tilesInHand.size() < 0 || tilesInHand.size() >= 14)
    {
        return false;
    }
    myStorage.Add(tile);
    tilesInHand.push_back(tile);
    return true;
}
//
//  FUNCTION: Reset(HDC)
//
//  PURPOSE: Erases all tiles and removes them from Storage
//
VOID Reset(HDC hdc)
{
    tilesInHand.clear();
}
//
//  FUNCTION: PrintText(HDc, std::wstring)
//
//  PURPOSE: Prints a string to the window
//
VOID PrintText(HDC hdc, std::wstring message)
{
    // get font

}
//
//  FUNCTION: LoadBitmapMap()
//
//  PURPOSE: Loads the bitmap map for all the tiles
//
VOID LoadBitmapMap()
{
    bitmapMap[L"1m"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\1m.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"2m"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\2m.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"3m"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\3m.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"4m"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\4m.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"5m"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\5m.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"6m"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\6m.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"7m"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\7m.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"8m"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\8m.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"9m"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\9m.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"1p"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\1p.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"2p"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\2p.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"3p"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\3p.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"4p"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\4p.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"5p"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\5p.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"6p"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\6p.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"7p"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\7p.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"8p"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\8p.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"9p"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\9p.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"1s"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\1s.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"2s"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\2s.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"3s"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\3s.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"4s"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\4s.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"5s"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\5s.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"6s"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\6s.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"7s"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\7s.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"8s"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\8s.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"9s"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\9s.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"ew"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\ew.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"sw"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\sw.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"ww"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\ww.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"nw"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\nw.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"wd"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\wd.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"gd"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\gd.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
    bitmapMap[L"rd"] = (HBITMAP)LoadImageW(nullptr, L"Tiles\\rd.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_LOADFROMFILE);
}
//
//  FUNCTION: DeleteBitmapMap()
//
//  PURPOSE: Deletes the bitmap map for all the tiles
//
VOID DeleteBitmapMap()
{
    for (std::map< const wchar_t*, HBITMAP>::iterator it = bitmapMap.begin(); it != bitmapMap.end(); ++it)
    {
        DeleteObject(it->second);
    }
}