#include"UI.h"
#include<iostream>
#include<cstdio>

using std::cout;
using std::string;

void UI::print_Button(int x,int y,std::string s){
    Locate(x, y);
    const char* top=" ______________";
    cout<<top;
    string btm="|______________|";
    auto pos = btm.begin() + 1 + (14 - s.size() + 1) / 2;
    btm = btm.replace(pos, pos + s.size(), s.c_str());
    Locate(x+1,y);
    cout<<btm;
}
void UI::print_Frame(){
    system("cls");
    Locate(1, 1);
    Setcolor(GRAY);
    const char* empty_line="[]                                              []";
    const char* frame_line="[][][][][][][][][][][][][][][][][][][][][][][][][]";
    printf(frame_line);
    for(int i=0;i<SCR_HEIGHT-2;i++){
        printf(empty_line);
    }
    printf(frame_line);
}

void UI::print_Upgrade(Weapon w) {
    print_Frame();
    W(3, 3, "Upgrade Factory");
    W(3, 20, w.name);
    print_PIC(5, 3, w.pic);
    W(5, 15, "money:");
    W(6, 15, "EXP:");
    const int BEGIN = 12;
    for (int i = 0; i < UPG_TYPE; i++) {
        const int NOW = BEGIN + i * 4;
        Locate(NOW, 2);
        cout << i + 1 << ' ';
        cout << w.upg[i].name;
        print_Button(NOW - 1, 15, "Upgrade");
        Locate(NOW + 1, 3);
        cout << w.upg[i].hint;
        Locate(NOW + 1, 15);
        cout << "EXP:" << w.upg[i].nd_exp;
        Locate(NOW + 1, 20);
        cout << '$' << w.upg[i].nd_money;
    }
    print_Button(31, 15, "EXIT");
}