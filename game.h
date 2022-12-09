/*
    This scope give out some usual fuctions about tiny games.
    You can free use:
        Locate(x,y);
        Setcolor(COLOR);
        SetConsoleTitle("title");
        system("mode con cols=50 lines=50");

        if(KEY_DOWN(MOUSE_MOVED))printf("��");
        printf("����Ҽ��Ƿ��£�");
        if(KEY_DOWN(MOUSE_EVENT))printf("��");
        printf("�����ּ��Ƿ��£�");
        if(KEY_DOWN(MOUSE_WHEELED))printf("��");
*/
//#pragma once

//#include "afxribbonstatusbar.h"
//
//class MyCMFCRibbonStatusBar :public CMFCRibbonStatusBar
//{
//public:
//MyCMFCRibbonStatusBar(void);
//~MyCMFCRibbonStatusBar(void);
//void OnPaneContextMenu(CWnd* pParentFrame, CPoint point);
//};

#include<windows.h>
#include<conio.h>
#include<string>
#include<iostream>

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

#define IsKeyPressed(nVirtKey) ((GetKeyState(nVirtKey) & (1<<(sizeof(SHORT)*8-1))) != 0)

HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

HANDLE hCon;
enum Color {
    DARKBLUE = 1,
    DARKGREEN,
    DARKTEAL,
    DARKRED,
    DARKPINK,
    DARKYELLOW,
    GRAY,
    DARKGRAY,
    BLUE,
    GREEN,
    TEAL,
    RED,
    PINK,
    YELLOW,
    WHITE
};

void Setcolor(Color c) {
    if(hCon == NULL)
        hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, c);
}

void Locate(int x,int y) {
    y = y * 2 - 1;
    coord.X=y - 1;
    coord.Y=x - 1;
    SetConsoleCursorPosition(hout,coord);
}
void W(int x,int y,std::string s) {
	Locate(x,y);
	std::cout<<s;
}
int winx,winy;
void Winset(int x,int y) {
    winx = y;
    winy = x;
    RECT rect;
    HWND hwnd=GetForegroundWindow();
    GetWindowRect(hwnd,&rect);
    int title_high = GetSystemMetrics(SM_CYCAPTION);   //���ڱ������߶�
    int line_wight = GetSystemMetrics(SM_CYSIZEFRAME)
                     + GetSystemMetrics(SM_CYBORDER);   //���ڱ߿����
    MoveWindow(hwnd,y-line_wight,x-title_high-line_wight,rect.right-rect.left,rect.bottom-rect.top,TRUE);
}
struct Mos {
    int xx,yy;
};
Mos Getmouse() {
    POINT pt;
    GetCursorPos(&pt);
    HWND hwnd=GetForegroundWindow();
    ScreenToClient(hwnd,&pt);
    Mos res;

    // ���� CONSOLE_FONT_INFOEX �ṹ�壬���ڱ������̨������Ϣ
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);

    // ��ȡ����̨��ǰ������Ϣ
    GetCurrentConsoleFontEx(hCon, false, &cfi);

    res.yy = pt.x/(cfi.dwFontSize.X*2)+1;
    res.xx = pt.y/(cfi.dwFontSize.Y)+1;
    return res;
}
/*
    POINT pt;
    GetCursorPos(&pt);
    cout << "��ǰ���������Ϊ��" << pt.x << "," << pt.y << endl;
    system("cls");

       =   4
SM_CXBORDER   =   5
SM_CYBORDER   =   6

GetSystemMetrics(6)   //���ڱ߿����
*/

/*
    // ��ȡ�����
    HWND h=GetForegroundWindow();
    printf("0x%X\n",h);
    // ��ȡ���ڱ���
    char text[200];
    GetWindowText(h,text,200);
    printf("%s\n",text);
    // ��ȡ��Ļ�������
    POINT pt;
    GetCursorPos(&pt);
    printf("%d %d\n",pt.x,pt.y);
    // ��ȡ�����������
    ScreenToClient(h,&pt);
    printf("%d %d\n",pt.x,pt.y);
*/


