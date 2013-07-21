#include "DxLib.h"
#include "../UsePrototype.h"
#include "EventMgr.h"
static int MainEvent=0;
static int LittleEvent=0;

//イベントファイルはちゃんと使えるようになっています
void function(){
	DrawFormatString( 320, 50, GetColor(250,250,250), "ちゃんと使える状態になっています。");
}