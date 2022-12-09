#include<iostream>
#include<windows.h>
using namespace std;
int main()
{
    POINT pt;
    GetCursorPos(&pt);
    HWND hwnd=GetForegroundWindow();
    ScreenToClient(hwnd,&pt);
    HANDLE hCon=GetStdHandle(STD_OUTPUT_HANDLE);
    // 定义 CONSOLE_FONT_INFOEX 结构体，用于保存控制台字体信息
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);

    // 获取控制台当前字体信息
    GetCurrentConsoleFontEx(hCon, false, &cfi);

    cout<<cfi.dwFontSize.X<<' '<<cfi.dwFontSize.Y<<endl;
    getchar();
}