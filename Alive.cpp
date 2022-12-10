//#pragma GCC optimize (3)
#include<iostream>
#include<cstdio>
#include<queue>
#include<ctime>
#include<string>
#include<fstream>
#include<cstring>
#include"game.h"
#define INF 1061109567

using namespace std;

const int SIZ = 25;
SYSTEMTIME sys;
string cat;

const int dx[4]= {1,0,0,-1},dy[4]= {0,1,-1,0};
struct UPGRADE {
	int lev[10];
};
struct Weapon {
	string name;
	int harm;
	int weight;
  	int standby;
	int nowclip;
	int clipspace;
	bool reseting;
	int st;
//  int clipspeed;
	int shoot_speed;
	UPGRADE upg;
	friend bool operator == (Weapon x,Weapon y) {
		return x.name == y.name;
	}
	friend bool operator != (Weapon x,Weapon y) {
		return x.name != y.name ;
	}
};
struct Armor {
	int type;
	int defense;
	int lev;
	int attack;
	string name;
	friend bool operator != (Armor x,Armor y) {
		return x.name != y.name ;
	}
};
struct Wear {
	Armor _head,_body,_bottom;
	Weapon _hand,_hand2;
};
struct Skill {
	int att,def,fat;
};
struct Player {
	bool blood_angry_end,inm_end;
	bool mp5,hpwave;
	int ar,br,cr,dr;//Proficiency
	long exp,money;
	int max_hp,hp;
	int fc;
	int x,y;
	int add_hp;
	Wear _wear;
	Skill _skill;
	string name;
	string race;
	int last_add,last_app,last_shoot;
	int last_blood,last_DNA,last_boom,last_flash;
	bool blood_angry,inm,servent;
	int servend_hp,sx,sy;
};
struct Zombie {
	int hp,att;
	int xp;
	bool die;
	int speed;
	int x,y;
	string name;
	int level;
};
struct cilp {
	int harm;
//  int speed;
	int fc;
	int contant;
	int start;
	bool flag;
	int x,y;
	string from;
} clip[10005];
struct PIC {
	string pic[2];
	string name;
} bmp[15];
struct ZombieCreate {
	int x,y;
} Pos[55];
//struct crenade {
//	int x,y;
//	int tim;
//	bool ban;
//} cre[100];
struct Boom {
	int x,y;
	int tim;
	int id;
	int dir;
} bom[600];

int bom_num;

Player p;
Zombie z[20];
Zombie a[500];
string Map[50][50];
Weapon Glock18,S686,MG3,M4A1,AWP,AA12,MP5,FireGun,Knife,WTF;
Armor armour,helmet[3],spike,noe;

int now_wave;
int cnt,pos_num,num_cre;
int flag[50][50];
bool jud_harm(int x,int y,int i) {
	if(!clip[i].contant) {
		clip[i].flag=1;
		return false;
	}
	if(Map[x][y]=="zombie") {
		clip[i].contant--;
//			Locate(10,10);cout<<clip[i].contant;
//			Sleep(5000);
		flag[x][y]=clip[i].harm+int(p._skill.att*0.1);
		return false;
	}
	return true;
}
bool jud_gift(int x,int y) {
	if(x==p.x && y==p.y) return false;
	if(Map[x][y]=="") return true;
	return false;
}
bool jud_gun(int x,int y) {
	if(Map[x][y]=="" || Map[x][y]=="boom" || Map[x][y]=="zombie") return true;
	else return false;
}
bool jud_world(int x,int y) {
	if(Map[x][y]=="" || Map[x][y]=="boom") return true;
	else return false;
}

void init_standby() {
	Knife.standby=INF;
	Glock18.standby = Glock18.clipspace * 10;
	S686.standby = S686.clipspace * 10;
	M4A1.standby = M4A1.clipspace * 4;
	MG3.standby = MG3.clipspace * 2;
	AWP.standby = 15;
	AA12.standby = AA12.clipspace * 4;
	MP5.standby = MP5.clipspace * 8;
	FireGun.standby = FireGun.clipspace * 5;
}
void init_upgrade() {
	if(M4A1.upg.lev[2]) M4A1.harm += 10;
	if(M4A1.upg.lev[1]) M4A1.weight -= 20;
	if(M4A1.upg.lev[3]) M4A1.clipspace=(M4A1.nowclip+=10);
	if(M4A1.upg.lev[4]) M4A1.harm += 3,M4A1.shoot_speed-=50;
	if(M4A1.upg.lev[5]) M4A1.harm += 7;
	if(AA12.upg.lev[1]) AA12.weight -= 30;
	if(AA12.upg.lev[2]) AA12.harm += 20;
	if(AA12.upg.lev[3]) AA12.clipspace=AA12.nowclip = 22;
	if(AA12.upg.lev[4]) AA12.shoot_speed -= 70;
	if(AA12.upg.lev[5]) AA12.harm += 10,AA12.shoot_speed -= 30;
	if(MG3.upg.lev[1]) MG3.weight -= 50;
	if(MG3.upg.lev[2]) MG3.harm += 5;
	if(MG3.upg.lev[3]) MG3.clipspace=(MG3.nowclip+=50);
	if(MG3.upg.lev[4]) MG3.shoot_speed -= 50;
	if(MG3.upg.lev[5]) MG3.harm += 5;
	if(S686.upg.lev[1]) S686.weight -= 15;
	if(S686.upg.lev[2]) S686.harm += 25;
	if(S686.upg.lev[3]) S686.clipspace = S686.nowclip = 4;
	if(S686.upg.lev[5]) S686.harm += 15;
	if(Glock18.upg.lev[1]) Glock18.harm+=5;
	if(Glock18.upg.lev[2]) Glock18.harm+=5;
	if(Glock18.upg.lev[3]) Glock18.nowclip=Glock18.clipspace=16;
	if(Glock18.upg.lev[4]) Glock18.shoot_speed = 450;
	if(Glock18.upg.lev[5]) Glock18.harm+=10,Glock18.weight += 30;
	if(AWP.upg.lev[1]) AWP.weight = 100;
	if(AWP.upg.lev[2]) AWP.harm += 300;
	if(AWP.upg.lev[4]) AWP.nowclip=AWP.clipspace=3;
	if(AWP.upg.lev[5]) AWP.harm += 500;
	if(MP5.upg.lev[1]) MP5.harm+=5;
	if(MP5.upg.lev[2]) MP5.harm+=5;
	if(MP5.upg.lev[3]) MP5.nowclip = MP5.clipspace = 35;
	if(MP5.upg.lev[4]) MP5.shoot_speed = 50;
	if(MP5.upg.lev[5]) MP5.weight = 5;
	if(FireGun.upg.lev[1]) FireGun.harm += 5;
	if(FireGun.upg.lev[2]) FireGun.clipspace = FireGun.nowclip = 500;
	if(FireGun.upg.lev[3]) FireGun.harm += 5;
	if(FireGun.upg.lev[4]) FireGun.shoot_speed = 35;
	if(FireGun.upg.lev[5]) FireGun.weight = 50;
	init_standby();
	return;
}
void init_weapon() {
	Knife.name="Knife";
	Knife.harm=50;
	Knife.weight = 5;
	Knife.shoot_speed=1000;
	Knife.clipspace=Knife.nowclip=Knife.standby=INF;
	Glock18.name="Glock18";
	Glock18.weight = 10;
	Glock18.harm=15;
	Glock18.clipspace=Glock18.nowclip=8;
	Glock18.shoot_speed = 700;
	S686.name="S686";
	S686.harm=70;
	S686.weight = 40;
	S686.clipspace=S686.nowclip=2;
	S686.shoot_speed = 100;
	M4A1.name="M4A1";
	M4A1.harm=25;
	M4A1.clipspace=M4A1.nowclip=30;
	M4A1.shoot_speed = 200;
	M4A1.weight = 50;
	MG3.name="MG3";
	MG3.clipspace=MG3.nowclip=120;
	MG3.harm=25;
	MG3.shoot_speed = 200;
	MG3.weight = 200;
	AWP.name="AWP";
	AWP.harm=800;
	AWP.weight = 150;
	AWP.clipspace=AWP.nowclip=1;
	AWP.shoot_speed = 2000;
	WTF.name="none";
	AA12.name="AA12";
	AA12.weight = 60;
	AA12.harm=50;
	AA12.clipspace=AA12.nowclip=12;
	AA12.shoot_speed = 300;
	MP5.name="MP5";
	MP5.harm=10;
	MP5.weight = 25;
	MP5.clipspace=MP5.nowclip=25;
	MP5.shoot_speed = 70;
	FireGun.name="FireGun";
	FireGun.harm=10;
	FireGun.weight = 70;
	FireGun.clipspace=FireGun.nowclip=300;
	FireGun.shoot_speed = 50;
	init_upgrade();
}
void Clean_clip(int x,int y) {
	if(Map[x][y] == "boom") return;
	Locate(x,y);
	cout<<"  ";
//    Locate(1,1);
}
void Print_clip(int x,int y,int i) {
	if(clip[i].flag) {
		return;
	}
//  if(Map[x][y] == "boom") return;
	if(Map[x][y] == "boom" || (p.x == x && p.y == y)) return;
	Locate(x,y);
	Setcolor(YELLOW);
	if(p.blood_angry) Setcolor(RED);
	if(clip[i].from == "Glock18") {
		if(Glock18.upg.lev[5]) cout << ": ";
		else cout<<"·";
	} else if(clip[i].from == "M4A1" || clip[i].from == "MP5") cout<<"''";
	else if(clip[i].from == "MG3") cout<<"::";
	else if(clip[i].from == "AWP") {
		Setcolor(GREEN);
		cout<<"+ ";
	} else if(clip[i].from == "S686" || clip[i].from == "AA12" ) cout<<"##";
	else if(clip[i].from == "FireGun") {
		if(rand()%6>=3) Setcolor(RED);
		else Setcolor(YELLOW);
		cout<<"<>";
	} else if(clip[i].from == "Knife") {
		cout<<" /";
	}
//    Locate(1,1);
	Setcolor(GRAY);
}
bool shoot(int x,int y,int fc,Weapon gun) {
	bool kkk=jud_gun(x,y);
	if(!kkk) return false;
	cnt++;
	GetLocalTime( &sys );
	clip[cnt].start = sys.wMilliseconds + sys.wSecond * 60 + sys.wHour * 3600;
	clip[cnt].x = x;
	clip[cnt].y = y;
	clip[cnt].harm=gun.harm;
	if(gun.name=="AWP") clip[cnt].contant=9999;
	else if(gun.name == "FireGun") clip[cnt].contant=3;
	else clip[cnt].contant=1;
//	Locate(10,10);cout<<clip[cnt].contant;
	clip[cnt].fc=fc;//p.fc
	clip[cnt].from = gun.name;
	if(!jud_harm(x,y,cnt)) {
		if(!clip[cnt].contant) clip[cnt].flag=1;
		if(clip[cnt].flag) return kkk;
	}
//    Print_clip(x,y,cnt);
	return kkk;
}
void Create_clip() {
	Weapon gun=p._wear._hand;
	GetLocalTime( &sys );
	int tmd = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
	if(tmd - p.last_shoot < gun.shoot_speed) return;
	p.last_shoot = tmd;
	if(gun.name=="none" || !gun.nowclip || gun.reseting) return;
	if(gun.name!="Knife") gun.nowclip--;
	int fc=p.fc;
	int x=p.x;
	int y=p.y;
	bool shooted=shoot(x,y,fc,gun);
	if(((gun.name=="Glock18" && Glock18.upg.lev[5]) || gun.name=="S686" || gun.name == "AA12" || gun.name=="Knife") && shooted) {
		if(fc == 1 || fc == 2) shoot(x+1,y,fc,gun),shoot(x-1,y,fc,gun);
		else shoot(x,y+1,fc,gun),shoot(x,y-1,fc,gun);
	}
	p._wear._hand=gun;
}
void clipmove() {
	GetLocalTime( &sys );
	int tim = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
	for(int i = 1; i <= cnt; i++) {
		if(clip[i].flag) continue;
		if(tim-clip[i].start > 20) {
			clip[i].start = tim;
			int fc= clip[i].fc;
			int x = clip[i].x,xx=x+dx[fc];
			int y = clip[i].y,yy=y+dy[fc];
			if(p.x!=x || p.y!=y)Clean_clip(x,y);
			jud_harm(xx,yy,i);
			if(!clip[i].contant) clip[i].flag=1;
			if(clip[i].flag) continue;
			if(!jud_gun(xx,yy)) {
				clip[i].flag=1;
				continue;
			}
			clip[i].x=xx,clip[i].y=yy;
			Print_clip(xx,yy,i);
			if(clip[i].from=="Knife") clip[i].contant=0;
		}
	}
}
void reload() {
	Weapon tmp=p._wear._hand;
	if(tmp.name=="none" || tmp.reseting) return;
//	if(!tmp.standby && (now_wave != 11 && now_wave != 21)) return;
	GetLocalTime( &sys );
	int t = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
	tmp.reseting=1;
	tmp.st=t;
	p._wear._hand=tmp;
}
void end_reload() {
	Weapon tmp=p._wear._hand;
	if(now_wave == 11 || now_wave == 21) {
		tmp.nowclip = tmp.clipspace;
		tmp.reseting=0;
		p._wear._hand=tmp;
//		printf("HHHHHHHH");
		return;
	}
	tmp.standby += tmp.nowclip;
	int ad = min(tmp.standby,tmp.clipspace);
	tmp.nowclip = ad;
	tmp.standby -= ad;
	tmp.reseting=0;
	p._wear._hand=tmp;
}

void print_house_stone(int x,int y) {
	Locate(x,y);
	Setcolor(GRAY);
	printf("■");
}
void print_grass(int x,int y) {
	Locate(x,y);
	Setcolor(DARKGREEN);
	printf("□");
	Setcolor(GRAY);
}


