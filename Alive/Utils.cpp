#include<iostream>
#include"Utils.h"

using std::cout;

void print_PIC(int x, int y, const PIC& pic)
{
	Locate(x, y);
	cout << pic.pic[0];
	Locate(x + 1, y);
	cout << pic.pic[1];
}