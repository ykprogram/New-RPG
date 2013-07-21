#include "DxLib.h"
#include "../UsePrototype.h"
#include "Map_Event.h"

static int Map_Event=0;//0はゲームスタート時

int MapEventChecker(){
	DrawFormatString(300,200,GetColor(255,255,255),"入ることはできません!!");
	return 0;
}