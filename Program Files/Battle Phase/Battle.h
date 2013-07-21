#ifndef DEF_BATTLE_H  //二重include防止

#define DEF_BATTLE_H
typedef struct{
	char ItemName[30];
	int NumberOfItem;
}TestItem_t;
typedef struct {
	int HP;			// 体力
	int MP;			// ﾏｼﾞｯｸﾎﾟｲﾝﾄ
	int LEVEL;		// レベル
	int Power;		// 攻撃力
	int Defense;	// 防御力
	int Money;		// 所持金
	int Speed;		// 速度
	int Speed2;		// 戦闘で使う攻撃順
	int Ex;			// 経験値
	int Graph;		// 画像
	int MaxHP;		// 最大体力
	int MaxMP;		// 最大ﾏｼﾞｯｸﾎﾟｲﾝﾄ
	char Name[30];	// 名前
	// ここからは主に敵が使う(E) 画像関係
	int X;			// x座標(E)
	int Y;			// y座標(E)
	char Pass[50];	// 画像のあるとこまでのパス(E)
	int NameNumber;	// 名前を表示するときに使う(E)
	int Flag;		// 表示フラグ
	// ここからはアイテム
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