#pragma once
#ifndef _UI_H
#define _UI_H

#include<string>
#include"Utils.h"
#include"Weapon.h"
#include"game.h"
class UI
{
private:
    /* data */
public:
    void print_Button(int x, int y, std::string s);
    void print_Frame();
    void print_Upgrade(Weapon w);
};



#endif // !_UI_H

