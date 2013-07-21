#include "DxLib.h"
#include "../UsePrototype.h"
#include "Battle.h"


int Damage=0;
int BackGround;
MenuElement_t BattleMenu[4]={
	{30, 380, 30, 30, GetColor(255,255,255), 255, 255, 255, "��������"},
	{30, 430, 30, 30, GetColor(255,255,255), 255/2, 255/2, 255/2, "�A�C�e��"},

	{120, 380, 120, 120, GetColor(255,255,255), 255/2, 255/2, 255/2, "�ɂ���"},
	{120, 430, 120, 120, GetColor(255,255,255), 255/2, 255/2, 255/2, "��������"}
};

StringScript_t BattleMenuString[10]={
	// �o��
	{ 230,380,GetColor(255,255,255), "%s�����ꂽ!",2},
	{ 230,400,GetColor(255,255,255), "�E�҂͉�������?" },

	// ������
	{ 230,380,GetColor(255,255,255), "�E�҂͓����o�����I" },

	// �U��
	{ 230,380,GetColor(255,255,255), "�E�҂̍U���I"},
	{ 230,400,GetColor(255,255,255), "%d�_���[�W�I",1 },

	// �G�̍U��
	{ 230,380,GetColor(255,255,255), "%s�̍U���I",2},
	{ 230,400,GetColor(255,255,255), "%d�_���[�W�I",1},

	//����
	{ 230,380,GetColor(255,255,255), "�����ɏ��������I" },
	{ 230,400,GetColor(255,255,255), "�o���l%d����ɓ��ꂽ",1},
};

//�G�̏�����
Character_t Enemy[2]={
	// HP,  MP, Lv,  ��,  ��,  ��,  ���x, ���x2, �o��, �摜,  MHP,  MMP,               ���O,   X,   Y, �p�X
	{  10,  10,  1,  15,  10,  10,     5,     0,    1,    0,   10,   10,           "�[���[", 280, 200, "RPG DATA\\�[���[.png" },
	{ 100, 100, 10, 150, 100, 100,    10,     0,  100,    0,  100,  100, "�A�[�}�[�h�[���[", 280,  80, "RPG DATA\\�[���[ type2.png"  }
};

void Battle_Ini(){
	Enemy[0].Graph = LoadGraph( Enemy[0].Pass );
	Enemy[1].Graph = LoadGraph( Enemy[1].Pass );
	//BackGround= LoadGraph("RPG DATA\\BackSougen.png");
}




static int NowNumber=0;
// ��b�Ȃǂ�\������,UseBeforeZ��1�̏ꍇ
static int DrawBattleMessage(int Start, int End, StringScript_t MenuString[], int Damage, int EnemyName, int UseBeforeZ){
	if(End<NowNumber+Start+UseBeforeZ){ NowNumber=0;return 1; }
	for( int i=Start; i<(NowNumber+Start+UseBeforeZ); i++){
		if( i==5 || i==0)DrawFormatString(MenuString[i].x,MenuString[i].y,MenuString[i].color,MenuString[i].hyoji,Enemy[EnemyName].Name);
		else DrawFormatString(MenuString[i].x,MenuString[i].y,MenuString[i].color,MenuString[i].hyoji,Damage);
		DrawFormatString(0,200+(i*20),GetRainbowColor(),"%d",i);
	}
	DrawFormatString(40,200,GetRainbowColor(),"%d",NowNumber);
	if(CheckHitKey2(KEY_INPUT_Z)==1)NowNumber++;
	return 0;
}

static int counter=0;		//���o�C�g���\�����邩
static int counter2=0;		//
//static char NowNumber=0;	//�O�s�̂����ǂ��܂ł�\�����Ă��邩
static char test[3][100]={{""},{""},{""}};		//�O�s�̓����̘g������ƍl����Ɨǂ�
// ��b�Ȃǂ�\������,���͎O�s�܂Ł@�����͑S�p���D�܂���
//(���p�A�S�p�̏��ŕ���ł��Ĕ��p�̐�����̏ꍇ�S�p���\��������Ƃ���u�_�ɂȂ邱�Ƃ�����̂�)
bool serch(char str, char str2)
{
	for(;str != '\0';){
		if(str == str2)return true; /*c�Ɠ���������������+1*/
		str++; /*���̕������r*/
	}
	return false;
}

