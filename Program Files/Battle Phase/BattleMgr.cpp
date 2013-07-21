#include "DxLib.h"
#include "../UsePrototype.h"
#include "../Function.h"
#include "BattleMgr.h"
/*
　敵A敵Bみたいに　味方の並び替え機能はなしとする
　呪文は呪文ごとに数値を割り振る
*/

static int BattlePhase=0;
static int MenuSelect=0;
static int EnemyExpSum=0;

//敵の初期化
Character_t EnemyStatus[2]={
	// HP,  MP, Lv,  力,  守,  金, 速度, 速度2, 経験, 画像,  MHP,  MMP,              名前,    X,   Y,						  パス,num
	{  10,  10,  1,  15,  10,  10,    5,     0,    1,    0,   10,   10,           "ゼリー", 200, 200,       "RPG DATA\\ゼリー.png", 0 ,1},
	{ 100, 100, 10, 150, 100, 100,   10,     0,  100,    0,  100,  100, "アーマードゼリー", 200,  80, "RPG DATA\\ゼリー type2.png", 1 ,1}
};
int ini=0;
static Character_t Enemy[4];

static MenuElement_t BattleMenu[4]={
	{30, 380, 30, 30, GetColor(255,255,255), 255, 255, 255, "たたかう"},
	{30, 430, 30, 30, GetColor(255,255,255), 255/2, 255/2, 255/2, "アイテム"},

	{120, 380, 120, 120, GetColor(255,255,255), 255/2, 255/2, 255/2, "にげる"},
	{120, 430, 120, 120, GetColor(255,255,255), 255/2, 255/2, 255/2, "さくせん"}
};

static MenuElement_t SelectEnemy[4]={
	{30, 380, 30, 30, GetColor(255,255,255), 255, 255, 255, " "},
	{30, 430, 30, 30, GetColor(255,255,255), 255/2, 255/2, 255/2, " "},

	{120, 380, 120, 120, GetColor(255,255,255), 255/2, 255/2, 255/2, " "},
	{120, 430, 120, 120, GetColor(255,255,255), 255/2, 255/2, 255/2, " "}
};

static StringScript_t BattleMenuString[11];
static StringScript_t BattleMenuString2[11]={
	// 出現
	{ 230,380,GetColor(255,255,255), "魔物が現れた!",0},		//0
	{ 230,400,GetColor(255,255,255), "勇者は何をする?",0},		//1

	// 逃げる
	{ 230,380,GetColor(255,255,255), "勇者は逃げ出した!",0},	//2

	// 攻撃
	{ 230,380,GetColor(255,255,255), "勇者の攻撃！"},			//3
	{ 230,400,GetColor(255,255,255), "%dダメージ！",1 },		//4

	// 敵の攻撃
	{ 230,380,GetColor(255,255,255), "%sの攻撃！",2},			//5
	{ 230,400,GetColor(255,255,255), "%dダメージ！",1},			//6

	//勝利
	{ 230,380,GetColor(255,255,255), "魔物に勝利した！" },		//7
	{ 230,400,GetColor(255,255,255), "経験値%dを手に入れた",1},	//8

	{ 230,380,GetColor(255,255,255), "勇者はレベルが%dになった!",1},//9
};
// はじめのx,y,ゲージのフレーム枠, 中身, 色, その隣に中身の数字をを描画するかしないか
static void DrawGauge(int x, int y, int GaugeFrame, int GaugeIn, int ColorFrame, int ColorIn, int Flag){
	DrawBox( x, y, x+GaugeFrame, y+15, ColorFrame, FALSE );
	DrawBox( x+1, y+1, x+1+GaugeIn-2, y-1+15,ColorIn, TRUE );
	if(Flag==TRUE)FontNumDraw( x+GaugeFrame, y, GaugeIn );
}

