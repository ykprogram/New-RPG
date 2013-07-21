#include "DxLib.h"
#include "../UsePrototype.h"
#include "Start Menu.h"
#include "../KeyBoard.h"
int syori;
// メニュー項目要素を5つ作る
MenuElement_t MenuElement[5]={
	// タグの中身の順番で格納される。xに80が、yに100が、nameに"ゲームスタート"が入る
	{  80, 100, 100, 80, GetColor(255,255,255), 255, 255, 255,"ゲームスタート" }, 
	{ 100, 150, 100, 80, GetColor(255,255,255), 255/2, 255/2, 255/2,"おまけ" },
	{ 100, 200, 100, 80, GetColor(255,255,255), 255/2, 255/2, 255/2,"ヘルプ" },
	{ 100, 250, 100, 80, GetColor(255,255,255), 255/2, 255/2, 255/2,"コンフィグ" },
	{ 100, 300, 100, 80, GetColor(255,255,255), 255/2, 255/2, 255/2,"ゲーム終了" },
};

int help(){
	DrawFormatString(320,0,GetColor(255,255,255),"決定:Zキー");
	DrawFormatString(320,20,GetColor(255,255,255),"拒否:Xキー");
	DrawFormatString(320,40,GetColor(255,255,255),"マップにて");
	DrawFormatString(320,60,GetColor(255,255,255),"勇者の移動:十字キー(↓→↑←)");
	DrawFormatString(320,80,GetColor(255,255,255),"メニューの表示:Cキー");
	DrawFormatString(320,100,GetColor(255,255,255),"Xキーでメニューに戻ります。");
	if(CheckHitKey(KEY_INPUT_X)==1)return 0;
	return 1;
} 
//int MenuBackGround;
void Start_BackGraph(){
	//メニュー画面の画像をロード
	//MenuBackGround= LoadGraph("RPG DATA\\google.png");
}

int StartMenu(){
	//DrawGraph(240,40,MenuBackGround,TRUE);
	DrawFormatString( 320, 240, GetColor( 255, 255, 255 ), "ver4.00");
	if(syori==1)syori=help();
		else {
			for(int i=0;i<5; i++)DrawBox( MenuElement[i].x, MenuElement[i].y, MenuElement[i].x+18, MenuElement[i].y+18, GetColor( 255, 0, 0 ), FALSE) ;
			switch( DrawMenu( 5, 1, KEY_INPUT_Z, MenuElement ) ){
		case 0:return 2;	// ゲームスタート
		case 2:syori=help();break;
		case 4:return 5; // ゲーム終了
		}
	}
	return 1;
}