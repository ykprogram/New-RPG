//このファイルではマップの本体が置いてあります(いわゆるmain関数でMap()と書くと下の処理がされるということです)
#include "DxLib.h"
#include "../UsePrototype.h"
#include "MapMgr.h"


//ゲームを完成品にしたときに消す
void Test(Map_t Map,  Map_Player_t Player ){
	DrawFormatString( 0, 0, GetColor(255, 255, 255), "今のx座標は%d",Player.x) ;
	DrawFormatString( 0, 20, GetColor(255, 255, 255), "今のy座標は%d",Player.y) ;
	DrawFormatString( 0, 40, GetColor(255, 255, 255), "今のMapXは%d",Map.MapX) ;
	DrawFormatString( 0, 60, GetColor(255, 255, 255), "今のMapYは%d",Map.MapY) ;
}

// マップの実体宣言
Map_t Map;
int MapMgr( Mouse_t Mouse,  Map_Player_t *Player, Character_t *Character, Map_t *MapM ){
	DrawBackGround( Map, Map.MapNumber );									//これで背景を描画する。中の数値でマップ構成を切り替える

	if( Menu( Character, Map, &Map.MapNumber ) == 0 ){
		PlayerMove_Map( Mouse, Player );	//もし画面にメニューが表示されていなかったらプレイヤーを動かす(マウスの処理が少し入ってます)
		DrawBuilding( Player, Map, &Map.MapNumber );							//城や建物を描画
	}

	PlayerControl_Map( &Map, Player );								//これで行動を制限する
	MapM->MapX		= Map.MapX;
	MapM->MapY		= Map.MapY;
	MapM->MapNumber	= Map.MapNumber;
	Player->Beforex = Player->x;									// 過去データ更新
	Player->Beforey = Player->y;									// 上に同じ
	DrawFormatString( 0, 60, GetColor(255, 255, 255), "%d%d",Player->Beforex,Player->Beforey) ;
	//FontNumDraw( 300, 200, Map.MapNumber );								//マップナンバーを自作フォントで表示
	//Test( Map, *Player );											//ゲームが完成したらこの関数は消します
	return Encounter( *Player );									//敵に出会うか抽選する,今Main.cppでのPhaseのswitchでマップは1なので1を代入
}