void sayno() {
	Locate(32,3),printf("You can't afford it!");
	Sleep(1000);
	Locate(32,3),printf("                    ");
}
void sayhave() {
	Locate(32,3),printf("You already have it.");
	Sleep(1000);
	Locate(32,3),printf("                    ");
}
void sayyes() {
	Locate(32,3),printf("You got it!");
	Locate(5,18);
	printf("       ");
	cout<<p.money<<"  ";
	Locate(6,18);
	printf("       ");
	cout<<p.exp<<"  ";
	init_weapon();
	Sleep(1000);
	Locate(32,3),printf("                    ");
}


int last_M4A1;
void upgrade_M4A1() {
	system("cls");
	Locate(1,1);
	Setcolor(GRAY);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Upgrade Factory                    M4A1    []");
	printf("[]                                              []");
	printf("[]    __==____+_          money:                []");
	printf("[]   [/ |/ \\\\             EXP:                  []");
	printf("[]                                              []");
	printf("[]   *升级M4A1将同时提升炮塔伤害                []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 1 轻合金枪托           |____Upgrade___|      []");//12
	printf("[]   减轻重量 提升移速     EXP:70   $700        []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 2 M203榴弹发射器       |____Upgrade___|      []");
	printf("[]   发射榴弹 大幅提高伤害 EXP:250  $2000       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 3 扩容弹夹             |____Upgrade___|      []");
	printf("[]   增加弹夹容量和总弹药  EXP:120  $1200       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 4 更好的气动配件       |____Upgrade___|      []");
	printf("[]   增加射速 提升伤害     EXP:120  $1200       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 5 ACOG瞄准镜           |____Upgrade___|      []");
	printf("[]   易击中要害 提升伤害   EXP:100  $1000       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]                        |_____Exit_____|      []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	Locate(5,18);
	cout<<p.money;
	Locate(6,18);
	cout<<p.exp;
	int mx,my;
	while(1) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_M4A1 >= 50) {
			last_M4A1 = T;
			if(!KEY_DOWN(MOUSE_MOVED)) continue;
			my = Getmouse().xx;
			mx = Getmouse().yy;
			if(15 <= mx && mx <= 21) {
				if(my == 12) {
					if(p.money < 700 || p.exp < 70) sayno();
					else if(M4A1.upg.lev[1]) sayhave();
					else {
						p.money-=700;
						p.exp-=70;
						M4A1.upg.lev[1] = 1;
						sayyes();
					}
				} else if(my == 16) {
					if(p.money < 2000 || p.exp < 250) sayno();
					else if(M4A1.upg.lev[2]) sayhave();
					else {
						p.money-=2000;
						p.exp-=250;
						M4A1.upg.lev[2] = 1;
						sayyes();
					}
				} else if(my == 20) {
					if(p.money < 1200 || p.exp < 120) sayno();
					else if(M4A1.upg.lev[3]) sayhave();
					else {
						p.money-=1200;
						p.exp-=120;
						M4A1.upg.lev[3] = 1;
						sayyes();
					}
				} else if(my == 24) {
					if(p.money < 1200 || p.exp < 120) sayno();
					else if(M4A1.upg.lev[4]) sayhave();
					else {
						p.money-=1200;
						p.exp-=120;
						M4A1.upg.lev[4] = 1;
						sayyes();
					}
				} else if(my == 28) {
					if(p.money < 1000 || p.exp < 100) sayno();
					else if(M4A1.upg.lev[5]) sayhave();
					else {
						p.money-=1000;
						p.exp-=100;
						M4A1.upg.lev[5] = 1;
						sayyes();
					}
				} else if(my == 32) return;
			}
		}
	}
}
int last_AA12;
void upgrade_AA12() {
	system("cls");
	Locate(1,1);
	Setcolor(GRAY);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Upgrade Factory                    AA12    []");
	printf("[]                                              []");
	printf("[]    _,,,,,,,,           money:                []");
	printf("[]   [/~[]~|              EXP:                  []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 1 轻质玻璃纤维塑料     |____Upgrade___|      []");//12
	printf("[]   减轻重量 提升移速     EXP:70   $700        []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 2 HEFA破片弹           |____Upgrade___|      []");
	printf("[]   大幅提升伤害          EXP:250  $2000       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 3 22发弹鼓             |____Upgrade___|      []");
	printf("[]   增加弹夹容量和总弹药  EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 4 更好的气动配件       |____Upgrade___|      []");
	printf("[]   增加射速              EXP:120  $1200       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 5 钢箍前握把           |____Upgrade___|      []");
	printf("[]   减小后坐力 提升伤害   EXP:100  $1000       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]                        |_____Exit_____|      []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	Locate(5,18);
	cout<<p.money;
	Locate(6,18);
	cout<<p.exp;
	int mx,my;
	while(1) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_AA12 >= 50) {
			last_AA12 = T;
			if(!KEY_DOWN(MOUSE_MOVED)) continue;
			my = Getmouse().xx;
			mx = Getmouse().yy;
			if(15 <= mx && mx <= 21) {
				if(my == 12) {
					if(p.money < 700 || p.exp < 70) sayno();
					else if(AA12.upg.lev[1]) sayhave();
					else {
						p.money-=700;
						p.exp-=70;
						AA12.upg.lev[1] = 1;
						sayyes();
					}
				} else if(my == 16) {
					if(p.money < 2000 || p.exp < 250) sayno();
					else if(AA12.upg.lev[2]) sayhave();
					else {
						p.money-=2000;
						p.exp-=250;
						AA12.upg.lev[2] = 1;
						sayyes();
					}
				} else if(my == 20) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(AA12.upg.lev[3]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						AA12.upg.lev[3] = 1;
						sayyes();
					}
				} else if(my == 24) {
					if(p.money < 1200 || p.exp < 120) sayno();
					else if(AA12.upg.lev[4]) sayhave();
					else {
						p.money-=1200;
						p.exp-=120;
						AA12.upg.lev[4] = 1;
						sayyes();
					}
				} else if(my == 28) {
					if(p.money < 1200 || p.exp < 120) sayno();
					else if(AA12.upg.lev[5]) sayhave();
					else {
						p.money-=1200;
						p.exp-=120;
						AA12.upg.lev[5] = 1;
						sayyes();
					}
				} else if(my == 32) return;
			}
		}
	}
}

int last_MG3;
void upgrade_MG3() {
	system("cls");
	Locate(1,1);
	Setcolor(GRAY);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Upgrade Factory                    MG3     []");
	printf("[]                                              []");
	printf("[]   [/=#######=          money:                []");
	printf("[]      \"\"\"  /\\           EXP:                  []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 1 枪身结构简化         |____Upgrade___|      []");//12
	printf("[]   减轻重量 提升移速     EXP:250  $2500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 2 M993穿甲弹           |____Upgrade___|      []");
	printf("[]   大幅提升伤害          EXP:250  $2000       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 3 扩容弹链箱           |____Upgrade___|      []");
	printf("[]   增加弹夹容量和总弹药  EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 4 两脚架               |____Upgrade___|      []");
	printf("[]   提升稳定性 提升射速   EXP:120  $1200       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 5 红点瞄准具           |____Upgrade___|      []");
	printf("[]   提升精准度 提升伤害   EXP:100  $1000       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]                        |_____Exit_____|      []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	Locate(5,18);
	cout<<p.money;
	Locate(6,18);
	cout<<p.exp;
	int mx,my;
	while(1) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_MG3 >= 50) {
			last_MG3 = T;
			if(!KEY_DOWN(MOUSE_MOVED)) continue;
			my = Getmouse().xx;
			mx = Getmouse().yy;
			if(15 <= mx && mx <= 21) {
				if(my == 12) {
					if(p.money < 2500 || p.exp < 250) sayno();
					else if(MG3.upg.lev[1]) sayhave();
					else {
						p.money-=2500;
						p.exp-=250;
						MG3.upg.lev[1] = 1;
						sayyes();
					}
				} else if(my == 16) {
					if(p.money < 2000 || p.exp < 250) sayno();
					else if(MG3.upg.lev[2]) sayhave();
					else {
						p.money-=2000;
						p.exp-=250;
						MG3.upg.lev[2] = 1;
						sayyes();
					}
				} else if(my == 20) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(MG3.upg.lev[3]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						MG3.upg.lev[3] = 1;
						sayyes();
					}
				} else if(my == 24) {
					if(p.money < 1200 || p.exp < 120) sayno();
					else if(MG3.upg.lev[4]) sayhave();
					else {
						p.money-=1200;
						p.exp-=120;
						MG3.upg.lev[4] = 1;
						sayyes();
					}
				} else if(my == 28) {
					if(p.money < 1200 || p.exp < 120) sayno();
					else if(MG3.upg.lev[4]) sayhave();
					else {
						p.money-=1200;
						p.exp-= 120;
						MG3.upg.lev[5] = 1;
						sayyes();
					}
				} else if(my == 32) return;
			}
		}
	}
}
int last_S686;
void upgrade_S686() {
	system("cls");
	Locate(1,1);
	Setcolor(GRAY);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Upgrade Factory                    S686    []");
	printf("[]                                              []");
	printf("[]    ______..__          money:                []");
	printf("[]   //~````^^^           EXP:                  []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 1 折式枪身             |____Upgrade___|      []");//12
	printf("[]   提升灵活性和移速      EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 2 金属砂弹             |____Upgrade___|      []");
	printf("[]   大幅提升伤害          EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 3 双弹头设计           |____Upgrade___|      []");
	printf("[]   增加弹夹容量和总弹药  EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 4 自动退壳装置         |____Upgrade___|      []");
	printf("[]   提升换弹速度          EXP:250  $2500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 5 橡胶强化枪托         |____Upgrade___|      []");
	printf("[]   降低后坐力 提升伤害   EXP:100  $1000       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]                        |_____Exit_____|      []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	Locate(5,18);
	cout<<p.money;
	Locate(6,18);
	cout<<p.exp;
	int mx,my;
	while(1) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_S686 >= 50) {
			last_S686 = T;
			if(!KEY_DOWN(MOUSE_MOVED)) continue;
			my = Getmouse().xx;
			mx = Getmouse().yy;
			if(15 <= mx && mx <= 21) {
				if(my == 12) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(S686.upg.lev[1]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						S686.upg.lev[1] = 1;
						sayyes();
					}
				} else if(my == 16) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(S686.upg.lev[2]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						S686.upg.lev[2] = 1;
						sayyes();
					}
				} else if(my == 20) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(S686.upg.lev[3]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						S686.upg.lev[3] = 1;
						sayyes();
					}
				} else if(my == 24) {
					if(p.money < 2500 || p.exp < 250) sayno();
					else if(S686.upg.lev[4]) sayhave();
					else {
						p.money-=2500;
						p.exp-=250;
						S686.upg.lev[4] = 1;
						sayyes();
					}
				} else if(my == 28) {
					if(p.money < 1000 || p.exp < 100) sayno();
					else if(S686.upg.lev[5]) sayhave();
					else {
						p.money-=1000;
						p.exp-= 100;
						S686.upg.lev[5] = 1;
						sayyes();
					}
				} else if(my == 32) return;
			}
		}
	}
}

int last_Glock18;
void upgrade_Glock18() {
	system("cls");
	Locate(1,1);
	Setcolor(GRAY);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Upgrade Factory                 Glock18    []");
	printf("[]                                              []");
	printf("[]      ,___              money:                []");
	printf("[]      #\"\"               EXP:                  []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 1 枪口补偿装置         |____Upgrade___|      []");//12
	printf("[]   提升精准度 提升伤害   EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 2 握把手指凹槽         |____Upgrade___|      []");
	printf("[]   提升稳定性 提升伤害   EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 3 双排弹夹             |____Upgrade___|      []");
	printf("[]   增加弹夹容量和总弹药  EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 4 发射模式选择钮       |____Upgrade___|      []");
	printf("[]   大幅提升射速          EXP:250  $2500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 5 XM26挂载式霰弹枪     |____Upgrade___|      []");
	printf("[]   大幅提升伤害 散射     EXP:250  $2500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]                        |_____Exit_____|      []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	Locate(5,18);
	cout<<p.money;
	Locate(6,18);
	cout<<p.exp;
	int mx,my;
	while(1) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_Glock18 >= 50) {
			last_Glock18 = T;
			if(!KEY_DOWN(MOUSE_MOVED)) continue;
			my = Getmouse().xx;
			mx = Getmouse().yy;
			if(15 <= mx && mx <= 21) {
				if(my == 12) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(Glock18.upg.lev[1]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						Glock18.upg.lev[1] = 1;
						sayyes();
					}
				} else if(my == 16) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(Glock18.upg.lev[2]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						Glock18.upg.lev[2] = 1;
						sayyes();
					}
				} else if(my == 20) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(Glock18.upg.lev[3]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						Glock18.upg.lev[3] = 1;
						sayyes();
					}
				} else if(my == 24) {
					if(p.money < 2500 || p.exp < 250) sayno();
					else if(Glock18.upg.lev[4]) sayhave();
					else {
						p.money-=2500;
						p.exp-=250;
						Glock18.upg.lev[4] = 1;
						sayyes();
					}
				} else if(my == 28) {
					if(p.money < 2500 || p.exp < 250) sayno();
					else if(Glock18.upg.lev[5]) sayhave();
					else {
						p.money-=2500;
						p.exp-= 250;
						Glock18.upg.lev[5] = 1;
						sayyes();
					}
				} else if(my == 32) return;
			}
		}
	}
}

