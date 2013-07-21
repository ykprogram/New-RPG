#ifndef EDF_BEFORE_BATTLE_H

#define EDF_BEFORE_BATTLE_H

typedef struct{
	int Enemy[4];
}EnemySelect_t;

	#ifdef BEFORE_BATTLE_PROTOTYPE

	#include "../Music/Music.h"
	#include "../Battle Phase/Battle.h"
	#include "../Define.h"
	#include "../Map/Map.h"
	void Before_Battle_Ini();
	void Set_Before_BattleMovie();
	int BeforeBattleMgr(EnemySelect_t *EnemyType, Map_t);
	void BeforeBattleMovie();
	void BeforeBattleMovie1();
	void BeforeBattleMovie2(int);

	#endif //BEFORE_BATTLE_PROTOTYPE END

#endif