#pragma once
#include"Utils.h"
#include<string>

using std::string;

const int UPG_TYPE = 5;

class Upgrade{
public:
    bool f;
	string name;
	string hint;
	int nd_exp;
	int nd_money;
	Upgrade(string name, string hint, int nd_exp, int nd_money);
	Upgrade();
};

class Weapon
{
private:
	int harm;
	int weight;
  	int standby;
	int nowclip;
	int clipspace;
	bool reseting;
	int st;
//  int clipspeed;
	int shoot_speed;
public:
	std::string name;
	Upgrade upg[UPG_TYPE];
	PIC pic;
    Weapon(std::string name,int harm,int weight,int standby,int clipspace,int shoot_speed);
};

