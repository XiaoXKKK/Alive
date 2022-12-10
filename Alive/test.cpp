#include"UI.h"
#include<iostream>
#include<windows.h>
using namespace std;

void init_window() {
	// srand(time(NULL));
	Winset(150,500);
	//SetConsoleTitle("Alive");
	system("mode con cols=50 lines=37");
	system("chcp 936");
	system("cls");
	//以下是关掉快速编辑模式
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hIn, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	mode &= ~ENABLE_INSERT_MODE;
	SetConsoleMode(hIn, mode);
	CloseHandle(&hIn);
	return;
}

Weapon MG3("MG3", 25, 200, 2, 120, 200);

int main()
{
    init_window();
    UI ui;
	if (0) {
		ui.print_Frame();
		ui.print_Button(10, 15, "EXIT");
		getchar();
	}
	if (1) {
		MG3.pic.pic[0] = "[/=#######=";
		MG3.pic.pic[1] = "   \"\"\" / \\ ";
		MG3.upg[0] = Upgrade("枪身结构简化", "减轻重量 提升移速", 250, 2500);
		MG3.upg[1] = Upgrade("M993穿甲弹", "大幅提升伤害", 250, 2000);
		MG3.upg[2] = Upgrade("扩容弹链箱", "增加弹夹容量和总弹药", 150, 1500);
		MG3.upg[3] = Upgrade("两脚架", "提升稳定性 提升射速", 120, 1200);
		MG3.upg[4] = Upgrade("红点瞄准具", "提升精准度 提升伤害", 100, 1000);
		ui.print_Upgrade(MG3);
		getchar();
	}

}