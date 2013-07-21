//このファイルではマップにいるプレイヤーの主な処理を行うファイルです。
#include "DxLib.h"
#include "../UsePrototype.h"
#include "Map_Player.h"

#define PLAYERMAX 30//残像。基本これは触らなくていいと思う

static int a=0;		//足を上げてるときなどのモーションを表すのに使う

static int Encountered=0;

SecondPlayer_t SecondPlayer[ PLAYERMAX ];
void Zanzou( Map_Player_t *Player ){
	//キャラクターを一つづつずらす
	for(int i = PLAYERMAX-1  ; i > 0 ; i -- ){
		if(i==1){
			SecondPlayer[i].x = Player->x ;
			SecondPlayer[i].y = Player->y ;
			SecondPlayer[i].PlayerMotion= Player->PlayerMotion;
		}else{
			SecondPlayer[i].x			 = SecondPlayer[i-1].x ;
			SecondPlayer[i].y			 = SecondPlayer[i-1].y ;
			SecondPlayer[i].PlayerMotion = SecondPlayer[i-1].PlayerMotion;
		}
	}
}

void Map_Player_Ini( Map_Player_t *Player ){
	Player->x=ScreenWidth/2;   
	Player->y=ScreenHeight/2;
	Player->PlayerMotion=0;
	Player->MoveControl=0;
	LoadDivGraph( "RPG DATA\\RPG騎士2.png", 12, 4, 3, 45, 45, Player->Graph ) ;
	GetGraphSize( Player->Graph[ Player->PlayerMotion ], &Player->w, &Player->h ) ;
	// キャラクターの初期位置をセット
	for(int i = 0 ; i < PLAYERMAX ; i ++ ){
		SecondPlayer[i].x = Player->x ;
		SecondPlayer[i].y = Player->y ;
	}
}

//以下四つはプレイヤーの動き。足を上げるという動作がない・・・。
void PlayerUp( Map_Player_t *Player ){
	a++;
	Player->y-=4;
	Player->PlayerMotion=1;
	Player->MoveControl=1;
	Zanzou(Player);
}
void PlayerDown( Map_Player_t *Player ){
	a++;
	Player->y+=4;
	Player->PlayerMotion=0;
	Player->MoveControl=1;
	Zanzou(Player);
}
void PlayerRight( Map_Player_t *Player ){
	a++;
	Player->x+=4;
	Player->PlayerMotion=8+(a/8%4);
	Player->MoveControl=1;
	Zanzou(Player);
}
void PlayerLeft( Map_Player_t *Player ){
	a++;
	Player->x-=4;
	Player->PlayerMotion=4+(a/8%4);
	Player->MoveControl=1;
	Zanzou(Player);
}

//プレイヤーがマップで画面端に来た時の処理 順序　左上右下
void PlayerControl_Map( Map_t *Map, Map_Player_t *Player ){
	if(Player->x<=0){
		if(Map->MapX != 0){
			Player->x=ScreenWidth-46;
			Map->MapX--;
			a=0;
			for(int i = 0 ; i < PLAYERMAX ; i ++ ){
				SecondPlayer[i].x = Player->x ;
				SecondPlayer[i].y = Player->y ;
			}
		}else Player->x=0;
	}
	if(Player->y<=0){
		if(Map->MapY != 0){
			Player->y=ScreenHeight-46;
			Map->MapY--;
			a=0;
			for(int i = 0 ; i < PLAYERMAX ; i ++ ){
				SecondPlayer[i].x = Player->x ;
				SecondPlayer[i].y = Player->y ;
			}
		}else Player->y=0;
	}
	if(Player->x>=ScreenWidth-45){
		if( Map->MapX != 9 ){
			Player->x=1;
			Map->MapX++;
			a=0;
			for(int i = 0 ; i < PLAYERMAX ; i ++ ){
				SecondPlayer[i].x = Player->x ;
				SecondPlayer[i].y = Player->y ;
			}
		}else Player->x=ScreenWidth-45;
	}
	if(Player->y>=ScreenHeight-45){
		if( Map->MapY != 9 ){
			Player->y=1;
			Map->MapY++;
			a=0;
			for(int i = 0 ; i < PLAYERMAX ; i ++ ){
				SecondPlayer[i].x = Player->x ;
				SecondPlayer[i].y = Player->y ;
			}
		}else Player->y=ScreenHeight-45;
	}
}
//マップでのプレイヤーのモーションと描画(マウスでも動ける)
void PlayerMove_Map( Mouse_t Mouse,  Map_Player_t *Player ){

	if( CheckHitKey( KEY_INPUT_UP )==1		&& Player->MoveControl==0 ){
		PlayerUp( Player );
	}
	if( CheckHitKey( KEY_INPUT_DOWN )==1	&& Player->MoveControl==0 ){
		PlayerDown( Player );
	}
	if( CheckHitKey( KEY_INPUT_RIGHT )==1	&& Player->MoveControl==0 ){
		PlayerRight( Player );
	}
	if( CheckHitKey( KEY_INPUT_LEFT )==1	&& Player->MoveControl==0 ){
		PlayerLeft( Player );
	}
	Encountered+=Player->MoveControl;
	//j<3となっている3の部分は後ろにくっついている人数
	for(int i=PLAYERMAX-1,j=0 ; (i>=0)&&(j<3); i-=9, j++ )DrawGraph(SecondPlayer[i].x, SecondPlayer[i].y, Player->Graph[SecondPlayer[i].PlayerMotion], TRUE);
	DrawGraph( Player->x, Player->y, Player->Graph[ Player->PlayerMotion ], TRUE ) ;

	//マウスの左ボタンが押されていたら(マウスの処理を使ってるのでMain関数からMouse_tの実体をもってきた)
	if( GetMouseInput() & MOUSE_INPUT_LEFT ){
		if( (Player->y - Mouse.MouseY > 5) && (Player->y > Mouse.MouseY) &&  Player->MoveControl==0 )PlayerUp( Player );
		if( (Mouse.MouseY - Player->y > 5) && (Player->y < Mouse.MouseY) &&  Player->MoveControl==0 )PlayerDown( Player );
		if( (Mouse.MouseX - Player->x > 5) && (Player->x < Mouse.MouseX) &&  Player->MoveControl==0 )PlayerRight( Player );
		if( (Player->x - Mouse.MouseX > 5) && (Player->x > Mouse.MouseX) &&  Player->MoveControl==0 )PlayerLeft( Player );
	}
}

//敵が出現する確率かどうか（エンカウント）
int Encounter( Map_Player_t Player ){
	//動いている時にだけ敵のエンカウントを行う 確率200
	if( Player.MoveControl!=0 && GetRand(200)==0 && Encountered>=60){
		Set_Before_BattleMovie();
		Encountered=0;
		return 3;
	}
	if(CheckHitKey2(KEY_INPUT_E)==1){Set_Before_BattleMovie();return 3;}
	return 2;
}