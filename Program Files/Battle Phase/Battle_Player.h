#ifndef EDF_BATTLE_PLAYER_H  //二重include防止

#define EDF_BATTLE_PLAYER_H

typedef struct{
	int HP;			// 体力
	int MP;			// ﾏｼﾞｯｸﾎﾟｲﾝﾄ
	int LEVEL;		// レベル
	int Power;		// 攻撃力
	int Defense;	// 防御力
	int Money;		// 所持金
	int Speed;		// 速度
	int Speed2;		// 速度2
	int Ex;			// 経験値
	int MaxHP;		// 最大体力
	int MaxMP;		// 最大ﾏｼﾞｯｸﾎﾟｲﾝﾄ
}IniStatus_t;

	#ifdef BATTLE_PLAYER_PROTOTYPE

	#include "Battle.h"

	void Battle_Player_Ini( Character_t *Character );

	int Levelup(Character_t *Character);

	#endif // BATTLE_PLAYER_PROTOTYPE END

#endif // EDF_BATTLE_PLAYER_H END