//���̃t�@�C���ł̓}�b�v�Ɋւ���֐��������Ă���܂�
#include "DxLib.h"
#include "../UsePrototype.h"
#include "Map.h"
#include "../Event/Map_Event.h"

//�����Ő��l�̏�����(Ini�ł���������ƍs����������)
Building_t Building[3]={
	{130,130,0,0,0},
	{260, 50,0,0,0},
	{  0,  0,0,0,0}
};

static int BackGroundGraph[3];

static char BackGround[2][WorldY][WorldX]={
	{//�ŏ��̃t�B�[���h
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	},
	{//���̃t�B�[���h(�ꉞ���ꂪ��̒��ɂȂ�ݒ�)
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	}
};



//�����Ŕw�i��ǉ��ł��܂�
void BackGround_Ini(){
	BackGroundGraph[0] = LoadGraph("RPG DATA\\sougen1.png");// �Â��ق��̑���
	BackGroundGraph[1] = LoadGraph("RPG DATA\\sougen2.png");// ���邢�ق��̑���
	BackGroundGraph[2] = LoadGraph("forest.png");// ���邢�ق��̑���

	Building[0].Graph = LoadGraph("RPG DATA\\castle.png"); // ��̓ǂݍ���
	Building[1].Graph = LoadGraph("RPG DATA\\castle.png"); // ��ڂ̎����p�̏�
	Building[2].Graph = LoadGraph("65416.png"); // ��ڂ̎����p�̏�
}

//FieldNumber�͂R�̔z��̍ŏ��ł���
void DrawBackGround( Map_t Map, int FieldNumber ){
	//BackGround�ɂ�����0�ƂȂ��Ă���Ƃ����Graphic[0]��w�i�ɂ���Ƃ������Ƃł�
	if(BackGround[FieldNumber][Map.MapY][Map.MapX]==0)DrawGraph( 0, 0, BackGroundGraph[0], FALSE ) ;
	if(BackGround[FieldNumber][Map.MapX][Map.MapY]==1)DrawGraph( 0, 0, BackGroundGraph[1], FALSE ) ;
	if(BackGround[FieldNumber][Map.MapX][Map.MapY]==2)DrawGraph( 0, 0, BackGroundGraph[2], FALSE ) ;
	
}

// �\����������𖞂����Ă����1���A�����łȂ����0�̒l��Ԃ��B
int DrawBuildingB(int FieldNumber, Map_t Map, Building_t Building, int i=0){
	if((FieldNumber==Building.MapNum)&&(Map.MapX==Building.MapX)&&(Map.MapY==Building.MapY)){
		return 1;
	}else return 0;
}

//�}�b�v�ɏo����_���W������`�悵�����蔻���݂���
void DrawBuilding(Map_Player_t *Player, Map_t Map, int *FieldNumber){
	//������̏���
	if((*FieldNumber==Building[0].MapNum)&&(Map.MapX==Building[0].MapX)&&(Map.MapY==Building[0].MapY)){
		DrawGraph(Building[0].x, Building[0].y, Building[0].Graph, TRUE);
		if(Player_Hantei( *Player, Building[0].x, Building[0].y, Building[0].Graph )==1)*FieldNumber=1;
	}

	//�\�������𖞂����Ă���Ȃ�
	if( *FieldNumber==Building[1].MapNum && Map.MapX==Building[1].MapX && Map.MapY==Building[1].MapY){
		DrawGraph( Building[1].x, Building[1].y, Building[1].Graph, TRUE);
		// ������ƗE�҂��������Ă���Ȃ�
		if(Player_Hantei( *Player, Building[1].x, Building[1].y, Building[1].Graph )==1){
			Player->x = Player->Beforex;
			Player->y = Player->Beforey;
			MapEventChecker();
		}
	}

	for (int i=0; i<10; i++){
		if(DrawBuildingB( *FieldNumber, Map, Building[2],i)==1){
			DrawGraph( (Building[2].x+30*i), Building[2].y, Building[2].Graph, TRUE);
			if(Player_Hantei( *Player, (Building[2].x+30*i), Building[2].y, Building[2].Graph )==1){
				Player->x = Player->Beforex;
				Player->y = Player->Beforey;
			}
		}
	}

}