static int NowNumber=0;
//static char NowNumber=0;	//三行のうちどこまでを表示しているか
static char test[3][100]={{""},{""},{""}};		//三行の透明の枠があると考えると良い
static int DrawBattleMessageString(int Start, int End, StringScript_t MenuString[],int EnemyName=0,int Number=0){
	
	//もしStartとNowNumberの合計値がEndより大きかったら,終了処理をする。
	if(End<NowNumber+Start){
		NowNumber=0;
		return 100; 
	}
	
	// 文字表示for文は今まで表示した文を表示したままにするため
	for( int i=Start; i<=(NowNumber+Start); i++){
		if(MenuString[i].Percentd_and_Percents==2)DrawFormatString( MenuString[i].x, MenuString[i].y, MenuString[i].color, MenuString[i].hyoji, EnemyStatus[EnemyName].Name);
		else if(MenuString[i].Percentd_and_Percents==1)DrawFormatString( MenuString[i].x, MenuString[i].y, MenuString[i].color, MenuString[i].hyoji, Number);
		else DrawFormatString( MenuString[i].x, MenuString[i].y, MenuString[i].color, MenuString[i].hyoji);
		DrawFormatString(0,200+(i*20),GetColor(255,255,255),"%d",i);
	}
	//もしZキーを押し,最後まで表示されていたら(表示している最中でなければ)
	if( CheckHitKey2(KEY_INPUT_Z)==1 )NowNumber++;
	
	DrawFormatString(40,200,GetColor(255,255,255),"%d",NowNumber);
	return NowNumber;
}
int DrawIni;
void Battle_Iniβ(){
	DrawIni=LoadGraph("RPG DATA\\cursor.png");
	EnemyStatus[0].Graph = LoadGraph( EnemyStatus[0].Pass );
	EnemyStatus[1].Graph = LoadGraph( EnemyStatus[1].Pass );

	for( int i=0; i<10; i++ )BattleMenuString[i]=BattleMenuString2[i];
	
}
int width[4]={0,0,0,0}, heith[4]={0,0,0,0};
int SecondIni(Character_t Substituted, int i){
	GetGraphSize( Substituted.Graph, &width[i], &heith[i]);
	return 0;
}
int number=0;
int DrawCursor( Character_t Enemy[4] ){	
	int Flag[4]={ Enemy[0].Flag, Enemy[1].Flag, Enemy[2].Flag, Enemy[3].Flag};
	if( CheckHitKey2( KEY_INPUT_LEFT ) == 1 ){
		number=(number+3)%4;
		for(int i=0; i<4; i++)if(Enemy[number].Flag==0)number=(number+3)%4;
	}
	if( CheckHitKey2( KEY_INPUT_RIGHT ) == 1 ){number=(number+1)%4;}
	if(Flag[number]==0)number=(number+1)%4;
	if(Flag[number]==1)DrawGraph(Enemy[number].X+(width[number]/2)+80*number,/* Enemy[number].Y+40*/15, DrawIni,TRUE);
	if(CheckHitKey2(KEY_INPUT_Z)==1)return number;
	if(CheckHitKey2(KEY_INPUT_X)==1)return 200;
	return 100;
}

void Substitution( Character_t *Substituted, Character_t EnemyStatus, int Flag = TRUE ){
	if(Flag==TRUE){
		Substituted->Defense= EnemyStatus.Defense;
		Substituted->Ex		= EnemyStatus.Ex;
		Substituted->Graph	= EnemyStatus.Graph;
		Substituted->HP		= EnemyStatus.HP;
		Substituted->LEVEL	= EnemyStatus.LEVEL;
		Substituted->MaxHP	= EnemyStatus.MaxHP;
		Substituted->MaxMP	= EnemyStatus.MaxMP;
		Substituted->Money	= EnemyStatus.Money;
		Substituted->MP		= EnemyStatus.MP;
		Substituted->NameNumber=EnemyStatus.NameNumber;
		Substituted->Power	= EnemyStatus.Power;
		Substituted->Speed	= EnemyStatus.Speed+GetRand(3);
		Substituted->X		= EnemyStatus.X;
		Substituted->Y		= EnemyStatus.Y;
		strcpy_s(Substituted->Name, sizeof(Substituted->Name), EnemyStatus.Name);
		Substituted->Flag	= 1;
	}else if(Flag==FALSE){
		Substituted->Defense	= 0;
		Substituted->Ex			= 0;
		Substituted->Graph		= 0;
		Substituted->HP			= 0;
		Substituted->LEVEL		= 0;
		Substituted->MaxHP		= 0;
		Substituted->MaxMP		= 0;
		Substituted->Money		= 0;
		Substituted->MP			= 0;
		strcpy_s(Substituted->Name, sizeof(""),"");
		Substituted->Power		= 0;
		Substituted->Speed		= 0;
		Substituted->X			= 0;
		Substituted->Y			= 0;
		Substituted->Flag		= 0;
	}
}

