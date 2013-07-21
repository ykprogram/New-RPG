#ifndef DEF_MAP_H

#define DEF_MAP_H 

#define WorldX 10
#define WorldY 10

//�}�b�v�̍\����
typedef struct{
	int MapX;
	int MapY;
	int MapNumber;//�ǂ̃}�b�v��`�悷�邩��I���ł���
				//MapNumber=1;�����̂悤�ɂ��ă}�b�v��؂�ւ���
}Map_t;

typedef struct{
	int x;		// X���W
	int y;		// Y���W
	int Graph;	// �摜
	int MapX,MapY,MapNum;	// �}�b�v�̍��W���i�[����ϐ�
}Building_t;

	#ifdef MAP_PROTOTYPE //���̉��ɂ���֐����g��������΍���#define�Ő錾����

	#include "../Function.h"
	#include "Map_Player.h"
	void BackGround_Ini();
	void DrawBackGround( Map_t Map, int FieldNumber );
	void DrawBuilding(Map_Player_t *, Map_t Map, int* );

	#endif //MAP_PROTOTYPE END

#endif //EDF_MAP_H END