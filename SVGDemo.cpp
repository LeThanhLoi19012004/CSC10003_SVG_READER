
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
float zoomFactor = 1.0f; // Tỷ lệ zoom mặc định
float viewBoxX = 0.0f, viewBoxY = 0.0f, viewBoxWidth = 800.0f, viewBoxHeight = 600.0f; // Giá trị viewBox mặc định


// Hàm di chuyển đa giác
void MovePolygon(Point* polygon, int numPoints, float offsetX, float offsetY)
{
    for (int i = 0; i < numPoints; ++i)
    {
        polygon[i].X += offsetX;
        polygon[i].Y += offsetY;
    }
}
VOID OnPaint(HDC hdc)
{
    // Ref: https://docs.microsoft.com/en-us/windows/desktop/gdiplus/-gdiplus-getting-started-use
    Graphics graphics(hdc);
    // Xóa nền của cửa sổ
    SolidBrush backgroundBrush(Color(255, 255, 255)); // Chọn màu nền (trắng trong trường hợp này)
    graphics.FillRectangle(&backgroundBrush, 0, 0, 2000, 2000);

    // Tính toán các tham số dựa trên giá trị viewBox
    float offsetX = -viewBoxX * zoomFactor;
    float offsetY = -viewBoxY * zoomFactor;

    // Khởi tạo ma trận biến đổi
    Matrix transformationMatrix;

    // Tọa độ x và y của điểm trung tâm bạn muốn zoom
    float centerXzoom = 100.0f;
    float centerYzoom = 100.0f;
    // Di chuyển tâm của ma trận biến đổi về điểm muốn zoom
    transformationMatrix.Translate(centerXzoom, centerYzoom);
    // Áp dụng tỷ lệ zoom
    transformationMatrix.Scale(zoomFactor, zoomFactor);
    // Di chuyển lại ma trận biến đổi để đưa tâm về vị trí ban đầu
    transformationMatrix.Translate(-centerXzoom, -centerYzoom);
    // Áp dụng ma trận biến đổi cho đối tượng Graphics
    graphics.SetTransform(&transformationMatrix);

    //Draw Line
    Pen penLine(Color(255, 128, 0, 128)); //purple color
    graphics.DrawLine(&penLine, 0.0f + offsetX, 0.0f + offsetY, 200.0f + offsetX, 100.0f + offsetY);
    //graphics.DrawLine(&penLine, 0, 0, 200, 100); 

    // Vẽ các hình ảnh với sự điều chỉnh dựa trên giá trị viewBox
    // Draw Rectangle
    int strokeWidthRectangle = 2;
    Pen penRectangle(Color(255, 0, 0, 0), strokeWidthRectangle); //black color
    SolidBrush fillRectangle(Color(60, 255, 0, 255));// fill color
    graphics.FillRectangle(&fillRectangle, 10 + offsetX, 10 + offsetY, 200.0f, 100.0f);
    graphics.DrawRectangle(&penRectangle, 10 + offsetX, 10 + offsetY, 200.0f, 100.0f);

    //graphics.FillRectangle(&fillRectangle, 10, 10, 200, 100);
    //graphics.DrawRectangle(&penRectangle, 10, 10, 200, 100); //draw

    //Draw a polygon
    int strokeWidthPolyGon = 5;
    Pen penPolygon(Color(200, 255, 0, 255), strokeWidthPolyGon); //pink color
    SolidBrush fillPolygon(Color(60, 0, 0, 230)); //blue color
    Point hexagon[] = { Point(50, 150), Point(100, 120), Point(150, 150), Point(150, 200), Point(100,230), Point(50,200)};
    MovePolygon(hexagon, 6, offsetX, offsetY);
    graphics.FillPolygon(&fillPolygon, hexagon, 6);
    graphics.DrawPolygon(&penPolygon, hexagon, 6);

    // Draw ellipse
    int strokeWithEllipse = 10;
    Pen penEllipse(Color(255, 255, 255, 0), strokeWithEllipse); //yellow collor
    SolidBrush fillEllipse(Color(255, 255, 255, 0)); //green fill color
    float centerXx = 300;
    float centerYy = 50;
    float radiusXx = 50;
    float radiusYy = 30;
    graphics.DrawEllipse(&penEllipse, centerXx - radiusXx + offsetX, centerYy - radiusYy + offsetY, 2.0f * radiusXx, 2.0f * radiusYy);
    graphics.FillEllipse(&fillEllipse, centerXx - radiusXx + offsetX, centerYy - radiusYy + offsetY, 2.0f * radiusXx, 2.0f * radiusYy);

    //graphics.DrawEllipse(&penEllipse, centerXx - radiusXx, centerYy - radiusYy, 2 * radiusXx, 2 * radiusYy);
    //graphics.FillEllipse(&fillEllipse, centerXx - radiusXx, centerYy - radiusYy, 2 * radiusXx, 2 * radiusYy);

    //Draw circle
    int strokeWidthCircle = 8;
    Pen penCircle(Color(255, 0, 0, 255), strokeWidthCircle); //blue color
    SolidBrush fillCircle(Color(255, 255, 255, 0)); //yellow fill color
    float centerX = 300;
    float centerY = 200;
    float radius = 70;
    graphics.DrawEllipse(&penCircle, centerX - radius + offsetX, centerY - radius + offsetY, 2.0f * radius, 2.0f * radius);
    graphics.FillEllipse(&fillCircle, centerX - radius + offsetX, centerY - radius + offsetY, 2.0f * radius, 2.0f * radius);

    //graphics.DrawEllipse(&penCircle, centerX - radius, centerY - radius, 2 * radius, 2 * radius);
    //graphics.FillEllipse(&fillCircle, centerX - radius, centerY - radius, 2 * radius, 2 * radius);

    //Draw star
    int strokeStar = 5;
    Pen penStar(Color(255, 255, 0, 0), strokeStar); //Red color
    SolidBrush fillStar(Color(255, 255, 255, 0)); //yellow fill color

    Point decgon[] = { Point(500, 100), Point(600, 100), Point(625, 0), Point(650, 100), Point(750,100), Point(675,150), Point(700,250),Point(625,175), Point (550,250),Point (575,150)};
    MovePolygon(decgon, 10, offsetX, offsetY);
    graphics.FillPolygon(&fillStar, decgon, 10);
    graphics.DrawPolygon(&penPolygon, decgon, 10);
    
    //Draw polyline
    int strokePolyline = 1;
    Pen penPolyline(Color(255, 0, 0, 0), strokePolyline);
    SolidBrush fillPolyline(Color(255, 0, 0, 255));
    Point heptgon[] = { Point(50, 300), Point(100, 300), Point(100, 360), Point(160, 360), Point(160,430), Point(230,430), Point(230,480)};
    //Point heptgon[] = {Point(100,100), Point(100,400), Point(600,100), Point(500,500), Point(50,200), Point(550,250)};
    MovePolygon(heptgon, 7, offsetX, offsetY);
    graphics.FillPolygon(&fillPolyline, heptgon, 7);
    graphics.DrawPolygon(&penPolyline, heptgon, 7);

    //Draw polyline biểu đồ (đang bug)
    int strokePolylines = 3;
    Pen penPolylines(Color(255, 255, 0, 0), strokePolylines);
    SolidBrush fillPolylines(Color(100, 0, 0, 255));
    Point gons[] = { Point(490, 400), Point(510, 400), Point(510, 390), Point (530,390), Point(530, 400), Point(550,400), Point(550,370), Point(570,370),Point(570,400), Point(590,400), Point(590,350), Point(610,350), Point(610,400), Point(630,400), Point(630,330), Point(650,330), Point(650,400), Point(670,400), Point(670,310), Point(690,310), Point(690,400), Point(710,400)};
    //graphics.FillPolygon(&fillPolylines, gons, 22);
    //graphics.DrawPolygon(&penPolylines, gons, 22);
   
    // Tạo ma trận biến đổi
    //Matrix transformationMatrix;

    // Áp dụng biến đổi: góc quay 45 độ, dịch chuyển theo trục X và Y, tỷ lệ scale 2 lần
    //transformationMatrix.Rotate(45.0f);
    //transformationMatrix.Translate(100.0f,50.0f);
    //transformationMatrix.Rotate(-45.0f);
    //transformationMatrix.Scale(2.0f, 2.0f);

    // Áp dụng ma trận biến đổi cho đối tượng Graphics
    //graphics.SetTransform(&transformationMatrix);

    // Vẽ hình trước khi áp dụng biến đổi
    //SolidBrush fillRed(Color(255, 0, 0));
    //graphics.FillRectangle(&fillRed, 50, 50, 50, 50);

    // Reset ma trận biến đổi để vẽ các hình tiếp theo mà không bị ảnh hưởng
    //transformationMatrix.Reset();
    //graphics.SetTransform(&transformationMatrix);

    // Vẽ hình sau khi áp dụng biến đổi
    SolidBrush fillBlue(Color(0, 0, 255));
    //graphics.FillRectangle(&fillBlue, 10, 10, 50, 50);



    // Vẽ văn bản
    Font font(L"Times New Roman", 25); // Chọn font và kích thước
    SolidBrush textBrush(Color(255, 0, 255)); // Màu văn bản (hồng)
    // Đoạn văn bản cần vẽ
    wstring textToDraw = L"Nguyen Van A";
    // Vị trí để vẽ văn bản
    PointF textPosition(400.0f + offsetX, 300.0f + offsetY);
    //PointF textPosition(400.0f, 300.0f);
    // Tạo đối tượng StringFormat để cấu hình canh lề
    StringFormat stringFormat;

    // Đặt canh lề theo chiều ngang
    //stringFormat.SetAlignment(StringAlignmentNear);    // Canh lề về phía trái
    //stringFormat.SetAlignment(StringAlignmentCenter);  // Canh giữa
    //stringFormat.SetAlignment(StringAlignmentFar);     // Canh lề về phía phải

    // Đặt canh lề theo chiều dọc
    //stringFormat.SetLineAlignment(StringAlignmentNear);    // Canh lề lên trên
    //stringFormat.SetLineAlignment(StringAlignmentCenter);  // Canh giữa
    //stringFormat.SetLineAlignment(StringAlignmentFar);     // Canh lề xuống dưới

    // Vẽ văn bản
    //graphics.DrawString(textToDraw.c_str(), textToDraw.size(), &font, textPosition, &stringFormat, &textBrush);
    graphics.DrawString(textToDraw.c_str(), textToDraw.size(), &font, textPosition, &stringFormat, &textBrush);
    // Reset ma trận biến đổi để vẽ các hình tiếp theo mà không bị ảnh hưởng
    transformationMatrix.Reset();
    graphics.SetTransform(&transformationMatrix);

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
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ADD:
            zoomFactor *= 1.5f; //Tỉ lệ zoom 50%
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE); // Gọi hàm vẽ lại cửa sổ
            break;
        case VK_SUBTRACT:
            zoomFactor /= 1.5f;
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
            break;
        case VK_LEFT:
            viewBoxX -= 10.0f / zoomFactor;
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
            break;
        case VK_RIGHT:
            viewBoxX += 10.0f / zoomFactor;
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
            break;
        case VK_UP:
            viewBoxY -= 10.0f / zoomFactor;
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
            break;
        case VK_DOWN:
            viewBoxY += 10.0f / zoomFactor;
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
            break;
        default:
            break;
        }
        return 0;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
} // WndProc