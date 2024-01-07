// SVG_Reader.cpp : Defines the entry point for the application.
//

#include "Lib.h"
#include "SVG_Reader.h"

#define MAX_LOADSTRING 100

struct CMD {
    string FileInput;
};

float offsetX = 0, offsetY = 0, zoomFactor = 1.0;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
float scale = 1.0;
float Rotate = 0;
float scroll_x = 0;
float scroll_y = 0;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int, CMD*);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    //Command Line
    wstring ws(lpCmdLine);
    CMD* cmdLine = new CMD;
    cmdLine->FileInput = string(ws.begin(), ws.end());

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SVGREADER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow, cmdLine))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SVGREADER));

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

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SVGREADER));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SVGREADER);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, CMD* cmdLine)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, cmdLine);

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
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplustoken;
    GdiplusStartup(&gdiplustoken, &gdiplusStartupInput, nullptr);

    CMD* cmdLine;
    LONG_PTR ptr;
    if (message == WM_CREATE)
    {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        cmdLine = reinterpret_cast<CMD*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)cmdLine);
    }

    bool is_dragging = false;
    POINT last_mouse_position;

    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDM_ZOOM_IN:
            scale *= 1.1;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        case IDM_ZOOM_OUT:
            scale *= 0.9;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        case IDM_DEFAULT:
            scale = 1;
            Rotate = 0;
            scroll_x = 0;
            scroll_y = 0;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        case IDM_ROTATE_LEFT:
            Rotate -= 30;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        case IDM_ROTATE_RIGHT:
            Rotate += 30;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        case IDM_UP:
            scroll_y -= 20;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        case IDM_DOWN:
            scroll_y += 20;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        case IDM_RIGHT:
            scroll_x += 20;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        case IDM_LEFT:
            scroll_x -= 20;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_UP:
            scroll_y -= 200;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        case VK_DOWN:
            scroll_y += 200;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        case VK_LEFT:
            scroll_x -= 200;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        case VK_RIGHT:
            scroll_x += 200;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        case 'i': case 'I':
            scale *= 1.1;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        case 'o': case 'O':
            scale *= 0.9;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        case 'r': case 'R':
            Rotate += 1;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        case 'l': case 'L':
            Rotate -= 1;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        case 'd': case 'D':
            scale = 1;
            Rotate = 0;
            scroll_x = 0;
            scroll_y = 0;
            InvalidateRect(hWnd, NULL, TRUE);
            goto DrawAgain;
            break;
        }
    }
    break;
    case WM_MOUSEWHEEL:
    {
        short delta = GET_WHEEL_DELTA_WPARAM(wParam);
        if (delta > 0)
            scale *= 1.1;
        else
            scale *= 0.9;
        InvalidateRect(hWnd, NULL, TRUE);
        goto DrawAgain;
    }
    break;
    case WM_PAINT:
    {
    DrawAgain:
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        ptr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
        cmdLine = reinterpret_cast<CMD*>(ptr);
        image img(cmdLine->FileInput);
        parser parseTool;
        renderer renderTool;
        viewbox* vb = new viewbox();
        img.parseImage(parseTool, *vb);

        float Width = vb->getPortWidth();
        float Height = vb->getPortHeight();
        float scaleX = 1, scaleY = 1, scaleXY = 1;
        
        RECT window;
        GetWindowRect(hWnd, &window);

        if (Width == 0 || Height == 0) {
            Width = window.right - window.left - 16;
            Height = window.bottom - window.top - 39;
        }

        float tmpX = 0, tmpY = 0;
        if (vb->getViewWidth() && vb->getViewHeight())
        {
            scaleX = Width / vb->getViewWidth();
            scaleY = Height / vb->getViewHeight();
            scaleXY = (scaleX < scaleY) ? scaleX : scaleY;
            tmpX = (Width - vb->getViewWidth() * scaleXY) / 2;
            tmpY = (Height - vb->getViewHeight() * scaleXY) / 2;
        }
        if (Width && Height && vb->getViewWidth() && vb->getViewHeight()) {
            scaleX = Width / vb->getViewWidth();
            scaleY = Height / vb->getViewHeight();
            scaleXY = (scaleX < scaleY) ? scaleX : scaleY;
        }
        static bool loop = true;
        if (loop && vb->getViewWidth() && vb->getViewHeight()) {
            scroll_x += abs(Width - vb->getViewWidth() * scaleXY) / 2;
            scroll_y += abs(Height - vb->getViewHeight() * scaleXY) / 2;
            loop = false;
        }

        Graphics graphics(hdc);
        graphics.RotateTransform(Rotate);
        graphics.TranslateTransform(scroll_x, scroll_y);
        if (vb->getViewHeight() != 0 || vb->getViewWidth() != 0)
            graphics.SetClip(Gdiplus::RectF(0, 0, Width * scale, Height * scale));
        graphics.ScaleTransform(scale * scaleXY, scale * scaleXY);

        graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
        graphics.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
        graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
        graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);

        img.renderImage(renderTool, graphics);

        EndPaint(hWnd, &ps);
        delete vb;
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    GdiplusShutdown(gdiplustoken);
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