int DrawBattleMessageString(int Start, int End, StringScript_t MenuString[],int EnemyName=0,int Number=0){
	
	//����Start��NowNumber�̍��v�l��End���傫��������,�I������������B
	if(End<NowNumber+Start){
		counter=0;
		NowNumber=0;
		//test�����S�Ƀ[��(������)����
		for(int i=0;i<3;i++)for(int j=0;j<100;j++)test[i][j]='\0';
		return 100; 
	}
	//����Z�L�[������,�Ō�܂ŕ\������Ă�����(�\�����Ă���Œ��łȂ����)
	if( CheckHitKey2(KEY_INPUT_Z)==1 && MenuString[NowNumber+Start].hyoji[counter]=='\0'){
		counter=0;
		NowNumber++;
	}
	if(counter<100-2&&MenuString[NowNumber+Start].hyoji[counter]!='\0'&&counter2%3==0){
		/*if(CheckHitKey2(KEY_INPUT_G)==1)*/{
			//if(counter==0)counter=2;
			counter+=2;
		}
		strncpy(test[NowNumber+Start], MenuString[NowNumber+Start].hyoji, counter);
		test[NowNumber][counter]='\0';
	}
	// �����\��for���͍��܂ŕ\����������\�������܂܂ɂ��邽��
	for( int i=Start; i<=(NowNumber+Start); i++){
		if(MenuString[i].Percentd_and_Percents==2)DrawFormatString( MenuString[i].x, MenuString[i].y, MenuString[i].color, test[i], Enemy[EnemyName].Name);
		else if(MenuString[i].Percentd_and_Percents==1)DrawFormatString( MenuString[i].x, MenuString[i].y, MenuString[i].color, test[i], Number);
		/*DrawFormatString( MenuString[i].x, MenuString[i].y, MenuString[i].color, MenuString[i].hyoji, Number);*/
		else DrawFormatString( MenuString[i].x, MenuString[i].y, MenuString[i].color, test[i]);
		DrawFormatString(0,200+(i*20),GetColor(255,255,255),"%d",i);
	}
	counter2++;
	DrawFormatString(40,200,GetColor(255,255,255),"%d",NowNumber);
	DrawFormatString(40,220,GetColor(255,255,255),"%d",counter);
	return NowNumber;
}



// �͂��߂�x,y,�Q�[�W�̃t���[���g, ���g, �F, ���ׂ̗ɒ��g�̐�������`�悷�邩���Ȃ���
void DrawGauge(int x, int y, int GaugeFrame, int GaugeIn, int ColorFrame, int ColorIn, int Flag){
	DrawBox( x, y, x+GaugeFrame, y+15, ColorFrame, FALSE );
	DrawBox( x+1, y+1, x+1+GaugeIn-2, y-1+15,ColorIn, TRUE );
	if(Flag==TRUE)FontNumDraw( x+GaugeFrame, y, GaugeIn );
}

