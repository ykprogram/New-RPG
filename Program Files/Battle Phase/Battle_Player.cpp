#include "DxLib.h"
#include "../UsePrototype.h"
#include "Battle_Player.h"

IniStatus_t Status[2]={
	// HP, MP, LV, PW, DF,   \, SP, SP2, EX, MHP, MMP
	{ 100, 20,  1, 30, 30, 100, 10,   0,  0, 100, 20 },
	{  70, 60,  1, 15, 40, 100,  8,   0,  0,  70, 60 },
};

static int LevelUp[99]={
	10,
	20,
	40,
	80,
	160,
	320,
	640,
	1280,
	2560,
	5120,
	10240
};
void Battle_Player_Ini( Character_t *Character ){
	// 勇者のステータスの初期化
	for(int i=0;i<2;i++){
		(Character+i)->HP		=Status[i].HP;
		(Character+i)->MP		=Status[i].MP;
		(Character+i)->Power	=Status[i].Power;
		(Character+i)->Defense	=Status[i].Defense;
		(Character+i)->LEVEL	=Status[i].LEVEL;
		(Character+i)->Money	=Status[i].Money;
		(Character+i)->Speed	=Status[i].Speed;
		(Character+i)->Speed2	=Status[i].Speed2;
		(Character+i)->Ex		=Status[i].Ex;
		(Character+i)->MaxHP	=Status[i].MaxHP;
		(Character+i)->MaxMP	=Status[i].MaxMP;
	}
}

int Levelup(Character_t *Character){
	for(int i=0;i<2;i++){
		for(int j=0;j<99;j++){
			if( (Character+i)->Ex > LevelUp[j] && (Character+i)->LEVEL == (j+1) ){
				(Character+i)->LEVEL+=1;
				return 1;
			}
		}
	}
	return 0;
}