//���̃t�@�C���ł̓}�b�v�̖{�̂��u���Ă���܂�(������main�֐���Map()�Ə����Ɖ��̏����������Ƃ������Ƃł�)
#include "DxLib.h"
#include "../UsePrototype.h"
#include "MapMgr.h"


//�Q�[���������i�ɂ����Ƃ��ɏ���
void Test(Map_t Map,  Map_Player_t Player ){
	DrawFormatString( 0, 0, GetColor(255, 255, 255), "����x���W��%d",Player.x) ;
	DrawFormatString( 0, 20, GetColor(255, 255, 255), "����y���W��%d",Player.y) ;
	DrawFormatString( 0, 40, GetColor(255, 255, 255), "����MapX��%d",Map.MapX) ;
	DrawFormatString( 0, 60, GetColor(255, 255, 255), "����MapY��%d",Map.MapY) ;
}

// �}�b�v�̎��̐錾
Map_t Map;
int MapMgr( Mouse_t Mouse,  Map_Player_t *Player, Character_t *Character, Map_t *MapM ){
	DrawBackGround( Map, Map.MapNumber );									//����Ŕw�i��`�悷��B���̐��l�Ń}�b�v�\����؂�ւ���

	if( Menu( Character, Map, &Map.MapNumber ) == 0 ){
		PlayerMove_Map( Mouse, Player );	//������ʂɃ��j���[���\������Ă��Ȃ�������v���C���[�𓮂���(�}�E�X�̏��������������Ă܂�)
		DrawBuilding( Player, Map, &Map.MapNumber );							//��⌚����`��
	}

	PlayerControl_Map( &Map, Player );								//����ōs���𐧌�����
	MapM->MapX		= Map.MapX;
	MapM->MapY		= Map.MapY;
	MapM->MapNumber	= Map.MapNumber;
	Player->Beforex = Player->x;									// �ߋ��f�[�^�X�V
	Player->Beforey = Player->y;									// ��ɓ���
	DrawFormatString( 0, 60, GetColor(255, 255, 255), "%d%d",Player->Beforex,Player->Beforey) ;
	//FontNumDraw( 300, 200, Map.MapNumber );								//�}�b�v�i���o�[������t�H���g�ŕ\��
	//Test( Map, *Player );											//�Q�[�������������炱�̊֐��͏����܂�
	return Encounter( *Player );									//�G�ɏo������I����,��Main.cpp�ł�Phase��switch�Ń}�b�v��1�Ȃ̂�1����
}