/*
��������Ӧ��

VK_LBUTTON
1
������
VK_RBUTTON
2
����Ҽ�
VK_CANCEL
3
Cancel
VK_MBUTTON
4
����м�
VK_XBUTTON1
5

VK_XBUTTON2
6

VK_BACK
8
Backspace
VK_TAB
9
Tab
VK_CLEAR
12
Clear
VK_RETURN
13
Enter
VK_SHIFT
16
Shift
VK_CONTROL
17
Ctrl
VK_MENU
18
Alt
VK_PAUSE
19
Pause
VK_CAPITAL
20
Caps Lock
VK_KANA
21

VK_HANGUL
21

VK_JUNJA
23

VK_FINAL
24

VK_HANJA
25

VK_KANJI
25*

VK_ESCAPE
27
Esc
VK_CONVERT
28

VK_NONCONVERT
29

VK_ACCEPT
30

VK_MODECHANGE
31

VK_SPACE
32
Space
VK_PRIOR
33
Page Up
VK_NEXT
34
Page Down
VK_END
35
End
VK_HOME
36
Home
VK_LEFT
37
Left Arrow
VK_UP
38
Up Arrow
VK_RIGHT
39
Right Arrow
VK_DOWN
40
Down Arrow
VK_SELECT
41
Select
VK_PRINT
42
Print
VK_EXECUTE
43
Execute
VK_SNAPSHOT
44
Snapshot
VK_INSERT
45
Insert
VK_DELETE
46
Delete
VK_HELP
47
Help

48
0

49
1

50
2

51
3

52
4

53
5

54
6

55
7

56
8

57
9

65
A

66
B

67
C

68
D

69
E

70
F

71
G

72
H

73
I

74
J

75
K

76
L

77
M

78
N

79
O

80
P

81
Q

82
R

83
S

84
T

85
U

86
V

87
W

88
X

89
Y

90
Z
VK_LWIN
91

VK_RWIN
92

VK_APPS
93

VK_SLEEP
95

VK_NUMPAD0
96
С���� 0
VK_NUMPAD1
97
С���� 1
VK_NUMPAD2
98
С���� 2
VK_NUMPAD3
99
С���� 3
VK_NUMPAD4
100
С���� 4
VK_NUMPAD5
101
С���� 5
VK_NUMPAD6
102
С���� 6
VK_NUMPAD7
103
С���� 7
VK_NUMPAD8
104
С���� 8
VK_NUMPAD9
105
С���� 9
VK_MULTIPLY
106
С���� *
VK_ADD
107
С���� +
VK_SEPARATOR
108
С���� Enter
VK_SUBTRACT
109
С���� -
VK_DECIMAL
110
С���� .
VK_DIVIDE
111
С���� /
VK_F1
112
F1
VK_F2
113
F2
VK_F3
114
F3
VK_F4
115
F4
VK_F5
116
F5
VK_F6
117
F6
VK_F7
118
F7
VK_F8
119
F8
VK_F9
120
F9
VK_F10
121
F10
VK_F11
122
F11
VK_F12
123
F12
VK_F13
124

VK_F14
125

VK_F15
126

VK_F16
127

VK_F17
128

VK_F18
129

VK_F19
130

VK_F20
131

VK_F21
132

VK_F22
133

VK_F23
134

VK_F24
135

VK_NUMLOCK
144
Num Lock
VK_SCROLL
145
Scroll
VK_LSHIFT
160

VK_RSHIFT
161

VK_LCONTROL
162

VK_RCONTROL
163

VK_LMENU
164

VK_RMENU
165

VK_BROWSER_BACK
166

VK_BROWSER_FORWARD
167

VK_BROWSER_REFRESH
168

VK_BROWSER_STOP
169

VK_BROWSER_SEARCH
170

VK_BROWSER_FAVORITES
171

VK_BROWSER_HOME
172

VK_VOLUME_MUTE
173
VolumeMute
VK_VOLUME_DOWN
174
VolumeDown
VK_VOLUME_UP
175
VolumeUp
VK_MEDIA_NEXT_TRACK
176

VK_MEDIA_PREV_TRACK
177

VK_MEDIA_STOP
178

VK_MEDIA_PLAY_PAUSE
179

VK_LAUNCH_MAIL
180

VK_LAUNCH_MEDIA_SELECT
181

VK_LAUNCH_APP1
182

VK_LAUNCH_APP2
183

VK_OEM_1
186
; :
VK_OEM_PLUS
187
= +
VK_OEM_COMMA
188

VK_OEM_MINUS
189
- _
VK_OEM_PERIOD
190

VK_OEM_2
191
/ ?
VK_OEM_3
192
` ~
VK_OEM_4
219
[ {
VK_OEM_5
220
\ |
VK_OEM_6
221
] }
VK_OEM_7
222
' "
VK_OEM_8
223

VK_OEM_102
226

VK_PACKET
231

VK_PROCESSKEY
229

VK_ATTN
246

VK_CRSEL
247

VK_EXSEL
248

VK_EREOF
249

VK_PLAY
250

VK_ZOOM
251

VK_NONAME
252

VK_PA1
253

VK_OEM_CLEAR
254
*/