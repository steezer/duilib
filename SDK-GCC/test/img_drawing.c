#include <windows.h>
#include <gdiplus.h>
#include <stdio.h>

using namespace Gdiplus;

void drawPNG (HWND hwnd, unsigned xpos, unsigned ypos, char * rid) {

    PAINTSTRUCT ps;
    HDC dc = BeginPaint (hwnd, &ps);

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    Rect rect(20,20,50,50);
    Graphics grpx(dc);
    Image* image = new Image(L"SomePhoto.png");
    grpx.DrawImage(image,rect);

    delete image;

    GdiplusShutdown(gdiplusToken);

    EndPaint(hwnd, &ps);

}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	
	return 0;
}