int last_MP5;
void upgrade_MP5() {
	system("cls");
	Locate(1,1);
	Setcolor(GRAY);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Upgrade Factory                     MP5    []");
	printf("[]                                              []");
	printf("[]    __...+__            money:                []");
	printf("[]    ]  /  \\             EXP:                  []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 1 回转环式照门         |____Upgrade___|      []");//12
	printf("[]   提升精准度 提升伤害   EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 2 金属防滑纹前护木     |____Upgrade___|      []");
	printf("[]   提升稳定性 提升伤害   EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 3 加长弹夹             |____Upgrade___|      []");
	printf("[]   增加弹夹容量和总弹药  EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 4 导轨前握把           |____Upgrade___|      []");
	printf("[]   降低后坐力 提升射速   EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 5 折叠枪托             |____Upgrade___|      []");
	printf("[]   提升移速              EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]                        |_____Exit_____|      []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	Locate(5,18);
	cout<<p.money;
	Locate(6,18);
	cout<<p.exp;
	int mx,my;
	while(1) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_MP5 >= 50) {
			last_MP5 = T;
			if(!KEY_DOWN(MOUSE_MOVED)) continue;
			my = Getmouse().xx;
			mx = Getmouse().yy;
			if(15 <= mx && mx <= 21) {
				if(my == 12) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(MP5.upg.lev[1]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						MP5.upg.lev[1] = 1;
						sayyes();
					}
				} else if(my == 16) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(MP5.upg.lev[2]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						MP5.upg.lev[2] = 1;
						sayyes();
					}
				} else if(my == 20) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(MP5.upg.lev[3]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						MP5.upg.lev[3] = 1;
						sayyes();
					}
				} else if(my == 24) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(MP5.upg.lev[4]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						MP5.upg.lev[4] = 1;
						sayyes();
					}
				} else if(my == 28) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(MP5.upg.lev[5]) sayhave();
					else {
						p.money-=1500;
						p.exp-= 150;
						MP5.upg.lev[5] = 1;
						sayyes();
					}
				} else if(my == 32) return;
			}
		}
	}
}

int last_FireGun;
void upgrade_FireGun() {
	system("cls");
	Locate(1,1);
	Setcolor(GRAY);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Upgrade Factory                     FireGun    []");
	printf("[]                                              []");
	printf("[]     ._._.              money:                []");
	printf("[]    [/[！]====[         EXP:                  []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 1 高能燃料配方         |____Upgrade___|      []");//12
	printf("[]   更高温 提升伤害       EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 2 大容量燃料罐         |____Upgrade___|      []");
	printf("[]   增加弹药容量          EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 3 加长喷射导管         |____Upgrade___|      []");
	printf("[]   更高温 提升伤害       EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 4 高压燃料泵           |____Upgrade___|      []");
	printf("[]   提升射速              EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 5 战术背带&两脚架      |____Upgrade___|      []");
	printf("[]   提升移速              EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]                        |_____Exit_____|      []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	Locate(5,18);
	cout<<p.money;
	Locate(6,18);
	cout<<p.exp;
	int mx,my;
	while(1) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_FireGun >= 50) {
			last_FireGun = T;
			if(!KEY_DOWN(MOUSE_MOVED)) continue;
			my = Getmouse().xx;
			mx = Getmouse().yy;
			if(15 <= mx && mx <= 21) {
				if(my == 12) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(FireGun.upg.lev[1]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						FireGun.upg.lev[1] = 1;
						sayyes();
					}
				} else if(my == 16) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(FireGun.upg.lev[2]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						FireGun.upg.lev[2] = 1;
						sayyes();
					}
				} else if(my == 20) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(FireGun.upg.lev[3]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						FireGun.upg.lev[3] = 1;
						sayyes();
					}
				} else if(my == 24) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(FireGun.upg.lev[4]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						FireGun.upg.lev[4] = 1;
						sayyes();
					}
				} else if(my == 28) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(FireGun.upg.lev[5]) sayhave();
					else {
						p.money-=1500;
						p.exp-= 150;
						FireGun.upg.lev[5] = 1;
						sayyes();
					}
				} else if(my == 32) return;
			}
		}
	}
}

int last_AWP;
void upgrade_AWP() {
	system("cls");
	Locate(1,1);
	Setcolor(GRAY);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Upgrade Factory                    AWP     []");
	printf("[]                                              []");
	printf("[]    ___===____          money:                []");
	printf("[]   [/*\"\"\"               EXP:                   []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 1 可折叠枪托           |____Upgrade___|      []");//12
	printf("[]   提升灵活性 减小重量   EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 2 可调贴腮板           |____Upgrade___|      []");
	printf("[]   提升稳定性 提升伤害   EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 3 高频脉冲器           |____Upgrade___|      []");
	printf("[]   增加换弹速度          EXP:150  $1500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 4 充能超导电池         |____Upgrade___|      []");
	printf("[]   增加弹容量            EXP:250  $2500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[] 5 610mm重型比赛级枪管  |____Upgrade___|      []");
	printf("[]   大幅提升伤害          EXP:250  $2500       []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]                        |_____Exit_____|      []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	Locate(5,18);
	cout<<p.money;
	Locate(6,18);
	cout<<p.exp;
	int mx,my;
	while(1) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_AWP >= 50) {
			last_AWP = T;
			if(!KEY_DOWN(MOUSE_MOVED)) continue;
			my = Getmouse().xx;
			mx = Getmouse().yy;
			if(15 <= mx && mx <= 21) {
				if(my == 12) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(AWP.upg.lev[1]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						AWP.upg.lev[1] = 1;
						sayyes();
					}
				} else if(my == 16) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(AWP.upg.lev[2]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						AWP.upg.lev[2] = 1;
						sayyes();
					}
				} else if(my == 20) {
					if(p.money < 1500 || p.exp < 150) sayno();
					else if(AWP.upg.lev[3]) sayhave();
					else {
						p.money-=1500;
						p.exp-=150;
						AWP.upg.lev[3] = 1;
						sayyes();
					}
				} else if(my == 24) {
					if(p.money < 2500 || p.exp < 250) sayno();
					else if(AWP.upg.lev[4]) sayhave();
					else {
						p.money-=2500;
						p.exp-=250;
						AWP.upg.lev[4] = 1;
						sayyes();
					}
				} else if(my == 28) {
					if(p.money < 2500 || p.exp < 250) sayno();
					else if(AWP.upg.lev[5]) sayhave();
					else {
						p.money-=2500;
						p.exp-= 250;
						AWP.upg.lev[5] = 1;
						sayyes();
					}
				} else if(my == 32) return;
			}
		}
	}
}

void shop() {
	system("cls");
	Locate(1,1);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Shop                                       []");
	printf("[]                                              []");
	printf("[]    \\#####]-+                                 []");
	printf("[]     \\####/       S E L L I N G ~             []");
	printf("[]      @  @                                    []");
	printf("[]                         ______________       []");
	printf("[]   Army         $1000   |______BUY_____|      []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]   Tac-B        $1000   |______BUY_____|      []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]   Blooder      $1500   |______BUY_____|      []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]   Spy          $2000   |______BUY_____|      []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]   HP+=50       $200    |______BUY_____|      []");
	printf("[]   Just in the next game                      []");
	printf("[]                         ______________       []");
	printf("[]   MP5          $3000   |______BUY_____|      []");
	printf("[]   Give you a MP5 instead of a Glock18        []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]    Money: $                                  []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]                        |_____EXIT_____|      []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	Locate(30,8);
	printf("%d",p.money);
	int last_shop = 0;
	bool done = 0;
	while(true) {
//    	p.money = 9999;
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_shop >= 50) {
			last_shop = T;
			if(!KEY_DOWN(MOUSE_MOVED)) {
				done = false;
				continue;
			}
			int kky = Getmouse().xx;
			int kkx = Getmouse().yy;
			if(15 <= kkx && kkx <= 21) {
				if(done) continue;
				done = true;
				if(kky == 9) {
					if(p.ar < 0 && p.money >= 1000) {
						p.ar = 1;
						p.money -= 1000;
						Locate(30,8);
						printf("             ");
						Locate(30,8);
						printf("%d",p.money);
						Locate(32,3),printf("You get it!");
						Sleep(1000);
						Locate(32,3),printf("                   ");
					} else {
						Locate(32,3),printf("You can't buy it!");
						Sleep(1000);
						Locate(32,3),printf("                   ");
					}
				} else if(kky == 12) {
					if(p.br < 0 && p.money >= 1000) {
						p.br = 1;
						p.money -= 1000;
						Locate(30,8);
						printf("             ");
						Locate(30,8);
						printf("%d",p.money);
						Locate(32,3),printf("You get it!");
						Sleep(1000);
						Locate(32,3),printf("                   ");
					} else {
						Locate(32,3),printf("You can't buy it!");
						Sleep(1000);
						Locate(32,3),printf("                   ");
					}
				} else if(kky == 15) {
					if(p.cr < 0 && p.money >= 1500) {
						p.cr = 1;
						p.money -= 1500;
						Locate(30,8);
						printf("             ");
						Locate(30,8);
						printf("%d",p.money);
						Locate(32,3),printf("You get it!");
						Sleep(1000);
						Locate(32,3),printf("                   ");
					} else {
						Locate(32,3),printf("You can't buy it!");
						Sleep(1000);
						Locate(32,3),printf("                   ");
					}
				} else if(kky == 18) {
					if(p.dr < 0 && p.money >= 2000) {
						p.dr = 1;
						p.money -= 2000;
						Locate(30,8);
						printf("             ");
						Locate(30,8);
						printf("%d",p.money);
						Locate(32,3),printf("You get it!");
						Sleep(1000);
						Locate(32,3),printf("                   ");
					} else {
						Locate(32,3),printf("You can't buy it!");
						Sleep(1000);
						Locate(32,3),printf("                   ");
					}
				} else if(kky == 21) {
					if(p.money >= 200 && !p.hpwave) {
						p.hpwave = true;
						p.money -= 200;
						Locate(30,8);
						printf("             ");
						Locate(30,8);
						printf("%d",p.money);
						Locate(32,3),printf("You get it!");
						Sleep(1000);
						Locate(32,3),printf("                   ");
					} else {
						Locate(32,3),printf("You can't buy it!");
						Sleep(1000);
						Locate(32,3),printf("                   ");
					}
				} else if(kky == 24) {
					if(p.money >= 3000 && !p.mp5) {
						p.mp5 = true;
						p.money -= 3000;
						Locate(30,8);
						printf("             ");
						Locate(30,8);
						printf("%d",p.money);
						Locate(32,3),printf("You get it!");
						Sleep(1000);
						Locate(32,3),printf("                   ");
					} else {
						Locate(32,3),printf("You can't buy it!");
						Sleep(1000);
						Locate(32,3),printf("                   ");
					}
				} else if(kky == 33) return;
			}
		}
	}
}

void read_army();
void read_Tac_B();
void read_blooder();
void read_spy();
void read_skill();
void read_producer();