int Data[6];
void SpeedChecker( Character_t *Character, Character_t Enemy[4]){
	int data[6]={ Enemy[0].Speed, Enemy[1].Speed, Enemy[2].Speed, Enemy[3].Speed, Character->Speed, (Character+1)->Speed };
	for(int i=0; i< 6; i++){
		int max = i ;
		for(int j=i+1; j<6; j++)if(data[max]<data[j])max = j ;
		swap(&data[i],&data[max]) ;
	}
	for(int i=0; i<6; i++)Data[i]=data[i];
}

static int DamageCalc( Character_t Attacker, Character_t Defender ){
	// 通常攻撃の計算式の答えを返す
	return (int)( Attacker.LEVEL*2*Attacker.Power /Defender.Defense +2 )*( 85+ GetRand(15) )/100;
}

static int BattleTurn=0;
static int Damage=0;
static int Rand=0;
static int Attack[2]={0,0};
static int doing=0;
static int once=0;
// 敵抽選はBefore_Battle.cppで行う
int BattleMgr( Character_t *Character, EnemySelect_t EnemySelect){
	MessageFrame();

	switch(BattlePhase){
		// 初期化 敵の枠に代入
		case 0:for(int i=0;i<4;i++){
			if(EnemySelect.Enemy[i]!=0)Substitution( &Enemy[i], EnemyStatus[(EnemySelect.Enemy[i]-1)]);
			if(EnemySelect.Enemy[i]==0)Substitution( &Enemy[i], EnemyStatus[(EnemySelect.Enemy[i]-1)], FALSE);
			SecondIni( Enemy[i], i);
		}BattlePhase=1;break;

		// 戦闘に入ったとこ
		case 1:if(DrawBattleMessageString( 0, 1, BattleMenuString)==100)BattlePhase=2;break;

		// 何を行うかの選択
		case 2:switch(DrawMenu( 2, 2, KEY_INPUT_Z, BattleMenu )){
				case 0:BattlePhase=4;SpeedChecker( Character, Enemy );break;
				case 1:break;
				case 2:BattlePhase=3;break;
				case 3:break;
			   }break;

		// 逃げる時の文表示
		case 3:if( DrawBattleMessageString( 2, 2, BattleMenuString ) == 100 ){BattlePhase=0;MenuSelect=0;return 2;}break;

		// 攻撃する敵を選択数
		case 4:{
			switch(MenuSelect){
				case 0:{
					DrawFormatString(230,380,GetColor(255,255,255),"勇者はどの敵を攻撃する？");
					Attack[0]=DrawCursor( Enemy );
					if(Attack[0]!=100){
						if(Attack[0]!=200)MenuSelect++;
						BattlePhase=2;
					}
				}break;

				case 1:{
					DrawFormatString(230,380,GetColor(255,255,255),"勇者(二人目)どの敵を攻撃する？");
					Attack[1]=DrawCursor( Enemy );
					if(Attack[1]!=100){
						if(Attack[1]==200)BattlePhase=2;
						else MenuSelect++;
					}
				}break;

				case 2:{MenuSelect=0;BattlePhase=5;}break;
			}
		}break;

		// 攻撃実行
		case 5:{
			// 敵四体
			for(int i=0;i<4;i++){
				if( Enemy[i].Speed==Data[BattleTurn] && doing==0 && (Enemy[i].Speed2==0)){
					doing=1;
					if( Enemy[i].Defense && Enemy[i].HP>0){
						switch( DrawBattleMessageString( 5, 6, BattleMenuString, Enemy[i].NameNumber, Damage )){
							case 0:if(once==0){Rand=GetRand(1);Damage=DamageCalc( Enemy[i], *(Character+Rand) );once++;}break;
							case 1:if(Rand!=2)(Character+Rand)->HP-=Damage;Rand=2;break;
							case 100:Enemy[i].Speed2=1;Rand=0;BattleTurn++;once=0;break;
						}
					}else if( Enemy[i].HP<=0 ){
						BattleTurn++;
						Enemy[i].Speed2++;
						Enemy[i].Flag=0;
					}
				} 
			}

			if( !Character->Speed2 && Character->Speed==Data[BattleTurn] && !doing ){
				doing=1;
				if(Enemy[Attack[0]].Flag){
					switch( DrawBattleMessageString( 3, 4, BattleMenuString, Enemy[Attack[0]].NameNumber, Damage )){
						case 0:if(!once){Damage=DamageCalc( *Character, Enemy[Attack[0]] );once++;}break;
						case 1:if(Rand!=2)Enemy[Attack[0]].HP-=Damage;Rand=2;break;
						case 100:Character->Speed2=1;if(Enemy[Attack[0]].HP<=0)Enemy[Attack[0]].Flag=0;Rand=0;BattleTurn++;once=0;break;
					}
				}else BattleTurn+=1;
			}

			if( !(Character+1)->Speed2 && (Character+1)->Speed==Data[BattleTurn] && !doing){
				doing=1;
				if(Enemy[Attack[1]].Flag){
					switch( DrawBattleMessageString( 3, 4, BattleMenuString, Enemy[Attack[1]].NameNumber, Damage )){
						case 0:if(once==0){Damage=DamageCalc( *(Character+1), Enemy[Attack[1]] );once++;}break;
						case 1:if(Rand!=2)Enemy[Attack[1]].HP-=Damage;Rand=2;break;
						case 100:(Character+1)->Speed2=1;if(Enemy[Attack[1]].HP<=0)Enemy[Attack[1]].Flag=0;Rand=0;BattleTurn++;once=0;break;
					}
				}else BattleTurn+=1;
			}

			//BattleTurnが6は全員行動したことになっている
			if( !doing && BattleTurn==6){
				doing=1;
				BattlePhase=2;
				for(int i=0; i<4; i++ )Enemy[i].Speed2=0;
				for(int i=0; i<2; i++)(Character+i)->Speed2=0;
				//敵全滅
				if( Enemy[0].HP<=0 && Enemy[1].HP<=0 && Enemy[2].HP<=0 && Enemy[3].HP<=0 ){
					for(int i=0 ; i<4; i++){ //先に経験値の合計を求める
						EnemyExpSum+=Enemy[i].Ex;
						Substitution( &Enemy[i], EnemyStatus[(EnemySelect.Enemy[i]-1)], FALSE);
					}
					BattlePhase=6;
				}
				else BattleTurn=0;
			}
		}doing=0;break;//case 5の終了

		// 戦闘終了後の処理
		case 6:{
			if( DrawBattleMessageString( 7, 8, BattleMenuString,0,EnemyExpSum ) == 100 ){
				doing=0;
				BattlePhase=0;
				BattleTurn=0;
				for(int i=0; i<4; i++ )Enemy[i].Speed2=0;
				for(int i=0; i<2; i++)(Character+i)->Speed2=0; 
				if(Character->HP>=0)Character->Ex+=EnemyExpSum;
				// EnemyExpSumは一度の戦闘で手に入れた経験値の合計
				EnemyExpSum=0;
				if(Levelup(Character)==1)BattlePhase=7;
				else return 2;
			}
		}break;
		// レベルアップ時
		case 7:{
			if( DrawBattleMessageString( 9, 9, BattleMenuString, 0, Character->LEVEL) == 100 ){
				BattlePhase=0;
				return 2;
			}
		}break;
	}//switchの終了
	
	//数字表示系　敵の数字を表示
	DrawFormatString(420,360,GetColor(255,255,255),"BattleTurn:%d",BattleTurn);
	DrawFormatString(150,100,GetColor(255,255,255),"%d,%d,%d,%d,%d,%d",Data[0],Data[1],Data[2],Data[3],Data[4],Data[5]);
	DrawFormatString(150,120,GetColor(0,255,0),"%d",Character->Ex);
	for(int i=0;i<4;i++)DrawFormatString(320,240+20*i,GetColor(255,255,255),"%d",EnemySelect.Enemy[i]);	

	//条件を満たしている敵の枠のみ表示
	for(int i=0; i<4; i++)if(Enemy[i].HP>0 && Enemy[i].Flag==1)DrawGraph( Enemy[i].X+80*i, Enemy[i].Y, Enemy[i].Graph, TRUE );
	//勇者側のステータス表示
	for(int i=0; i<2; i++){
		if( (Character+i)->HP > 0 ){
			DrawGauge( 15, 16+35*i, (Character+i)->MaxHP, (Character+i)->HP, GetColor( 0, 255, 0 ), GetColor(0, 255/2, 0),TRUE);
			DrawGauge( 15, 31+35*i, (Character+i)->MaxMP, (Character+i)->MP, GetColor( 255, 255, 0 ),GetColor( 255/2, 255/2, 0 ),TRUE );
		}else if( (Character+i)->HP <=0 ) (Character+i)->HP=0;
	}

	if(CheckHitKey(KEY_INPUT_H)==1)return 2;
	return 4;
}