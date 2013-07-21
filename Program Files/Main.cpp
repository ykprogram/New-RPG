//��������ǂݎn�߂܂��B
//switch�̒��ɂ���֐���mgr�̂ق��ɓ����Ă܂��B
//�K���֐����g���Ƃ���UsePrototype.h���C���N���[�h���邱�ƂɂȂ��Ă܂�
#include "DxLib.h"
#include "UsePrototype.h"
#include "Define.h"
#include "Mouse.h"
#include "Function.h"
#include "Start Menu\Start Menu.h"
#include "Map\MapMgr.h"
#include "Map\Map_Player.h"
#include "Battle Phase\Battle.h"
#include "BeforeBattle\Before_Battle.h"
#include "Story\StoryMgr.h"
#include "Music\Music.h"
#include "Map\MapMenu.h"
#include "KeyBoard.h"
#include "Battle Phase\Battle_Player.h"
#include "Battle Phase\BattleMgr.h"
#include "Event\EventMgr.h"

#define MaxPlayerCharacter 2

static char Phase=0;//����Ń��C��switch�𐧌䂷��

EnemySelect_t EnemySelect;//�G�l�̂܂ŁI

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow )
{
	Mouse_t Mouse;									// �}�E�X�̎��̐錾
	Map_Player_t Player;							// �}�b�v�ł̃v���C���[�̎��̐錾(1�l��)
	Character_t Character[MaxPlayerCharacter];		// �L�����N�^�[�̃X�e�[�^�X�̎��Ԑ錾
	Map_t MapA;										// ���̂Ƃ���̎���

	SetGraphMode( ScreenWidth, ScreenHeight, 32 ) ;
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); // �E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	SetMouseDispFlag(TRUE) ;	// �}�E�X��\����Ԃɂ��� 
	DrawFormatString( 0, 0, GetColor(255, 255, 255), "Now Loading...") ;
	Before_Battle_Ini();		// �퓬�ɓ���O�̃��[�r�[�̏�����
	Function_Ini();				// Function�̏�����������(�摜)
	Mouse_Ini( &Mouse );		// �}�E�X�̏�����������(�摜)
	Menu_Ini();					// ���j���[�̏�����(�摜)
	BackGround_Ini();			// �w�i�̏�����������(�摜)
	Map_Player_Ini( &Player );	// �v���C���[�̏�����������(�摜)
	//Start_BackGraph();		// �X�^�[�g��ʂ̔w�i��`�悷��
	Battle_Ini��();				// �G�̉摜�����[�h
	Battle_Player_Ini( Character );// �\�͂̏�����
	Music_Ini();				// ���y�̏�����
	TestStoryIni();				// ���܂�������̏�����
	
	
	// while( ����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A, �G�X�P�[�v��������E�o, Phase��1000������ƒE�o)
	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && CheckHitKey( KEY_INPUT_ESCAPE )==0){
		AllKey();									// �����CheckHitKey2���g����悤�ɂȂ��	
		switch(Phase){
		case 0:Phase=StoryMgr();break;				// ���j���[�Ȃ񂾂���Phase�ɑ�����Ă�͕̂Ԃ�l
		case 1:Phase=StartMenu();break;				// �}�b�v���̈ړ������邱�ꂪ0���Ǝ~�܂��Ă��Ă���ȊO���Ɠ����Ă���
		case 2:Phase=MapMgr( Mouse, &Player, Character, &MapA);Player.MoveControl=0;break;//�}�b�v�����Player���|�C���^�[�ɂ��Ȃ��Ɠ����Ă���Ȃ���
		case 3:Phase=BeforeBattleMgr( &EnemySelect, MapA );break;
		case 4:Phase=BattleMgr( Character, EnemySelect );break;//��������BattleMgr�ɂ���ɂ�Battle�̂��Ƃ�Mgr��t����Ηǂ�
		}
		if(Phase==5)return 0;
		Mouse_Draw( &Mouse );// �����Ń}�E�X�̃|�C���^�[���擾���`�悷��
	}
	DxLib_End(); // DX���C�u�����I������
	return 0;
} 

		
	//int Music;
	//char handle[100];if(GetDragFilePath( handle )==0)Music = LoadSoundMem( handle );
	//if(CheckHitKey(KEY_INPUT_M))PlaySoundMem( Music, DX_PLAYTYPE_BACK ) ;
	//SetDragFileValidFlag(TRUE);	// D&D���邽�߂̂���