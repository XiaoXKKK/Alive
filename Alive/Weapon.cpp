#include"Weapon.h"
Weapon::Weapon(std::string name,int harm,int weight,int standby,int clipspace,int shoot_speed)
    :name(name),harm(harm),weight(weight),standby(standby),clipspace(clipspace),shoot_speed(shoot_speed)
{
    nowclip=clipspace;
}

Upgrade::Upgrade(string name, string hint, int nd_exp, int nd_money)
    :name(name), hint(hint), nd_exp(nd_exp), nd_money(nd_money)
{
    f = 0;
}

Upgrade::Upgrade() {}