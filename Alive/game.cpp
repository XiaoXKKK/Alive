#include"game.h"

COORD coord;
HANDLE hCon;
void Setcolor(Color c) {
    if (hCon == NULL)
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, c);
}
void Locate(int x, int y) {
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    y = y * 2 - 1;
    coord.X = y - 1;
    coord.Y = x - 1;
    SetConsoleCursorPosition(hout, coord);
}

void W(int x, int y, std::string s) {
    Locate(x, y);
    std::cout << s;
}

int winx, winy;
void Winset(int x, int y) {
    winx = y;
    winy = x;
    RECT rect;
    HWND hwnd = GetForegroundWindow();
    GetWindowRect(hwnd, &rect);
    int title_high = GetSystemMetrics(SM_CYCAPTION);   //窗口标题栏高度
    int line_wight = GetSystemMetrics(SM_CYSIZEFRAME)
        + GetSystemMetrics(SM_CYBORDER);   //窗口边框宽度
    MoveWindow(hwnd, y - line_wight, x - title_high - line_wight, rect.right - rect.left, rect.bottom - rect.top, TRUE);
}

Mos Getmouse() {
    POINT pt;
    GetCursorPos(&pt);
    HWND hwnd = GetForegroundWindow();
    ScreenToClient(hwnd, &pt);
    Mos res;

    // 定义 CONSOLE_FONT_INFOEX 结构体，用于保存控制台字体信息
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);

    // 获取控制台当前字体信息
    GetCurrentConsoleFontEx(hCon, false, &cfi);

    res.yy = pt.x / (cfi.dwFontSize.X * 2) + 1;
    res.xx = pt.y / (cfi.dwFontSize.Y) + 1;
    return res;
}