void read_army() {
	system("cls");
	Locate(1,1);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Library                                    []");
	printf("[]    ____                                      []");
	printf("[]   |BOOK|                                     []");
	printf("[]   |    |         Story about army            []");
	printf("[]   |____|                                     []");
	printf("[]         _________________                    []");
	printf("[]   生存：■■■■_________]                   []");
	printf("[]         _________________                    []");
	printf("[]   灵活：■■■■_________]                   []");
	printf("[]         _________________                    []");
	printf("[]   技能：■_______________]                   []");
	printf("[]         _________________                    []");
	printf("[]   伤害：■■■■■■■■_]                   []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]   Name: Reznov          Sex: ♂              []");
	printf("[]   拥有高超战斗技巧的陆军上尉                 []");
	printf("[]   受过特殊训练，身体强壮，但没有技能。       []");
	printf("[]   僵尸是什么？战争又是什么？他并不在乎，对   []");
	printf("[]   他而言，生活就是子弹和酒。常年征战使他百   []");
	printf("[]   发百中，能攻击僵尸的要害从而产生致命伤害   []");
	printf("[]   然而同大多数退伍军人一样，他总是对伤口报   []");
	printf("[]   以爱管不管的态度，无疑这会让伤口恶化。军   []");
	printf("[]   用绷带在他手里发挥的作用还不如一点止疼片   []");
	printf("[]   技能：[K]绷带 回复少量生命                 []");
	printf("[]                                              []");
	printf("[]   “They fight against zombies,              []");
	printf("[]             And they die for zombies.”      []");
	printf("[]                              ——Reznov      []");
	printf("[]                         ______________       []");
	printf("[]                        |_____EXIT_____|      []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	int last_shop = 0;
	while(true) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_shop >= 50) {
			last_shop = T;
			if(!KEY_DOWN(MOUSE_MOVED)) continue;
			int kky = Getmouse().xx;
			int kkx = Getmouse().yy;
			if(15 <= kkx && kkx <= 21) {
				if(kky == 33) return;
			}
		}
	}
}
void read_Tac_B() {
	system("cls");
	Locate(1,1);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Library                                    []");
	printf("[]    ____                                      []");
	printf("[]   |BOOK|                                     []");
	printf("[]   |    |         Story about Tac-B           []");
	printf("[]   |____|                                     []");
	printf("[]         _________________                    []");
	printf("[]   生存：■■■■■■■■_]                   []");
	printf("[]         _________________                    []");
	printf("[]   灵活：■■■■_________]                   []");
	printf("[]         _________________                    []");
	printf("[]   技能：■■■■■■■___]                   []");
	printf("[]         _________________                    []");
	printf("[]   伤害：■■■■■■_____]                   []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]   TacticalBot MOD-B        Sex: N/A          []");
	printf("[]   战术机器人                                 []");//
	printf("[]   显然没有人类那样各种各样的麻烦和弱点，     []");
	printf("[]   使用者给它挂载了杀伤性极强的火焰喷射器.    []");
	printf("[]   提升功率产生的护盾能带来一段时间的无敌     []");
	printf("[]   效果，是从尸潮中突围的利器。经过一段时     []");
	printf("[]   间的充能后可以通过过载来进行自我修复，     []");
	printf("[]   回复效果有了本质的加强。                   []");
	printf("[]                                              []");
	printf("[]   技能：[K]模块过载 强力回血                 []");
	printf("[]         [L]护盾 短时间内免疫伤害             []");
	printf("[]                                              []");
	printf("[]   “I'm old,but I'm not obsolete”           []");
	printf("[]                                ——Tac-B     []");
	printf("[]                         ______________       []");
	printf("[]                        |_____EXIT_____|      []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	int last_shop = 0;
	while(true) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_shop >= 50) {
			last_shop = T;
			if(!KEY_DOWN(MOUSE_MOVED)) continue;
			int kky = Getmouse().xx;
			int kkx = Getmouse().yy;
			if(15 <= kkx && kkx <= 21) {
				if(kky == 33) return;
			}
		}
	}
}
void read_blooder() {
	system("cls");
	Locate(1,1);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Library                                    []");
	printf("[]    ____                                      []");
	printf("[]   |BOOK|                                     []");
	printf("[]   |    |         Story about blooder         []");
	printf("[]   |____|                                     []");
	printf("[]         _________________                    []");
	printf("[]   生存：■■■■■■■___]                   []");
	printf("[]         _________________                    []");
	printf("[]   灵活：■■■■_________]                   []");
	printf("[]         _________________                    []");
	printf("[]   技能：■■■■■■■___]                   []");
	printf("[]         _________________                    []");
	printf("[]   伤害：■■■■■■_____]                   []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]   Name: Dracula         Sex: ♂              []");
	printf("[]   血族                                       []");
	printf("[]   在暗夜和欲望中诞生的血族。                 []");
	printf("[]   技能机制独特，嗜血，极难驾驭。             []");
	printf("[]   由于暴露在城市的地表，即使月光也对他产     []");
	printf("[]   生伤害，必须依靠发动血怒吸血来维持生命     []");
	printf("[]   有着其他角色无可比拟的回血量和反杀能力     []");
	printf("[]   血怒也会增强攻击力，这给了Dracula说得      []");
	printf("[]   过去的输出。后期生命力极强，几乎无解。     []");
	printf("[]   技能：[K]释放人偶 损耗200生命 吸引怪物     []");
	printf("[]         [L]血怒 大幅增加攻击力 攻击可吸血    []");
	printf("[]                                              []");
	printf("[]   “Honer! And blood!”                      []");
	printf("[]                              ——Dracula     []");
	printf("[]                         ______________       []");
	printf("[]                        |_____EXIT_____|      []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	int last_shop = 0;
	while(true) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_shop >= 50) {
			last_shop = T;
			if(!KEY_DOWN(MOUSE_MOVED)) continue;
			int kky = Getmouse().xx;
			int kkx = Getmouse().yy;
			if(15 <= kkx && kkx <= 21) {
				if(kky == 33) return;
			}
		}
	}
}
void read_spy() {
	system("cls");
	Locate(1,1);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Library                                    []");
	printf("[]    ____                                      []");
	printf("[]   |BOOK|                                     []");
	printf("[]   |    |         Story about spy             []");
	printf("[]   |____|                                     []");
	printf("[]         _________________                    []");
	printf("[]   生存：■■■■_________]                   []");
	printf("[]         _________________                    []");
	printf("[]   灵活：■■■■■■■■_]                   []");
	printf("[]         _________________                    []");
	printf("[]   技能：■■■■■■■■_]                   []");
	printf("[]         _________________                    []");
	printf("[]   伤害：■■■■■■■___]                   []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]   Nick: ■■■■        Sex: ♂              []");
	printf("[]   特工                                       []");
	printf("[]   某特殊任务■■■■者，与■■爆发密切相关。 []");
	printf("[]   技能机制独特，擅长■■■■，奇袭对手。     []");
	printf("[]   [HIDE]                                     []");
	printf("[]                                              []");
	printf("[]   技能：[No Access: Error 52200]             []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]   “A***[s] w**e* C***a-N.”                 []");
	printf("[]                              ——■■■      []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]                        |_____EXIT_____|      []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	int last_shop = 0;
	while(true) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_shop >= 50) {
			last_shop = T;
			if(!KEY_DOWN(MOUSE_MOVED)) continue;
			int kky = Getmouse().xx;
			int kkx = Getmouse().yy;
			if(15 <= kkx && kkx <= 21) {
				if(kky == 33) return;
			}
		}
	}
}
void read_skill() {
	system("cls");
	Locate(1,1);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Library                                    []");
	printf("[]    ____                                      []");
	printf("[]   |BOOK|                                     []");
	printf("[]   |    |         How to Play                 []");
	printf("[]   |____|                                     []");
	printf("[]                                              []");
	printf("[]   操作说明                                   []");
	printf("[]       W A S D 移动   R 换弹   I 回头         []");
	printf("[]       K 技能1        L 技能2                 []");
	printf("[]       J 射击         Q 切换武器              []");
	printf("[]                                              []");
	printf("[]   武器升级系统                               []");
	printf("[]       通过给您的武器升级新的配件，您可以     []");
	printf("[]       获得更强的战斗力。满配件的武器是毁     []");
	printf("[]       天灭地的存在，建议优先升级常用武器     []");
	printf("[]                                              []");
	printf("[]   关于商店                                   []");
	printf("[]       除了初始人物外，我们还设计了三个角     []");
	printf("[]       色，您可以通过游戏得到经验和金币，     []");
	printf("[]       进而购买新人物和各种增益效果。         []");
	printf("[]                                              []");
	printf("[]   人物熟练度                                 []");
	printf("[]       每一局结束后将会对您进行测评，根据     []");
	printf("[]       评估得分（即超越的玩家的百分比）来     []");
	printf("[]       给与不同层次的经验金币以及熟练度奖     []");
	printf("[]       励。更高的熟练度会对人物有更多加成。   []");
	printf("[]   图鉴及攻略                                 []");
	printf("[]       请加入luogu团队，有更多福利。          []");
	printf("[]       www.luogu.org/team/show?teamid=12348   []");
	printf("[]                         ______________       []");
	printf("[]                        |_____EXIT_____|      []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	int last_shop = 0;
	while(true) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_shop >= 50) {
			last_shop = T;
			if(!KEY_DOWN(MOUSE_MOVED)) continue;
			int kky = Getmouse().xx;
			int kkx = Getmouse().yy;
			if(15 <= kkx && kkx <= 21) {
				if(kky == 33) return;
			}
		}
	}
}
void read_producer() {
	system("cls");
	Locate(1,1);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]                制作人员名单                  []");
	printf("[]                                              []");
	printf("[]  四向搜                                      []");//
	printf("[]   BLOG: www.cnblogs.com/floatiy              []");
	printf("[]   总策划，游戏设计，细节制作，后期制作       []");
	printf("[]                                              []");
	printf("[]  XiaoX                                       []");
	printf("[]   BLOG: www.luogu.org/blog/XiaoXkkk          []");//
	printf("[]   游戏设计，细节制作，后期制作，图标制作     []");
	printf("[]                                              []");
	printf("[]  sdfzzza                                     []");
	printf("[]   BLOG: blog.csdn.net/ancientone             []");
	printf("[]   发布攻略，图鉴制作，故事文稿               []");//
	printf("[]                                              []");
	printf("[]  墨雨笙                                      []");
	printf("[]   修改文案，后期宣传                         []");
	printf("[]……………………………………………………………[]");
	printf("[]             BUG反馈及VIP账号申请             []");
	printf("[]   请加入luogu团队——Alive.team：            []");
	printf("[]     www.luogu.org/team/show?teamid=12348     []");
	printf("[]……………………………………………………………[]");
	printf("[]                                              []");
	printf("[]                   写在最后                   []");
	printf("[]   我们想真正做一款属于程序员的游戏。做独立   []");
	printf("[]   游戏毕竟很不容易，千行代码的付出总还是希   []");
	printf("[]   望有所回报，您鼓励的话就是对我们最大的肯   []");
	printf("[]   定，如果能帮忙宣传我们会不胜感激。         []");
	printf("[]   联系方式 洛谷ID:四向搜  或  XiaoX          []");
	printf("[]                         ______________       []");
	printf("[]                        |_____EXIT_____|      []");
	printf("[]        Copyright (C)2018 XKAS_workteam.      []");
	printf("[]               All rights reserved.           []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	int last_shop = 0;
	while(true) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_shop >= 50) {
			last_shop = T;
			if(!KEY_DOWN(MOUSE_MOVED)) continue;
			int kky = Getmouse().xx;
			int kkx = Getmouse().yy;
			if(15 <= kkx && kkx <= 21) {
				if(kky == 32) return;
			}
		}
	}
}

inline void print_lab() {
	system("cls");
	Locate(1,1);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Library                                    []");
	printf("[]    ____                                      []");
	printf("[]   |BOOK|                                     []");
	printf("[]   |    |       Stories & Playing Skills      []");
	printf("[]   |____|                                     []");
	printf("[]                         ______________       []");
	printf("[]   Story about Army     |_____READ_____|      []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]   Story about Tac-B    |_____READ_____|      []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]   Story about Blooder  |_____READ_____|      []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]   Story about Spy      |_____READ_____|      []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]   Playing Skills       |_____READ_____|      []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]   Producers            |_____READ_____|      []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]                        |_____EXIT_____|      []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	return;
}

void library() {
	print_lab();
	int last_shop = 0;
	bool mouse_done=0;
	while(true) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_shop >= 50) {
			last_shop = T;
			if(!KEY_DOWN(MOUSE_MOVED)) {
				mouse_done = 0;
				continue;
			}
			if(mouse_done) continue;
			mouse_done = 1;
			int kky = Getmouse().xx;
			int kkx = Getmouse().yy;
			if(15 <= kkx && kkx <= 21) {
				if(kky == 9) read_army(),print_lab();
				else if(kky == 12) read_Tac_B(),print_lab();
				else if(kky == 15) read_blooder(),print_lab();
				else if(kky == 18) read_spy(),print_lab();
				else if(kky == 21) read_skill(),print_lab();
				else if(kky == 24) read_producer(),print_lab();
				else if(kky == 33) return;
			}
		}
	}
}

void mainpage() {
	system("cls");
	Locate(1,1);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Welcome back!Dear                          []");
	printf("[]                                              []");
	printf("[]   Maybe you want to ...                      []");
	printf("[]                         ______________       []");
	printf("[]   Buy something        |______GO______|      []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]   Start a New Game     |______GO______|      []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]   Read the Help        |______GO______|      []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]   Upgrade weapons      |______GO______|      []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]    Race Proficiency                          []");
	printf("[]                                              []");
	printf("[]    Army   :               Tac-B:             []");
	printf("[]                                              []");
	printf("[]    Blooder:               Spy  :             []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]    Informations                              []");
	printf("[]                                              []");
	printf("[]    Money: $              Exp:                []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	Locate(21,11);
	Locate(3,12);
	cout<<" "<<p.name<<endl;
	Locate(29,8);
	printf("%d",p.money);
	Locate(29,17);
	printf("%d",p.exp);
	Locate(21,9);
	if(p.ar < 0) printf("Locked");
	else if(p.ar < 100) printf("I");
	else if(p.ar < 200) printf("II");
	else if(p.ar < 400) printf("III");
	else if(p.ar < 800) printf("IV");
	else printf("V");
	Locate(21,20);
	if(p.br < 0) printf("Locked");
	else if(p.br < 100) printf("I");
	else if(p.br < 200) printf("II");
	else if(p.br < 400) printf("III");
	else if(p.br < 800) printf("IV");
	else printf("V");
	Locate(23,9);
	if(p.cr < 0) printf("Locked");
	else if(p.cr < 100) printf("I");
	else if(p.cr < 200) printf("II");
	else if(p.cr < 400) printf("III");
	else if(p.cr < 800) printf("IV");
	else printf("V");
	Locate(23,20);
	if(p.dr < 0) printf("Locked");
	else if(p.dr < 100) printf("I");
	else if(p.dr < 200) printf("II");
	else if(p.dr < 400) printf("III");
	else if(p.dr < 800) printf("IV");
	else printf("V");
}
long long last_choose;
void choose_race() {
	system("cls");
	Locate(1,1);
	Setcolor(GRAY);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Choose your race                           []");
	printf("[]                                              []");
	printf("[]    ~●█〓██▄▄▄▄▄▄▄                 []");
	printf("[]   ▄▅██████▅▄▃▂                   []");
	printf("[]   ██████████████               []");
	printf("[]   ◥⊙▲⊙▲⊙▲⊙▲⊙▲⊙▲◤               []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]   Army                 |____Choose ___|      []");//12
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]   Tac-B                |____Choose ___|      []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]   Blooder              |____Choose ___|      []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]   Spy                  |____Choose ___|      []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]                        |_____Exit_____|      []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");

	Locate(13,4);
	if(p.ar < 0) printf("[Locked]");
	else if(p.ar < 100) printf("★");
	else if(p.ar < 200) printf("★★");
	else if(p.ar < 400) printf("★★★");
	else if(p.ar < 800) printf("★★★★");
	else printf("★★★★★");
	Locate(17,4);
	if(p.br < 0) printf("[Locked]");
	else if(p.br < 100) printf("★");
	else if(p.br < 200) printf("★★");
	else if(p.br < 400) printf("★★★");
	else if(p.br < 800) printf("★★★★");
	else printf("★★★★★");
	Locate(21,4);
	if(p.cr < 0) printf("[Locked]");
	else if(p.cr < 100) printf("★");
	else if(p.cr < 200) printf("★★");
	else if(p.cr < 400) printf("★★★");
	else if(p.cr < 800) printf("★★★★");
	else printf("★★★★★");
	Locate(25,4);
	if(p.dr < 0) printf("[Locked]");
	else if(p.dr < 100) printf("★");
	else if(p.dr < 200) printf("★★");
	else if(p.dr < 400) printf("★★★");
	else if(p.dr < 800) printf("★★★★");
	else printf("★★★★★");

	int mx,my;
	while(1) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_choose >= 50) {
			last_choose = T;
			if(!KEY_DOWN(MOUSE_MOVED)) continue;
			my = Getmouse().xx;
			mx = Getmouse().yy;
			p.race = "none";
			if(15 <= mx && mx <= 21) {
				if(my == 12) {
					if(p.ar >= 0) {
						p.race = "army";
						return;
					} else Locate(30,4),printf("You don't have it!"),Sleep(1300),Locate(30,4),printf("                    ");
				} else if(my == 16) {
					if(p.br >= 0) {
						p.race = "Tac-B";
						return;
					} else Locate(30,4),printf("You don't have it!"),Sleep(1300),Locate(30,4),printf("                    ");
				} else if(my == 20) {
					if(p.cr >= 0) {
						p.race = "blooder";
						return;
					} else Locate(30,4),printf("You don't have it!"),Sleep(1300),Locate(30,4),printf("                    ");
				} else if(my == 24) {
					if(p.dr >= 0) {
						p.race = "spy";
						return;
					} else Locate(30,4),printf("You don't have it!"),Sleep(1300),Locate(30,4),printf("                    ");
				} else if(my == 32) {
					p.race = "exit";
					return;
				}
			}
		}
	}
}