int move=0;
int backmenu=0;
int Battle( Character_t *Character, int EnemyType){	
	DrawGraph(0,0,BackGround,TRUE);
	MessageFrame();
	DrawFormatString( 60, 140, GetColor(255, 255, 255), " LV:%d ",Character->LEVEL) ;

	DrawGauge( 15, 16, Character->MaxHP, Character->HP, GetColor( 0, 255, 0 ), GetColor(0, 255/2, 0),TRUE);
	DrawGauge( 15, 31, Character->MaxMP, Character->MP, GetColor( 255, 255, 0 ),GetColor( 255/2, 255/2, 0 ),TRUE );

	if(move!=6)DrawGraph(Enemy[EnemyType].X, Enemy[EnemyType].Y, Enemy[EnemyType].Graph, TRUE);
	// ���ꂽ�Ƃ�
	if(move==0){if(DrawBattleMessageString( 0, 1, BattleMenuString, EnemyType) == 100 )move=1;}


	// �I��
	if(move==1)switch( DrawMenu( 2, 2, KEY_INPUT_Z, BattleMenu) ){
		// ���x����
	case 0:backmenu=0;if( Character->Speed >= Enemy[EnemyType].Speed ){
		Damage=DamageCalc2( *Character, &Enemy[EnemyType]);move=3;
		   }else {
			   Damage=DamageCalc2( Enemy[EnemyType], Character);move=5;
		   }break;
	case 1:break;
	case 2:move=2;break;
	case 3:break;
	}

	//�����o���E�҂̏���
	if(move==2)if( DrawBattleMessageString( 2, 2, BattleMenuString ) == 100 ){move=0;Enemy[EnemyType].HP = Enemy[EnemyType].MaxHP ;return 2;}
	


	// �I�Ƀ_���[�W��^���鏈���@���������̒��ɂ͏��������̏���
	if(move==3)if(DamageCalc3( Character, &Enemy[EnemyType], 3, 4, 5, EnemyType, FALSE)==1){
		Character->Ex += Enemy[EnemyType].Ex ;	
		move=6;
	}	


	// �G�̃_���[�W��^���镪��\���@���������̒��ɂ͕��������̏���
	if(move==5)if(DamageCalc3( &Enemy[EnemyType], Character, 5, 6, 3, EnemyType, TRUE)==1){
		move=0 ;
		return 0 ;
	}
	//�o���l
	if(move==6)if( DrawBattleMessageString( 7, 8, BattleMenuString, EnemyType, Enemy[EnemyType].Ex ) == 100){
		Enemy->HP = Enemy[EnemyType].MaxHP ; 
		move=0 ; 
		return 2 ;
	}

	return 4 ;
}/*
 ( ( �U�����̃��x��*2 /5 +2) *�Z�̈З� *�U�����̔\�͒l/�h�䑤�̔\�͒l/50+2)*GetRand(85�`100)/100
 ( ( �U�����̃��x�� *2 /5 +2) *�U�����̍U���� /�h�䑤�̖h��� /50 +2 )*GetRand(85�`100)/100
 */

int DamageCalc( Character_t Attacker, Character_t Defender ){
	// �ʏ�U���̌v�Z���̓�����Ԃ�
	return (int)( Attacker.LEVEL *2 *Attacker.Power /Defender.Defense +2 )*( 85+ GetRand(15) )/100;
}

int DamageCalc2( Character_t Attacker, Character_t *Defender ){
	// �\�����邽�߂ɂ���������
	int Damage2= DamageCalc( Attacker, *Defender ) ;
	// �G��HP����_���[�W������
	Defender->HP -= Damage2;
	if(Defender->HP < 0 )Defender->HP=0;
	return Damage2;
}

// �U�����̃X�e�[�^�X�@�h�䑤�̃X�e�[�^�X�@���͂̎n�܂�@���͂̏I���@���ɍs��move�̐��l�@�G�̔ԍ��@�O��Z�L�[���g�����������������ۂ�
int DamageCalc3( Character_t *Attacker, Character_t *Defender, int StartLog, int EndLog, int Go, int EnemyType, int Flag){
	// �h�䑤�ɗ^����_���[�W�v�Z
	if( DrawBattleMessageString( StartLog, EndLog, BattleMenuString, EnemyType, Damage) == 100 ){
		// HP��0�ȉ��̏ꍇ�@�ˏ���
		if( Defender->HP <= 0 )return 1 ;
		// �h�䑤�̃_���[�W�v�Z
		Damage=DamageCalc2( *Defender, Attacker );
		// ���̍s����
		move=Go;
		// �������ڂ̍s���ł������ꍇ�͂����Ń��j���[�ɖ߂�
		if(backmenu==1)move=1 ;
		backmenu=1;
	}
	return 0;
}