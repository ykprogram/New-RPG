#ifndef DEF_MAPPLAYER_H

#define DEF_MAPPLAYER_H

typedef struct{
	int x, y;//プレイヤーの画像のxy
	int w, h;//プレイヤーの横幅と縦幅
	int Graph[ 12 ];//画像を格納するための物
	int Beforex;// 前の座標のx
	int Beforey;// 前の座標のy
	char PlayerMotion;//基本はGraph[12]の中に入れる。
	char MoveControl;//これが0なら動いていない、1なら動いてる
}Map_Player_t;

typedef struct{
	int x;
	int y;
	int PlayerMotion;
}SecondPlayer_t;

	#ifdef MAPPLAYER_PROTOTYPE //この下にある関数を使いたければ左を#defineで宣言しろ

	//ここにあるincludeは構造体を使うためのもの
	#include "../BeforeBattle/Before_Battle.h"
	#include "../Mouse.h"
	#include "../Define.h"
	#include "Map.h"
	void Map_Player_Ini( Map_Player_t *Player );
	void PlayerUp( Map_Player_t *Player );
	void PlayerDown( Map_Player_t *Player );
	void PlayerRight( Map_Player_t *Player );
	void PlayerLeft( Map_Player_t *Player );
	void PlayerControl_Map( Map_t *Map, Map_Player_t *Player );
	void PlayerMove_Map( Mouse_t Mouse, Map_Player_t *Player );
	int Encounter( Map_Player_t Player );

	//戦闘中に操作できるキャラ数なのだが、マップでの追尾も必要となるなめここで定義する
	#define ALL_CONTROLLABLE_PLAYER 2

	#endif		//MAPPLAYER_PROTOTYPE END

#endif//DEF_MAPPLAYER_H END