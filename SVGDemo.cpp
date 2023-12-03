
#include "stdafx.h"
#include "rapidxml.hpp"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <vector>
#include <fstream>
using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

VOID OnPaint(HDC hdc)
{
    // Ref: https://docs.microsoft.com/en-us/windows/desktop/gdiplus/-gdiplus-getting-started-use
    Graphics graphics(hdc);
    //Draw Line
    Pen penLine(Color(255, 128, 0, 128)); //purple color
    graphics.DrawLine(&penLine, 0, 0, 200, 100); 

    //Draw rectangle
    int strokeWidthRectangle = 2; 
    //stroke                   opac,  r,  g, b - stroke default = 1
    Pen      penRectangle(Color(255, 0, 0, 0), strokeWidthRectangle); //black color
    SolidBrush fillRectangle(Color(60, 255, 0, 255)); //fill color
    graphics.FillRectangle(&fillRectangle, 10, 10, 200, 100);
    graphics.DrawRectangle(&penRectangle, 10, 10, 200, 100); //draw

    //Draw a polygon
    int strokeWidthPolyGon = 5;
    Pen penPolygon(Color(200, 255, 0, 255), strokeWidthPolyGon); //pink color
    SolidBrush fillPolygon(Color(60, 0, 0, 230)); //blue color
    Point hexagon[] = { Point(50, 150), Point(100, 120), Point(150, 150), Point(150, 200), Point(100,230), Point(50,200)};
    graphics.FillPolygon(&fillPolygon, hexagon, 6);
    graphics.DrawPolygon(&penPolygon, hexagon, 6);

    // Draw ellipse
    int strokeWithEllipse = 10;
    Pen penEllipse(Color(255, 255, 255, 0), strokeWithEllipse); //yellow collor
    SolidBrush fillEllipse(Color(255, 255, 255, 0)); //green fill color
    int centerXx = 300;
    int centerYy = 50;
    int radiusXx = 50;
    int radiusYy = 30;
    graphics.DrawEllipse(&penEllipse, centerXx - radiusXx, centerYy - radiusYy, 2 * radiusXx, 2 * radiusYy);
    graphics.FillEllipse(&fillEllipse, centerXx - radiusXx, centerYy - radiusYy, 2 * radiusXx, 2 * radiusYy);

    //Draw circle
    int strokeWidthCircle = 8;
    Pen penCircle(Color(255, 0, 0, 255), strokeWidthCircle); //blue color
    SolidBrush fillCircle(Color(255, 255, 255, 0)); //yellow fill color
    int centerX = 300;
    int centerY = 200;
    int radius = 70;
    graphics.DrawEllipse(&penCircle, centerX - radius, centerY - radius, 2 * radius, 2 * radius);
    graphics.FillEllipse(&fillCircle, centerX - radius, centerY - radius, 2 * radius, 2 * radius);

    //Draw star
    int strokeStar = 5;
    Pen penStar(Color(255, 255, 0, 0), strokeStar); //Red color
    SolidBrush fillStar(Color(255, 255, 255, 0)); //yellow fill color

    Point decgon[] = { Point(500, 100), Point(600, 100), Point(625, 0), Point(650, 100), Point(750,100), Point(675,150), Point(700,250),Point(625,175), Point (550,250),Point (575,150)};
    graphics.FillPolygon(&fillStar, decgon, 10);
    graphics.DrawPolygon(&penPolygon, decgon, 10);
    
    //Draw polyline
    int strokePolyline = 1;
    Pen penPolyline(Color(255, 0, 0, 255), strokePolyline);
    SolidBrush fillPolyline(Color(255, 0, 0, 255));
    Point heptgon[] = { Point(50, 300), Point(100, 300), Point(100, 360), Point(160, 360), Point(160,430), Point(230,430), Point(230,480)};
    graphics.FillPolygon(&fillPolyline, heptgon, 7);
    graphics.DrawPolygon(&penPolyline, heptgon, 7);

    //Draw polyline bậc thang (đang bug)
    int strokePolylines = 3;
    Pen penPolylines(Color(255, 255, 0, 0), strokePolylines);
    SolidBrush fillPolylines(Color(100, 0, 0, 255));
    Point gons[] = { Point(490, 400), Point(510, 400), Point(510, 390), Point (530,390), Point(530, 400), Point(550,400), Point(550,370), Point(570,370),Point(570,400), Point(590,400), Point(590,350), Point(610,350), Point(610,400), Point(630,400), Point(630,330), Point(650,330), Point(650,400), Point(670,400), Point(670,310), Point(690,310), Point(690,400), Point(710,400)};
    graphics.FillPolygon(&fillPolylines, gons, 22);
    graphics.DrawPolygon(&penPolylines, gons, 22);
   

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
    HWND                hWnd;
    MSG                 msg;
    WNDCLASS            wndClass;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    // Read XML
    xml_document<> doc;
    xml_node<>* rootNode;
    // Read the xml file into a vector
    ifstream file("sample.svg");
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0');
    // Parse the buffer using the xml file parsing library into doc 
    doc.parse<0>(&buffer[0]);

    rootNode = doc.first_node();
    xml_node<>* node = rootNode->first_node();

    while (node != NULL) {
        char* nodeName = node->name();
        xml_attribute<>* firstAttribute = node->first_attribute();
        char* attributeName = firstAttribute->name();
        char* attributeValue = firstAttribute->value();
        xml_attribute<>* secondAttribute = firstAttribute->next_attribute();
        // Set breakpoint here to view value
        // Ref: http://rapidxml.sourceforge.net/manual.html
        node = node->next_sibling();
    }



    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = TEXT("GettingStarted");

    RegisterClass(&wndClass);

    hWnd = CreateWindow(
        TEXT("GettingStarted"),   // window class name
        TEXT("SVG Demo"),  // window caption
        WS_OVERLAPPEDWINDOW,      // window style
        CW_USEDEFAULT,            // initial x position
        CW_USEDEFAULT,            // initial y position
        CW_USEDEFAULT,            // initial x size
        CW_USEDEFAULT,            // initial y size
        NULL,                     // parent window handle
        NULL,                     // window menu handle
        hInstance,                // program instance handle
        NULL);                    // creation parameters

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GdiplusShutdown(gdiplusToken);
    return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC          hdc;
    PAINTSTRUCT  ps;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        OnPaint(hdc);
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
} // WndProc