#ifndef DEF_BATTLEMGR_H  //��dinclude�h�~

#define DEF_BATTLEMGR_H
	
	#ifdef BATTLEMGR_PROTOTYPE
	
	#include "Battle.h"
	#include "../BeforeBattle/Before_Battle.h"
	#include "Battle_Player.h"
	int BattleMgr( Character_t *Character, EnemySelect_t EnemySelect );
	void Battle_Ini��();

	#endif // BATTLEMGR_PROTOTYPE END

#endif // DEF_BATTLE_H END