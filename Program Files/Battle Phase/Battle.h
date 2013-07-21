#ifndef DEF_BATTLE_H  //��dinclude�h�~

#define DEF_BATTLE_H
typedef struct{
	char ItemName[30];
	int NumberOfItem;
}TestItem_t;
typedef struct {
	int HP;			// �̗�
	int MP;			// ϼޯ��߲��
	int LEVEL;		// ���x��
	int Power;		// �U����
	int Defense;	// �h���
	int Money;		// ������
	int Speed;		// ���x
	int Speed2;		// �퓬�Ŏg���U����
	int Ex;			// �o���l
	int Graph;		// �摜
	int MaxHP;		// �ő�̗�
	int MaxMP;		// �ő�ϼޯ��߲��
	char Name[30];	// ���O
	// ��������͎�ɓG���g��(E) �摜�֌W
	int X;			// x���W(E)
	int Y;			// y���W(E)
	char Pass[50];	// �摜�̂���Ƃ��܂ł̃p�X(E)
	int NameNumber;	// ���O��\������Ƃ��Ɏg��(E)
	int Flag;		// �\���t���O
	// ��������̓A�C�e��
	TestItem_t waku[10];
}Character_t;

	#ifdef BATTLE_PROTOTYPE

	#include "../Define.h"
	#include "../Function.h"
	void Battle_Ini();
	int Battle( Character_t *Character, int EnemyType );
	int DamageCalc( Character_t Attacker, Character_t Defender );
	int	DamageCalc2( Character_t Attacker, Character_t *Defender );
	int DamageCalc3( Character_t *Character, Character_t *Defender, int StartLog, int EndLog, int Go, int EnemyType, int Flag);

	#endif //BATTLE_PROTOTYPE END

#endif