void change_skill() {
	if(p.race=="army") p._skill.att=20,p._skill.def=20;
	else p._skill.att=0,p._skill.def=0;
	p._skill.att+=p._wear._body.attack+p._wear._bottom.attack+p._wear._head.attack;
	p._skill.def+=p._wear._body.defense+p._wear._bottom.defense+p._wear._head.defense;
}
void cleaning();
void newgame();
void SAVE_keep();

void upgrade_print() {
	system("cls");
	Locate(1,1);
	Setcolor(GRAY);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   By consuming your EXP and money, you can   []");
	printf("[]   make your weapons stronger or faster.      []");
	printf("[]   Choose the weapon you want to upgrade.     []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]    __==____+_           ______________       []");
	printf("[]   [/ |/ \\\\             |_____M4A1_____|      []");
	printf("[]                                              []");
	printf("[]    _,,,,,,,,            ______________       []");
	printf("[]   [/~[]~|              |_____AA12_____|      []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]   [/=#######=          |______MG3_____|      []");
	printf("[]      \"\"\"  /\\                                 []");
	printf("[]    ______..__           ______________       []");
	printf("[]   //~````^^^           |_____S686_____|      []");
	printf("[]                                              []");
	printf("[]      ,___               ______________       []");
	printf("[]      #\"\"               |___Glock-18___|      []");
	printf("[]                                              []");
	printf("[]   __...+__              ______________       []");
	printf("[]   ]  /  \\              |______MP5_____|      []");
	printf("[]                                              []");
	printf("[]    ._._.                ______________       []");
	printf("[]   [/[！]====[          |____FireGun___|      []");
	printf("[]                                              []");
	printf("[]    ___===____           ______________       []");
	printf("[]   [/*\"\"\"               |______AWP_____|      []");
	printf("[]                                              []");
	printf("[]                         ______________       []");
	printf("[]                        |_____EXIT_____|      []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
}
int last_upgrade;
void upgrade() {
	int mx,my;
	upgrade_print();
	while(1) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_upgrade >= 50) {
			last_upgrade = T;
			if(!KEY_DOWN(MOUSE_MOVED)) continue;
			my = Getmouse().xx;
			mx = Getmouse().yy;
			if(15 <= mx && mx <= 21) {
				if(my == 9) {
					upgrade_M4A1();
					upgrade_print();
				} else if(my == 12) {
					upgrade_AA12();
					upgrade_print();
				} else if(my == 15) {
					upgrade_MG3();
					upgrade_print();
				} else if(my == 18) {
					upgrade_S686();
					upgrade_print();
				} else if(my == 21) {
					upgrade_Glock18();
					upgrade_print();
				} else if(my == 24) {
					upgrade_MP5();
					upgrade_print();
				} else if(my == 27) {
					upgrade_FireGun();
					upgrade_print();
				} else if(my == 30) {
					upgrade_AWP();
					upgrade_print();
				} else if(my == 33) return;
			}
		}
	}
}
//string cdk;
//void CDK() {
//	system("cls");
//	Locate(1,1);
//	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
//	printf("[]                                              []");
//	printf("[]   CDK兑换                                    []");
//	printf("[]                                              []");
//	printf("[]                                              []");
//	printf("[]   输入您得到的兑换码：                       []");
//	printf("[]                                              []");
//	printf("[]                                              []");
//	printf("[]        ■■■■■■■■■■■■■■■        []");
//	printf("[]        ■                          ■        []");
//	printf("[]        ■■■■■■■■■■■■■■■        []");
//	printf("[]                                              []");
//	printf("[]                                              []");
//	printf("[]                                              []");
//	printf("[]                                              []");
//	printf("[]   如何得到兑换码？                           []");
//	printf("[]       加入 luogu团队，或者赞助此游戏均可     []");
//	printf("[]       获得兑换码（团队兑换码将会在各种节     []");
//	printf("[]       日期间发放）。                         []");
//	printf("[]                                              []");
//	printf("[]   团队网址                                   []");
//	printf("[]       www.luogu.org/team/show?teamid=12348   []");
//	printf("[]   赞助网址                                   []");
//	printf("[]                                              []");
//	printf("[]                                              []");
//	printf("[]                                              []");
//	printf("[]                                              []");
//	printf("[]                                              []");
//	printf("[]                                              []");
//	printf("[]                                              []");
//	printf("[]                         ______________       []");
//	printf("[]                        |_____BACK_____|      []");
//	printf("[]                                              []");
//	printf("[]                                              []");
//	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
//	Locate(10,7); cin>>cdk;
//	judge_cdk(cdk);
//	return;
//}

int last_mainpage;
//7 10 13 16's  16~21
void mainpage_modify() {
	int mx,my;
	mainpage();
	while(1) {
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_mainpage >= 50) {
			last_mainpage = T;
			if(!KEY_DOWN(MOUSE_MOVED)) continue;
			my = Getmouse().xx;
			mx = Getmouse().yy;
			if(15 <= mx && mx <= 21) {
				if(my == 7) {
					shop();
					mainpage();
				} else if(my == 10) {
					newgame();
					system("cls");
					SAVE_keep();
					mainpage();
				} else if(my == 13) {
					library();
					mainpage();
				} else if(my == 16) {
					upgrade();
					mainpage();
				}
			}
		}
	}
}


void init_window();
void init_player();
void init_zombie();
void init_map();
void init_welcome();
void init_print();
void init_Armor();
void init_picture();

int best_wave;
void SAVE_load() {
	if(p.name=="#Team") p.cr=1;
	else p.cr=-1;
	p.ar = p.br = p.dr = -1;
	p.ar = 1;
	p.money = 0;
	p.exp = 0;
	ifstream fin;
	fin.open("aipart.dll",ios::in);  //以写入和在文件末尾添加的方式打开.txt文件，没有的话就创建该文件。
	if (!fin.is_open()) exit(0);
	fin>>p.ar>>p.br>>p.cr>>p.dr;
	if(p.name=="#Team" && p.cr==-1) p.cr=1;
	fin>>p.money;
	fin>>p.exp;
	fin>>p.mp5>>p.hpwave;
	fin>>best_wave;
//	if(!p.ar) p.ar = -1;
	if(!p.br) p.br = -1;
	if(!p.cr) p.cr = -1;
	if(!p.dr) p.dr = -1;
	fin>>M4A1.upg.lev[1]>>M4A1.upg.lev[2]>>M4A1.upg.lev[3]>>M4A1.upg.lev[4]>>M4A1.upg.lev[5];
	fin>>AA12.upg.lev[1]>>AA12.upg.lev[2]>>AA12.upg.lev[3]>>AA12.upg.lev[4]>>AA12.upg.lev[5];
	fin>>MP5.upg.lev[1]>>MP5.upg.lev[2]>>MP5.upg.lev[3]>>MP5.upg.lev[4]>>MP5.upg.lev[5];
	fin>>Glock18.upg.lev[1]>>Glock18.upg.lev[2]>>Glock18.upg.lev[3]>>Glock18.upg.lev[4]>>Glock18.upg.lev[5];
	fin>>AWP.upg.lev[1]>>AWP.upg.lev[2]>>AWP.upg.lev[3]>>AWP.upg.lev[4]>>AWP.upg.lev[5];
	fin>>MG3.upg.lev[1]>>MG3.upg.lev[2]>>MG3.upg.lev[3]>>MG3.upg.lev[4]>>MG3.upg.lev[5];
	fin>>FireGun.upg.lev[1]>>FireGun.upg.lev[2]>>FireGun.upg.lev[3]>>FireGun.upg.lev[4]>>FireGun.upg.lev[5];
	fin>>S686.upg.lev[1]>>S686.upg.lev[2]>>S686.upg.lev[3]>>S686.upg.lev[4]>>S686.upg.lev[5];
	init_weapon();
	fin.close();
//	fread()
}

void SAVE_keep() {
//	fwrite()
	ofstream fout;
	fout.open("aipart.dll",ios::out);  //以写入和在文件末尾添加的方式打开.txt文件，没有的话就创建该文件。
	if (!fout.is_open()) exit(0);
	fout<<p.ar<<" "<<p.br<<" "<<p.cr<<" "<<p.dr<<endl;
	fout<<p.money<<endl;
	fout<<p.exp<<endl;
	fout<<p.mp5<<" "<<p.hpwave<<endl;
	fout<<best_wave<<endl;
	fout<<M4A1.upg.lev[1]<<" "<<M4A1.upg.lev[2]<<" "<<M4A1.upg.lev[3]<<" "<<M4A1.upg.lev[4]<<" "<<M4A1.upg.lev[5]<<endl;
	fout<<AA12.upg.lev[1]<<" "<<AA12.upg.lev[2]<<" "<<AA12.upg.lev[3]<<" "<<AA12.upg.lev[4]<<" "<<AA12.upg.lev[5]<<endl;
	fout<<MP5.upg.lev[1]<<" "<<MP5.upg.lev[2]<<" "<<MP5.upg.lev[3]<<" "<<MP5.upg.lev[4]<<" "<<MP5.upg.lev[5]<<endl;
	fout<<Glock18.upg.lev[1]<<" "<<Glock18.upg.lev[2]<<" "<<Glock18.upg.lev[3]<<" "<<Glock18.upg.lev[4]<<" "<<Glock18.upg.lev[5]<<endl;
	fout<<AWP.upg.lev[1]<<" "<<AWP.upg.lev[2]<<" "<<AWP.upg.lev[3]<<" "<<AWP.upg.lev[4]<<" "<<AWP.upg.lev[5]<<endl;
	fout<<MG3.upg.lev[1]<<" "<<MG3.upg.lev[2]<<" "<<MG3.upg.lev[3]<<" "<<MG3.upg.lev[4]<<" "<<MG3.upg.lev[5]<<endl;
	fout<<FireGun.upg.lev[1]<<" "<<FireGun.upg.lev[2]<<" "<<FireGun.upg.lev[3]<<" "<<FireGun.upg.lev[4]<<" "<<FireGun.upg.lev[5]<<endl;
	fout<<S686.upg.lev[1]<<" "<<S686.upg.lev[2]<<" "<<S686.upg.lev[3]<<" "<<S686.upg.lev[4]<<" "<<S686.upg.lev[5]<<endl;
	fout.close();
}

