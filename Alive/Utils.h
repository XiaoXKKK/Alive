#pragma once
#ifndef _Utils_H
#define _Utils_H
#include"game.h"
#include<string>

using std::string;

struct PIC {
	string pic[2];
	string name;
};

void print_PIC(int x, int y,const PIC& pic);
const int SCR_WIDTH = 50, SCR_HEIGHT = 35;



#endif // !_Utils_H

