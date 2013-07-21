#ifndef EDF_BATTLE_PLAYER_H  //��dinclude�h�~

#define EDF_BATTLE_PLAYER_H

typedef struct{
	int HP;			// �̗�
	int MP;			// ϼޯ��߲��
	int LEVEL;		// ���x��
	int Power;		// �U����
	int Defense;	// �h���
	int Money;		// ������
	int Speed;		// ���x
	int Speed2;		// ���x2
	int Ex;			// �o���l
	int MaxHP;		// �ő�̗�
	int MaxMP;		// �ő�ϼޯ��߲��
}IniStatus_t;

	#ifdef BATTLE_PLAYER_PROTOTYPE

	#include "Battle.h"

	void Battle_Player_Ini( Character_t *Character );

	int Levelup(Character_t *Character);

	#endif // BATTLE_PLAYER_PROTOTYPE END

#endif // EDF_BATTLE_PLAYER_H END