void init() {
	ofstream fout;
	fout.open("aipart.dll",ios::in);  //以写入和在文件末尾添加的方式打开.txt文件，没有的话就创建该文件。
	if (!fout.is_open()) ofstream fout("aipart.dll");
	fout.close();
	init_weapon();
	init_window();
	init_zombie();
	init_Armor();
	init_picture();
	init_welcome();
	SAVE_load();
	mainpage_modify();
}
void init_picture() {
	bmp[1].name="Glock18";
	bmp[2].name="S686";
	bmp[3].name="AWP";
	bmp[4].name="M4A1";
	bmp[5].name="MP5";
	bmp[6].name="AA12";
	bmp[7].name="MG3";
	bmp[8].name="FireGun";
	bmp[9].name="Knife";

	bmp[1].pic[0]="    ,___   ";
	bmp[1].pic[1]="    #\"\"    ";
	bmp[2].pic[0]=" ______..__";
	bmp[2].pic[1]="//~````^^^ ";
	bmp[3].pic[0]=" ___===____";
	bmp[3].pic[1]="[/*\"\"\"     ";
	bmp[4].pic[0]=" __==____+_";
	bmp[4].pic[1]="[/ |/ \\\\   ";
	bmp[5].pic[0]="__...+__   ";
	bmp[5].pic[1]="]  /  \\   ";
	bmp[6].pic[0]=" _,,,,,,,, ";
	bmp[6].pic[1]="[/~[]~|    ";
	bmp[7].pic[0]="[/=#######=";
	bmp[7].pic[1]="   \"\"\"  /\\ ";
	bmp[8].pic[0]=" ._._.     ";
	bmp[8].pic[1]="[/[!]====[";
	bmp[9].pic[0]="_____=____ ";
	bmp[9].pic[1]="\'\'\'\"|----/";
}
void init_race() {
	p.race = "none";
	while(p.race == "none") {
		choose_race();
		if(p.race == "exit") return;
	}
	system("cls");
	W(12,9,"Ready---  GO!");
	Sleep(2000);
	system("cls");
	return;
}
void init_Armor() {
	armour.defense=50;
	armour.type=2;
	armour.name="Armour";
	for(int i=0; i<=2; i++) {
		helmet[i].defense=20+i*10;
		helmet[i].type=1;
		helmet[i].lev=i+1;
		helmet[i].name="Helmet";//  +char(i+'0'+1)
	}
	spike.defense=10;
	spike.attack=10;
	spike.type=3;
	spike.name="spike";
	noe.name="none";
}
void init_window() {
	srand(time(NULL));
	Winset(150,500);
	SetConsoleTitle((LPCWSTR)"Alive");
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
void init_player() {
	if(p.race == "army")         if(p.ar < 100) p.hp+=0;
		else if(p.ar < 200) p.hp+=20;
		else if(p.ar < 400) p.hp+=30;
		else if(p.ar < 800) p.hp+=40;
		else p.hp+=70;
	else if(p.race == "Tac-B")   if(p.br < 100) p.hp+=0;
		else if(p.br < 200) p.hp+=20;
		else if(p.br < 400) p.hp+=30;
		else if(p.br < 800) p.hp+=40;
		else p.hp+=70;
	else if(p.race == "blooder") if(p.cr < 100) p.hp+=0;
		else if(p.cr < 200) p.hp+=20;
		else if(p.cr < 400) p.hp+=30;
		else if(p.cr < 800) p.hp+=40;
		else p.hp+=70;
	else if(p.race == "spy")     if(p.dr < 100) p.hp+=0;
		else if(p.dr < 200) p.hp+=20;
		else if(p.dr < 400) p.hp+=30;
		else if(p.dr < 800) p.hp+=40;
		else p.hp+=70;
	p.fc=1;
	p.hp = 100;
	p._skill.att = 10;
	p._skill.def = 0;
	p._skill.fat = 0;
	p._wear._hand = Glock18;
	p._wear._hand2 = Knife;
	p._wear._bottom = noe;
	p._wear._head = noe;
	p._wear._body = noe;
	p.add_hp = 0;
	p.last_add=p.last_app=p.last_shoot=0;
	p.last_blood=p.last_DNA=p.last_boom=p.last_flash=0;
	p.blood_angry=p.inm=p.servent=false;
	p.servend_hp=0;
	if(p.hpwave) p.hp += 50,p.hpwave = false;
	if(p.mp5) p._wear._hand = MP5;
//    if(p.name =="XiaoX") {
//        p._wear._body=armour;
//        p._wear._hand = Knife;
//        p.hp += 99999;
//    }
//	else if(p.name == "sxs") {
//        p._wear._body=armour;
//        p._wear._hand = MP5;
//        p.hp += 99999;
//    }
	if(p.name == "SWHsz"||
	        p.name == "Scatter"||
	        p.name == "He_Ren" ||
	        p.name == "jiangzeming" ||
	        p.name == "AC我最萌" ||
	        p.name == "floatiy" ||
	        p.name == "sdfzzza" ||
	        p.name == "cn_suqingnian" ||
	        p.name == "ztz11"||
	        p.name == "radish"||
	        p.name == "mys040124"||
	        p.name == "yzm"||
	        p.name == "学委"
	  ) {
//        p.name = "VIP-"+p.name;
		p.hp += 20;
		p._wear._hand = MP5;
	}
//	if(p.name == "floatiy") p.hp = 999999,now_wave = 10;
	if(p.name == "#Team") {
		p.hp+=20;
	}
	if(p.race == "army") {
		p.hp += 40;
		p._wear._head = helmet[0];
//        p.name = "Cpt."+p.name;
	} else if(p.race == "blooder") {
		p.hp -= 20;
//        p.name = "Dracula."+p.name;
	} else if(p.race == "Tac-B") {
		p._wear._hand = FireGun;
//        p.name = "Dr."+p.name;
	} else if(p.race == "spy") {
//        p.name = "Z-Plan-021";
		p._wear._bottom = spike;
		p._wear._hand = AA12;
		p._wear._hand2 = AWP;
	}
	p.max_hp = p.hp;
	return;
}
void init_zombie() {
	z[1].att = 20;
	z[1].hp = 50;
	z[1].name = "test-001";
	z[1].level = 1;
	z[1].speed = 5;

	z[2].att = 30;
	z[2].hp = 70;
	z[2].name = "test-002";
	z[2].level = 2;
	z[2].speed = 4;

	z[3].att = 50;
	z[3].hp = 150;
	z[3].name = "test-003";
	z[3].level = 3;
	z[3].speed = 2;

	z[4].att = 90;
	z[4].hp = 20;
	z[4].name = "test-004";
	z[4].level = 4;
	z[4].speed = 1;

	z[5].att = 100;
	z[5].hp = 800;
	z[5].name = "boss1";
	z[5].level = 5;
	z[5].speed = 3;

	z[6].att = 500;
	z[6].hp = 3000;
	z[6].name = "final-boss";
	z[6].level = 6;
	z[6].speed = 3;

	z[7].att = 170;
	z[7].hp = 70;
	z[7].name = "EXdog";
	z[7].level = 7;
	z[7].speed = 2;

	z[8].att = 100;
	z[8].hp = 300;
	z[8].name = "EXwheel";
	z[8].level = 8;
	z[8].speed = 4;

	z[9].att = 1000;
	z[9].hp = 10000;
	z[9].name = "final-boss";
	z[9].level = 9;
	z[9].speed = 3;
}
int map_tot=4;
inline void print_choose_map() {
	system("cls");
	Locate(1,1);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]   Choose Map                                 []");
	printf("[]    _____                                     []");
	printf("[]   |X--##|                                    []");
	printf("[]   |~~O~X|       Map List                     []");
	printf("[]   |_X___|                                    []");
	printf("[]                HARD     ______________       []");
	printf("[]   BurryTown   ☆       |______GO______|      []");
	printf("[]       -by floatiy                            []");
	printf("[]                         ______________       []");
	printf("[]   Rainforest  ☆☆☆   |______GO______|      []");
	printf("[]       -by sdfzzza                            []");
	printf("[]                         ______________       []");
	printf("[]   SDFZ        ☆☆     |______GO______|      []");
	printf("[]       -by ztz11                              []");
	printf("[]                         ______________       []");
	printf("[]   Slum        ☆☆☆   |______GO______|      []");
	printf("[]       -by Scatter                            []");
	printf("[]                         ______________       []");
	printf("[]   QD code     ☆☆     |______GO______|      []");
	printf("[]       -by sdfzzza                            []");
	printf("[]                         ______________       []");
	printf("[]   Palace      ☆☆     |______GO______|      []");
	printf("[]       -by AK47                               []");
	printf("[]                         ______________       []");
	printf("[]   605         ☆       |______GO______|      []");
	printf("[]       -by floatiy                            []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]   To be continued...  Waiting For Your Map!  []");
	printf("[]                                              []");
	printf("[]   Please send your map to XiaoX.             []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	return;
}

void choose_map() {
	print_choose_map();
	int last_shop = 0;
	bool mouse_done=0;
	bool choosed=0;
	while(true) {
		if(choosed) break;
		GetLocalTime( &sys );
		int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
		if(T - last_shop >= 50) {
			last_shop = T;
			if(!KEY_DOWN(MOUSE_MOVED)) {
				mouse_done = 0;
				continue;
			}
			if(mouse_done) continue;
			mouse_done = 1;
			int kky = Getmouse().xx;
			int kkx = Getmouse().yy;
			if(15 <= kkx && kkx <= 21) {
				if(kky == 9) cat="burrytown",choosed=1;
				else if(kky == 12) cat="Rainfst",choosed=1;
				else if(kky == 15) cat="sdfz",choosed=1;
				else if(kky == 18) cat="slum",choosed=1;
				else if(kky == 21) cat="QDcode",choosed=1;
				else if(kky == 24) cat="palace",choosed=1;
				else if(kky == 27) cat="605",choosed=1;
//				else if(kky == 33) return;
			}
		}
	}
}

void init_map() {
	ifstream fin;
	choose_map();
	string path=cat+".sev";
	fin.open(path.c_str());
	char tmp[30][30];
	for(int i=1; i<=SIZ; i++)
		fin>>tmp[i]+1;
	for(int i=1; i<=SIZ; i++)
		for(int j=1; j<=SIZ; j++)
			if(tmp[i][j]=='1') Map[i][j]="house_stone";
	for(int i = 1; i <= SIZ; i++) {
		Map[i][0] = "barrier";
		Map[i][SIZ + 1] = "barrier";
		Map[0][i] = "barrier";
		Map[SIZ + 1][i] = "barrier";
	}
	Map[0][0] = Map[SIZ+1][SIZ+1] = "barrier";
	fin>>pos_num;
	for(int i=1; i<=pos_num; i++) {
		fin>>Pos[i].x>>Pos[i].y;
	}
	fin>>p.x>>p.y;
	return;
}
bool init_lock_judge(string id,string pass) {
	//测试号
	if(id == "vis" && pass == "19260817") return true;
	//开发者
	if(id == "sxs" && pass == "147258") return true;
	if(id == "XiaoX" && pass == "875440114") return true;
	//贡献者
	if(id == "He_Ren" && pass == "heren666") return true;
	if(id == "jiangzeming" && pass == "moha0817") return true;
	if(id == "AC我最萌" && pass == "1357924") return true;
	if(id == "Scatter" && pass == "computa") return true;
	if(id == "SWHsz" && pass == "123456") return true;
	//others
	if(id == "mys040124" && pass == "mys040124") return true;
	if(id == "yzm" && pass == "yzm1003") return true;
	if(id == "学委" && pass == "xuewei") return true;
	if(id == "floatiy" && pass == "413084569") return true;
	if(id == "radish" && pass == "radish721105") return true;
	if(id == "ztz11" && pass == "ztz11123456") return true;
	if(id == "sdfzzza" && pass == "xxkasngjjp") return true;
	if(id == "cn_suqingnian" && pass == "trewq2trewq2") return true;
	if(id == "四方契" && pass == "国际金牌") return true;
	//团队VIP
	if(id == "#Team" && pass == "Alive") return true;
	return false;
}

void init_welcome() {
	while(1) {
		Locate(11,1);
		printf("            +========Welcome!========+            ");
		printf("            |username:               |            ");
		printf("            |========================|            ");
		printf("            |password:               |            ");
		printf("            +========================+            ");
		printf("                                                  ");
		printf("                                                  ");
		printf("                                                  ");
		printf("                                                  ");
		Setcolor(YELLOW);
		printf("         Tips:If you have joined our team,        ");
		printf("               you can get the VIP ID,            ");
		printf("          or you can use the visitor ID:          ");
		printf("           ID:\"vis\",password:\"19260817\"              ");
		Setcolor(GRAY);
		W(35,1,"V7.0.6");
		Locate(12,12);
		cin>>p.name;
		Locate(14,12);
		string password;
		cin>>password;
		if(init_lock_judge(p.name,password)) {
			Locate(16,1);
			printf("          Login successfully. Welcome back!          ");
			Sleep(1500);
			break;
		}
		Locate(16,1);
		printf("            Wrong password or username            ");
		Sleep(1500);
		system("cls");
	}
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle,&CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
	system("cls");
	return;
}
void print_player(int x,int y);
void init_print() {
	for(int i = 1; i <= SIZ; i++) {
		for(int j = 1; j <= SIZ; j++) {
			if(Map[i][j] == "house_stone") print_house_stone(i,j);
//          else if(Map[i][j] == "grass") print_grass(i,j);
			else printf("  ");
		}
	}
	Locate(26,1);
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");//26
	printf("[]                                              []");
	printf("[]  HP:                          Head:          []");
	printf("[]  Skill 1:                     Body:          []");
	printf("[]  Skill 2:                     Feet:          []");
	printf("[]  tot npc:                     Gun:           []");
	printf("[]  now npc:             Ammo:                  []");
	printf("[]  nowwave:                                    []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	W(27,3,p.name);
	W(27,20,p.race);
	print_player(p.x,p.y);
	return;
}

int lev[50];
int aim_npc,now_npc;

bool judge_move(int x,int y) {
	if(Map[x][y] == "barrier") return false;
	if(Map[x][y] == "house_stone") return false;
	if(Map[x][y] == "zombie" && p._wear._bottom.name=="spike") {
		flag[x][y]=10;
		return true;
	}
	if(Map[x][y] == "zombie") return false;
	if(Map[x][y] == "boom") return false;
	return true;
}
bool judge_servent(int x,int y) {
	if(Map[x][y] == "barrier") return false;
	if(Map[x][y] == "house_stone") return false;
	if(Map[x][y] == "zombie") return false;
	if(Map[x][y] == "boom") return false;
	if(Map[x][y] == "gift") return false;
	return true;
}
bool judge_zombie(int x,int y) {
	if(Map[x][y] == "barrier") return false;
	if(Map[x][y] == "house_stone") return false;
	if(Map[x][y] == "zombie") return false;
	if(Map[x][y] == "gift") return false;
	return true;
}
void print_player(int x,int y) {
	if(p.race == "army") Setcolor(DARKGREEN);
	else if(p.race == "blooder") Setcolor(RED);
	else if(p.race == "Tac-B") Setcolor(TEAL);
	else if(p.race == "spy") Setcolor(BLUE);
	if(p.blood_angry) Setcolor(DARKPINK);
	else if(p.inm) Setcolor(GREEN);
	Locate(x,y);
	printf("♀");
	Setcolor(GRAY);
}
void clean_player(int x,int y) {
	Locate(x,y);
	printf("  ");
}
void print_zombie(int x,int y,int num) {
	if(Map[x][y] == "boom") {
		for(int i = 1; i <= 500; i++) {
			if(bom[i].x == x && bom[i].y == y) {
				bom[i].tim = 0;
				break;
			}
		}
		Locate(x,y);
		Setcolor(RED);
		printf("##");
		Sleep(150);
		Setcolor(GRAY);
		a[num].hp -= 100;
		if(a[num].hp > 0) Map[x][y] = "zombie";
		else Map[x][y]= "",now_npc--;
		Locate(x,y),printf("  ");
		return;
	}
	Setcolor(DARKRED);
	Locate(x,y);
//  printf("%d",num);
	if(a[num].level == 1) printf("×");
	else if(a[num].level == 2) printf("♀");
	else if(a[num].level == 3) printf("◎");
	else if(a[num].level == 4) printf("¤");
	else if(a[num].level == 5) printf("☆");
	else if(a[num].level == 6) {
		Setcolor(TEAL);
		printf("★");
	} else if(a[num].level == 7) {
		Setcolor(DARKPINK);
		printf("¤");
	} else if(a[num].level == 8) {
		Setcolor(DARKPINK);
		printf("◎");
	} else if(a[num].level == 9) {
		Setcolor(DARKGREEN);
		printf("★");
	}
	Map[x][y] = "zombie";
	Setcolor(GRAY);
}
void clean_zombie(int x,int y) {
	Locate(x,y);
	Map[x][y] = "";
	printf("  ");
}

//0 down,1 right,2 up,3 left;
void get_gift(int x,int y) {
	int opt = rand() % 100 + 1;
	if(!(opt%3) && p._wear._hand != Knife) {
		if(p._wear._hand != S686 || p._wear._hand != Glock18) p._wear._hand.standby += p._wear._hand.clipspace*2;
		else p._wear._hand.standby += 20;
	}
	if(opt <= 5 && p._wear._body != armour) p._wear._body=armour;//5%
	else if(opt<= 10 && p._wear._bottom != spike) p._wear._bottom=spike;//5%
	else if(opt<= 15 && p._wear._hand != AWP) p._wear._hand = AWP;//5%
	else if(opt <= 25 && p._wear._hand != S686) p._wear._hand = S686;//10%
	else if(opt <= 35 && p._wear._hand != Glock18) p._wear._hand = Glock18;//10%
	else if(opt <= 40 && p._wear._hand != Knife) p._wear._hand = Knife;//5%
	else if(opt <= 50 && p._wear._hand != MG3)  p._wear._hand = MG3;//10%
	else if(opt <= 60 && p._wear._hand != M4A1) p._wear._hand = M4A1;//10%
	else if(opt <= 75) {
		if(p._wear._head != helmet[0]) p._wear._head = helmet[0];
		else if(p._wear._head.lev != 3) {
			int levvv=p._wear._head.lev;
			p._wear._head = helmet[levvv];
		}
	}//15%
	else if(opt <= 90) {
		int ttt=rand() % 2;
		if(ttt) {
			if(p.race == "spy") p._wear._hand = AA12;
			else if(p.race == "Tac-B") p._wear._hand = FireGun;
			else p.hp += 100,p.max_hp += 50;
		} else p.hp += 100,p.max_hp += 50;
	}//15%
	else if(opt<= 95 && p._wear._bottom != spike) p._wear._bottom=spike;//5%
	else p._wear._hand = MP5;//5%
	change_skill();
	Map[x][y] = "";
}

int last_mv=0;
void move(int x,int y,char dir) {
	GetLocalTime(&sys);
	int T = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
	if(p._wear._bottom != spike) {
		if(T - last_mv < 120+p._wear._hand.weight) return;
	} else if(T - last_mv < 70+p._wear._hand.weight/2) return;
	last_mv = T;
	if(dir == 'w') clean_player(x+1,y),p.fc=3;
	else if(dir == 'a') clean_player(x,y+1),p.fc=2;
	else if(dir == 's') clean_player(x-1,y),p.fc=0;
	else if(dir == 'd') clean_player(x,y-1),p.fc=1;
	p.x = x;
	p.y = y;
	if(Map[x][y] == "gift") {
		get_gift(x,y);
	}
	print_player(x,y);
	return;
}
int mlgb;
void killed();
void create_wave(int wave) {
	while(1) {
		int xxx = rand() % 25 + 1;
		int yyy = rand() % 25 + 1;
		if(jud_gift(xxx,yyy)) {
			Map[xxx][yyy] = "gift";
			Locate(xxx,yyy);
			Setcolor(TEAL);
			printf("□");
			break;
		}
	}
	if(p.race == "Tac-B") p.add_hp += 40,p.max_hp += 20;
	now_npc = 0;
	mlgb = 0;
	if(wave == 1) {
		lev[1] = 10;
		aim_npc = 10;
	} else if(wave == 2) {
		lev[1] = 10;
		lev[2] = 5;
		aim_npc = 15;
	} else if(wave == 3) {
		lev[2] = 10;
		lev[3] = 1;
		aim_npc = 11;
	} else if(wave == 4) {
		lev[1] = 20;
		lev[2] = 10;
		aim_npc = 30;
	} else if(wave == 5) {
		lev[2] = 20;
		lev[3] = 5;
		aim_npc = 25;
		p.max_hp += 30;
		p.add_hp = 30;
	} else if(wave == 6) {
		lev[2] = 30;
		lev[5] = 1;
		aim_npc = 31;
	} else if(wave == 7) {
		lev[3] = 5;
		lev[4] = 10;
		aim_npc = 15;
	} else if(wave == 8) {
//		p._wear._hand = AWP;
//		p.hp += 100;
		lev[5] = 1;
		lev[4] = 15;
		aim_npc = 16;
	} else if(wave == 9) {
		lev[3] = 5;
		lev[4] = 100;
		aim_npc = 105;
	} else if(wave == 10) {
		lev[1] = 200;
		lev[5] = 5;
		aim_npc = 205;
		p.max_hp += 50;
		p.add_hp = 50;
	} else if(wave == 11) {
//		p._wear._hand = S686;
		lev[6] = 1;
		lev[2] = 20;
		aim_npc = 21;
	} else if(wave == 12) {
		lev[3] = 15;
		lev[4] = 10;
		lev[5] = 5;
		aim_npc = 30;
	} else if(wave == 13) {
		lev[8] = 7;
		aim_npc = 7;
	} else if(wave == 14) {
		p.add_hp += 100;
		lev[7] = 5;
		lev[4] = 20;
		aim_npc = 25;
	} else if(wave == 15) {
		lev[5] = 15;
		lev[2] = 50;
		aim_npc = 65;
		p.max_hp += 100;
		p.add_hp = 150;
	} else if(wave == 16) {
		lev[6] = 1;
		lev[5] = 2;
		lev[4] = 20;
		aim_npc = 26;
	} else if(wave == 17) {
		lev[7] = 20;
		aim_npc = 20;
	} else if(wave == 18) {
		lev[4] = 20;
		lev[8] = 5;
		aim_npc = 25;
	} else if(wave == 19) {
		lev[5] = 10;
		lev[7] = 20;
		aim_npc = 20;
	} else if(wave == 20) {
		lev[7] = 30;
		lev[4] = 70;
		aim_npc = 100;
		p.max_hp += 200;
		p.add_hp = 500;
	} else if(wave == 21) {
		lev[9] = 1;
		lev[8] = 5;
		lev[7] = 15;
		lev[6] = 1;
		lev[5] = 5;
		aim_npc = 27;
		p.add_hp = 300;
		p.max_hp += 1000;
		p._skill.att += 100;
	} else if(wave == 22) {
		p.hp = -1;
		return;
	}
}
void cz(int x,int y) {
	if(!judge_zombie(x,y)) return;
	for(int i = 1; i <= 9; i++) {
		if(lev[i]) {
			lev[i]--;
			now_npc++;
			mlgb++;
			a[mlgb] = z[i];
			a[mlgb].x = x;
			a[mlgb].y = y;
			a[mlgb].die = 0;
			return;
		}
	}
}
void create_zombie() {
	int opt = rand() % pos_num +1;
	int X=Pos[opt].x,Y=Pos[opt].y;
	cz(X,Y);
}
const int dix[] = {0,1,-1,0,0};
const int diy[] = {0,0,0,1,-1};
int vis[30][30];
bool judge_bfs(int x,int y) {
	if(Map[x][y] == "barrier") return false;
	if(Map[x][y] == "house_stone") return false;
	if(Map[x][y] == "gift") return false;
	if(!p.servent)
		if(x == p.x && y == p.y) return false;
//  if(Map[x][y] == "zombie") return false;
	return true;
}
void bfs(int x,int y) {

	queue<int> q;
	memset(vis,0,sizeof(vis));
	q.push(x);
	q.push(y);
	int curx,cury;
	int cu = 0;
	while(!q.empty()) {
		curx = q.front(),q.pop();
		cury = q.front(),q.pop();
		for(int i = 1; i <= 4; i++) {
			if(!vis[curx+dix[i]][cury+diy[i]] && judge_bfs(curx+dix[i],cury+diy[i])) {

				vis[curx+dix[i]][cury+diy[i]] = vis[curx][cury] + 1;
				q.push(curx+dix[i]),q.push(cury+diy[i]);
			}
		}

	}
//  W(1,1,"1926");
}
void print_picture(string tmp) {
	int id;
	for(int i=1; i<=9; i++) {
		if(bmp[i].name==tmp) {
			id=i;
			break;
		}
	}
	Setcolor(YELLOW);
	W(32,19,bmp[id].pic[0]);
	W(33,19,bmp[id].pic[1]);
	Setcolor(GRAY);
}
void print_mation() {
//    Locate(27,6);
//    printf("att:%d   def:%d   ",p._skill.att,p._skill.def);
	Locate(28,8);
	printf("%d/%d       ",p.hp,p.max_hp);
	Locate(33,8);
	printf("%d   ",now_wave);
	Locate(32,8);
	printf("%d   ",now_npc);
	Locate(31,8);
	printf("%d   ",aim_npc);
//    printf("nownpc: %d,aimnpc: %d     ",now_npc,aim_npc);
	Weapon tmp=p._wear._hand;
	Locate(31,20);
	cout<<"          ";
	Locate(31,20);
	cout<<tmp.name;
//    Locate(30,14);
//    if(!p.crenade) Setcolor(RED);
//    else Setcolor(YELLOW);
//    printf("%d    ",p.crenade);
//    Setcolor(GRAY);
	Locate(33,14);
	if(!tmp.nowclip) {
		Setcolor(RED);
		printf("0");
		Setcolor(GRAY);
		if(now_wave == 11 || now_wave == 21) printf("/∞    ");
		else printf("/%d    ",tmp.standby);
	} else if(tmp.clipspace==INF) {
		printf("∞/∞   ");
	} else if(now_wave != 11 && now_wave != 21) printf("%d/%d    ",tmp.nowclip,tmp.standby);
	else printf("%d/∞    ",tmp.nowclip);
	char lev=p._wear._head.lev+'0';
	if(p._wear._head != noe) W(28,20,p._wear._head.name+"<"+lev+">");
	else W(28,20,p._wear._head.name);
	W(29,20,p._wear._body.name);
	W(30,20,p._wear._bottom.name);
	print_picture(tmp.name);
}
double spk_tmp;
double recovery_tmp,flash_tmp;
void print_skill_k(int t) {
	if(p.race=="spy") {
		Locate(29,7);
		flash_tmp= 1.0*p.last_flash+ 15000.0-t;
		if(flash_tmp < 0) flash_tmp = 0;
		if(flash_tmp==0.0) printf(" Ready");
		else printf(" %.1lfs   ",flash_tmp/1000.0);
	} else {
		Locate(29,7);
		recovery_tmp = 1.0*p.last_add + 20000.0 - t;
		if(recovery_tmp < 0) recovery_tmp = 0;
		if(p.race == "blooder") {
			if(p.hp<200)printf(" HP>200");
			else if(p.servent) printf(" Setted");
			else printf(" Ready ");
		} else if(recovery_tmp==0.0) printf(" Ready");
		else printf(" %.1lfs   ",recovery_tmp/1000.0);
	}
}
void print_skill_l(int t) {
	if(p.race == "blooder") {
		Locate(30,7);
		if(p.race == "blooder") spk_tmp = 1.0*p.last_blood + 15000.0 - t;
		if(spk_tmp < 0) spk_tmp = 0;
		if(spk_tmp==0.0) printf(" Ready    ");
		else if(spk_tmp >= 10000) {
			Setcolor(RED);
			printf(" killing  ");
			Setcolor(GRAY);
		} else printf(" %.1lfs     ",spk_tmp/1000.0);
	} else if(p.race == "Tac-B") {
		Locate(30,7);
		spk_tmp = 1.0*p.last_DNA + 20000.0 - t;
		if(spk_tmp < 0) spk_tmp = 0;
		if(spk_tmp==0.0) printf(" Ready    ");
		else if(spk_tmp >= 15000) {
			Setcolor(GREEN);
			printf("immortal   ");
			Setcolor(GRAY);
		} else printf(" %.1lfs     ",spk_tmp/1000.0);
	} else if(p.race == "spy") {
		Locate(30,7);
		spk_tmp = 1.0*p.last_boom + 15000.0 - t;
		if(spk_tmp < 0) spk_tmp = 0;
		if(spk_tmp==0.0) printf(" Ready    ");
		else printf(" %.1lfs     ",spk_tmp/1000.0);
	} else if(p.race == "army") {
		Locate(30,7);
		printf(" N/A   ");
	}
}

void Create_boom_clip(int z) {
	Weapon gun=M4A1;
	GetLocalTime( &sys );
	int fc=bom[z].dir;
	int x=bom[z].x;
	int y=bom[z].y;
	shoot(x,y,fc,gun);
}

void boom_shot() {
	for(int i = 1; i <= 500; i++) {
		if(Map[bom[i].x][bom[i].y] != "boom") bom[i].tim = 0;
		if(bom[i].tim > 0) Create_boom_clip(i);
	}
	return;
}

void cheak_boom() {
	for(int i = 1; i <= 500; i++) {
		if(bom[i].tim <= 0) continue;
		bom[i].tim -= 10;
		if(bom[i].tim <= 0) {
			int x = bom[i].x;
			int y = bom[i].y;
			Locate(x,y);
			Setcolor(RED);
			printf("##");
			Sleep(150);
			Setcolor(GRAY);
			Map[x][y]= "";
			Locate(x,y),printf("  ");
		}
	}
}

void goodbye();
int t;
int tot;
int zx,zy,bst;
int nxt;
int last_time = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
void world_modify() {
	if(p.hp <= 0) return;
	GetLocalTime( &sys );
	t = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
	if(p._wear._hand == MG3 && p._wear._hand.reseting && t - p._wear._hand.st >= 4000 ) end_reload();
	else if(p._wear._hand == MP5 && p._wear._hand.reseting && t - p._wear._hand.st >= 700 ) end_reload();
	else if(S686.upg.lev[4] && p._wear._hand == S686 && p._wear._hand.reseting && t - p._wear._hand.st >= 900 ) end_reload();
	else if(p._wear._hand == Glock18 && p._wear._hand.reseting && t - p._wear._hand.st >= 1000 ) end_reload();
	else if(AWP.upg.lev[3] && p._wear._hand == AWP && p._wear._hand.reseting && t - p._wear._hand.st >= 900 ) end_reload();
	else if(p._wear._hand.reseting && t - p._wear._hand.st >= 1700 ) end_reload();
	if(t - last_time >= 100) {
		last_time = t;
		tot++;
		tot %= 120;
		if(p.add_hp) {
			p.add_hp--;
			if(p.hp < p.max_hp) p.hp++;
			if(p.hp < p.max_hp && p.race == "Tac-B") p.hp += 3;
		}
		if(t - p.last_blood > 5000) p.blood_angry = 0;
		if(t - p.last_DNA > 5000) p.inm = 0;
		if(!(tot%10) && p.race == "blooder") p.hp -= 1;

		if(!p.blood_angry && p.blood_angry_end) {
			p.blood_angry_end = false;
			print_player(p.x,p.y);
		}
		if(!p.inm && p.inm_end) {
			p.inm_end = false;
			print_player(p.x,p.y);
		}

		print_skill_k(t);
		print_skill_l(t);
		if(tot % 8 == 0) boom_shot();
		int i,j;
//		for(i = 1; i <= 25; i++) {
//			for(j = 1; j <= 25; j++) {
//				if(Map[i][j] == "boom") {
//					Locate(i,j);
//					Setcolor(YELLOW);
//					printf("●");
//					Setcolor(GRAY);
//				}
//			}
//		}

		if(p.servent) {
			Locate(p.sx,p.sy);
			Setcolor(RED);
			printf("♂");
			Setcolor(GRAY);
		}
		if(p.servent) bfs(p.sx,p.sy);
		else bfs(p.x,p.y);

		if(p.servent) vis[p.sx][p.sy] = 0;
		else vis[p.x][p.y] = 0;

		if(!now_npc && !(tot % 5) ) {
			create_wave(++now_wave);
			create_zombie();
		}
		if(aim_npc > mlgb && !(tot % 5)) {
			create_zombie();
		}
		for(i = 1; i <= 100; i++) {
			if(a[i].hp <= 0 || a[i].die) {
				continue;
			}
			if(flag[a[i].x][a[i].y]) {

				if(p.blood_angry) {
					p.hp += min(flag[a[i].x][a[i].y],a[i].hp)/3;
					a[i].hp -= flag[a[i].x][a[i].y];
				} else if(p.race == "army") {
					a[i].hp -= flag[a[i].x][a[i].y];
				} else if(p.race == "spy") {
					a[i].hp -= flag[a[i].x][a[i].y]/2;
				}
				a[i].hp-=flag[a[i].x][a[i].y];
			}
//          Locate(31,3); cout<<a[i].hp;
			if(a[i].hp<=0) {
				a[i].die=1;
				clean_zombie(a[i].x,a[i].y);
				now_npc--;
			}

			if(!(a[i].hp <= 0 || a[i].die) && !(tot % a[i].speed)) {
				bst = 100000000;
				nxt = 0;
				for(int j = 1; j <= 4; j++) {
					if(vis[a[i].x + dix[j]][a[i].y + diy[j]] < bst && judge_zombie(a[i].x + dix[j],a[i].y + diy[j])) {
						bst = vis[a[i].x + dix[j]][a[i].y + diy[j]];
						nxt = j;
					}
				}
				if(nxt) {
					clean_zombie(a[i].x,a[i].y);
					print_zombie(a[i].x+=dix[nxt],a[i].y+=diy[nxt],i);
				}
				if(a[i].x == p.sx && a[i].y == p.sy) {
					p.servend_hp -= a[i].att;
					p.hp -= a[i].att/5;
				} else if(a[i].x == p.x && a[i].y == p.y) {
					if(!p.inm) {
						int tmpharm=(a[i].att*(1-(p._skill.def*0.5*0.01)));
						if(tmpharm<0) tmpharm=0;
						p.hp -= tmpharm;
					}
				}

			}

		}
		cheak_boom();
		print_mation();
		memset(flag,0,sizeof(flag));
		if(p.hp <= 0) {
			killed();
			return;
		}
		if(p.servend_hp <= 0 && p.servent) {
			p.servent = false;
			p.sx=0;
			p.sy=0;
			p.add_hp = 50;
			Map[p.sx][p.sy] = "";
		}
	}
}

bool judge_boom(int x,int y) {
	if(Map[x][y]==""||Map[x][y]=="grass") return true;
	return false;
}

void change_weapon() {
	Weapon TMP=p._wear._hand;
	if(TMP.reseting) TMP.reseting=0;
	p._wear._hand=p._wear._hand2;
	p._wear._hand2=TMP;
}
int time_skill;
void skill_k() {
	GetLocalTime( &sys );
	time_skill = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
	if(p.race == "spy") {
		if(time_skill - p.last_boom > 15000) {
			int fc=p.fc;
			int xx=p.x+dx[fc];
			int yy=p.y+dy[fc];
			if(!judge_boom(xx,yy)) return;
			p.last_boom = time_skill;
			Map[xx][yy] = "boom";
			Locate(xx,yy);
			Setcolor(YELLOW);
			printf("□");
			Setcolor(GRAY);
			if(bom_num == 500) bom_num = 0;
			bom[++bom_num].x = xx;
			bom[bom_num].y = yy;
			bom[bom_num].tim = 6000;//60s
			bom[bom_num].id = bom_num;
			bom[bom_num].dir = p.fc;
			return;
		}
	} else if(p.race == "blooder" && p.hp > 200 && !p.servent) {
		int fc=p.fc;
		int xx=p.x+dx[fc];
		int yy=p.y+dy[fc];
		if(!judge_servent(xx,yy)) return;
		p.hp -= 150;
		p.sx=xx;
		p.sy=yy;
		p.servend_hp = 200;
		p.servent = true;
//      Map[xx][yy] = "servent";
		Locate(xx,yy);
		Setcolor(RED);
		printf("♂");
		Setcolor(GRAY);
		return;
	} else if(time_skill - p.last_add > 20000) {
		if(p.race == "Tac-B") p.add_hp = 40;
		else if(p.race == "blooder") return;
		else p.add_hp = 20;
		p.last_add = time_skill;
	}
}

void skill_sp() {
	GetLocalTime( &sys );
	time_skill = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
	if(p.race == "blooder") {
		if(p.hp <= 20) return;
		if(time_skill - p.last_blood > 15000) {
			p.add_hp = 30;
			p.hp -= 20;
			p.last_blood = time_skill;
			p.blood_angry = true;
			p.blood_angry_end = true;
			print_player(p.x,p.y);
		}
	} else if(p.race == "spy") {
		if(time_skill - p.last_flash <= 15000) return;
		int fc=p.fc;
		int xx=p.x+dx[fc]*3;
		int yy=p.y+dy[fc]*3;
		p.last_flash=time_skill;
		if(xx>SIZ || yy>SIZ || xx<1 || yy<1) return;
		if(!judge_move(xx,yy))  return;
		else {
			Setcolor(YELLOW);
			Locate(p.x,p.y);
			printf("∷");
			Sleep(50);
			Setcolor(GRAY);
			clean_player(p.x,p.y);
			print_player(xx,yy);
			p.x=xx;
			p.y=yy;
		}
	} else if(p.race == "Tac-B") {
		if(time_skill - p.last_DNA > 20000) {
			if(p.max_hp <= 140) p.max_hp += 10;
			p.add_hp = 10;
			p.last_DNA = time_skill;
			p.inm = true;
			p.inm_end = true;
			print_player(p.x,p.y);
		}
	}
}

void DEBUG();
#define turn_back p.fc=3-p.fc
void play() {
	char ch;
	create_wave(1);
//    while(true) {
//        if(kbhit()) {
//            ch = getch();
//            if(ch == 'w' && judge_move(p.x-1,p.y)) move(p.x-1,p.y,'w');
//            else if(ch == 'a' && judge_move(p.x,p.y-1)) move(p.x,p.y-1,'a');
//            else if(ch == 's' && judge_move(p.x+1,p.y)) move(p.x+1,p.y,'s');
//            else if(ch == 'd' && judge_move(p.x,p.y+1)) move(p.x,p.y+1,'d');
//            else if(ch == '+') DEBUG();
//            else if(ch == 'j') Create_clip();
//            else if(ch == 'r') reload();
//            else if(ch == 'k') skill_k();
//            else if(ch == 'l') skill_sp();
//        }
//        clipmove();
//        world_modify();
//        if(p.hp <= 0) break;
//    }
	while(true) {
		if(IsKeyPressed(87) && judge_move(p.x-1,p.y)) move(p.x-1,p.y,'w');//w
		if(IsKeyPressed(65) && judge_move(p.x,p.y-1)) move(p.x,p.y-1,'a');//a
		if(IsKeyPressed(83) && judge_move(p.x+1,p.y)) move(p.x+1,p.y,'s');//s
		if(IsKeyPressed(68) && judge_move(p.x,p.y+1)) move(p.x,p.y+1,'d');//d
		if(IsKeyPressed(74)) Create_clip();//j
		if(kbhit()) {
			ch = getch();
			if(ch == 'r' || ch == 'R') reload();
			else if(ch == 'i' || ch == 'I') turn_back;
			else if(ch == 'k' || ch == 'K') skill_k();
			else if(ch == 'l' || ch == 'L') skill_sp();
			else if(ch == 'q' || ch == 'Q') change_weapon();
		}
		clipmove();
		world_modify();
		if(p.hp <= 0) break;
	}
}

void DEBUG() {
	system("cls");
	Locate(1,1);
	int i,j;
	for(i = 1; i <= 25; i++) {
		for(j = 1; j <= 25; j++) {
			if(Map[i][j] == "house_stone") printf("[]");
			else if(Map[i][j] == "zombie") printf("+=");
			else if(Map[i][j] == "boom") printf("##");
			else printf("%2d",vis[i][j]);
//          else printf("  ");
		}
	}
//  Locate(26,1);
//  cout<<now_npc<<" "<<aim_npc<<" "<<endl;
//  for(i = 1; i <= 20; i++) cout<<a[i].x<<" "<<a[i].y<<" "<<a[i].level<<endl;
	Sleep(5000);
	system("cls");
}

void killed() {
	int over_rate;
	if(now_wave==1) over_rate=3;
	else if(now_wave==2) over_rate=3;
	else if(now_wave==3) over_rate=6;
	else if(now_wave==4) over_rate=14;
	else if(now_wave==5) over_rate=17;
	else if(now_wave==6) over_rate=23;
	else if(now_wave==7) over_rate=25;
	else if(now_wave==8) over_rate=28;
	else if(now_wave==9) over_rate=30;
	else if(now_wave==10) over_rate=36;
	else if(now_wave==11) over_rate=43;
	else if(now_wave==12) over_rate=49;
	else if(now_wave==13) over_rate=56;
	else if(now_wave==14) over_rate=62;
	else if(now_wave==15) over_rate=70;
	else if(now_wave==16) over_rate=77;
	else if(now_wave==17) over_rate=84;
	else if(now_wave==18) over_rate=86;
	else if(now_wave==19) over_rate=90;
	else if(now_wave==20) over_rate=94;
	else if(now_wave==21) over_rate=98;
	else if(now_wave==22) over_rate=100;
	else over_rate=100;
	int get_exp = 0;
	int get_money = over_rate * 8;
	get_exp = get_money/12;
	p.exp += get_exp+5;
	p.money += get_money;
	if(now_wave>=10) get_money+=100;
	if(now_wave>16) get_money+=1000,get_exp+=1000;
	system("cls");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	if(now_wave<=16) {
		printf("[]                 You Died !                   []");
		printf("[]                                              []");
		printf("[]       after fighting against %2d wave         []",now_wave);
	} else {
		printf("[]                 You Win !                    []");
		printf("[]                                              []");
		printf("[]       after fighting against %2d wave        []",now_wave);
	}
	printf("[]                                              []");
	printf("[]                                              []");
	if(now_wave > best_wave)
		printf("[]                 NEW RECORD!                  []"),best_wave=now_wave;
	else
		printf("[]                                              []");
	printf("[]                                              []");
	printf("[]          Good luck to the next time!         []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]   Find resourse                              []");
	printf("[]       Money: %3d                             []",get_money);
	printf("[]        EXP : %3d                             []",get_exp+5);
	printf("[]                                              []");
	printf("[]   Your grade is :                            []");
	printf("[]                                              []");
	printf("[]   Over    %% player                           []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[]                                              []");
	printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");
	Locate(31,6);
	printf("%d",over_rate);
	Locate(29,12);
	if(now_wave < 3) printf("C");
	else if(now_wave < 6) printf("B-");
	else if(now_wave < 9) printf("B");
	else if(now_wave < 15) printf("A");
	else if(now_wave < 16) printf("S");
	else if(now_wave < 18) printf("SS");
	else if(now_wave < 20) printf("SSS");
	else printf("Master! Orz");
	if(p.race == "army") p.ar += over_rate*2;
	else if(p.race == "Tac-B") p.br += over_rate*2;
	else if(p.race == "blooder") p.cr += over_rate*2;
	else if(p.race == "spy") p.dr += over_rate*2;
	Sleep(3000);
	return;
}
void cleaning() {
//	zombie
	int i;
	for(i = 1; i <= 400; i++) {
		a[i].die = 0;
		a[i].name="";
		a[i].att = a[i].hp = a[i].speed = a[i].x = a[i].y = 0;
	}
	for(i = 1; i <= 500; i++) bom[i].tim = 0;
	bom_num = 0;
	memset(flag,0,sizeof(flag));
	for(i = 0; i <= SIZ+1; i++) {
		for(int j = 0; j <= SIZ+1; j++) {
			Map[i][j]="";
		}
	}
	for(int i = 1; i <= 6; i++) {
		if(lev[i]) lev[i]=0;
	}
	memset(vis,0,sizeof(vis));
	aim_npc = now_npc = now_wave = 0;
//	now_wave=16;
	tot = 0;
	nxt = 0;
	mlgb = 0;
	last_time = sys.wMilliseconds + sys.wSecond * 1000 + sys.wMinute * 1000*60 + sys.wHour * 1000*3600;
	recovery_tmp = flash_tmp = 0;
//	cleanplayer();
}

void newgame() {
	system("cls");
	num_cre = 0;
	cleaning();
	init_zombie();
	init_map();
	init_race();
	if(p.race == "exit") return;
	init_player();
	init_print();
	change_skill();
//	system("cls");
//	Locate(1,1);
//	if(M4A1.upg.lev[1]) cout <<" Yes";
//	Sleep(50000);
	play();
	return;
}

int main() {
	Setcolor(GRAY);
	init();
	Sleep(5000);
	return 0;
}

/*

AWP
 ___===____
[/*"""

Glock18
    ,___
    #""

M4A1
 __==____+_
[/ |/ \\

MP5
__...+__
]  /  \

S686
 ______..__
//~````^^^

AA12
 _,,,,,,,,
[/~[]~|

MG3
[/=#######=
   """  /\

Knife
_____=____
`----|'''"

printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");//26
printf("[] (     name     )                    ( race  )[]");
printf("[]  HP:      75 /120             Hand:          []");
printf("[]  Skill 1:   ready             Body:          []");
printf("[]  Skill 2:   04.55s            Feet:          []");
printf("[]  tot npc:   50                               []");
printf("[]  now npc:             Ammo:      __==____+_  []");
printf("[]  nowwave:             100/100   [/ |/ \\     []");
printf("[][][][][][][][][][][][][][][][][][][][][][][][][]");

*/
