//このファイルではマップに関する関数が書いてあります
#include "DxLib.h"
#include "../UsePrototype.h"
#include "Map.h"
#include "../Event/Map_Event.h"

//ここで数値の初期化(Iniでこれを書くと行数がかさむ)
Building_t Building[3]={
	{130,130,0,0,0},
	{260, 50,0,0,0},
	{  0,  0,0,0,0}
};

static int BackGroundGraph[3];

static char BackGround[2][WorldY][WorldX]={
	{//最初のフィールド
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
	{//第二のフィールド(一応これが城の中になる設定)
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



//ここで背景を追加できます
void BackGround_Ini(){
	BackGroundGraph[0] = LoadGraph("RPG DATA\\sougen1.png");// 暗いほうの草原
	BackGroundGraph[1] = LoadGraph("RPG DATA\\sougen2.png");// 明るいほうの草原
	BackGroundGraph[2] = LoadGraph("forest.png");// 明るいほうの草原

	Building[0].Graph = LoadGraph("RPG DATA\\castle.png"); // 城の読み込み
	Building[1].Graph = LoadGraph("RPG DATA\\castle.png"); // 二つ目の実験用の城
	Building[2].Graph = LoadGraph("65416.png"); // 二つ目の実験用の城
}

//FieldNumberは３つの配列の最初である
void DrawBackGround( Map_t Map, int FieldNumber ){
	//BackGroundにおいて0となっているところはGraphic[0]を背景にしろということです
	if(BackGround[FieldNumber][Map.MapY][Map.MapX]==0)DrawGraph( 0, 0, BackGroundGraph[0], FALSE ) ;
	if(BackGround[FieldNumber][Map.MapX][Map.MapY]==1)DrawGraph( 0, 0, BackGroundGraph[1], FALSE ) ;
	if(BackGround[FieldNumber][Map.MapX][Map.MapY]==2)DrawGraph( 0, 0, BackGroundGraph[2], FALSE ) ;
	
}

// 表示する条件を満たしていれば1を、そうでなければ0の値を返す。
int DrawBuildingB(int FieldNumber, Map_t Map, Building_t Building, int i=0){
	if((FieldNumber==Building.MapNum)&&(Map.MapX==Building.MapX)&&(Map.MapY==Building.MapY)){
		return 1;
	}else return 0;
}

//マップに出る城やダンジョンを描画し当たり判定を設ける
void DrawBuilding(Map_Player_t *Player, Map_t Map, int *FieldNumber){
	//入れる城の処理
	if((*FieldNumber==Building[0].MapNum)&&(Map.MapX==Building[0].MapX)&&(Map.MapY==Building[0].MapY)){
		DrawGraph(Building[0].x, Building[0].y, Building[0].Graph, TRUE);
		if(Player_Hantei( *Player, Building[0].x, Building[0].y, Building[0].Graph )==1)*FieldNumber=1;
	}

	//表示条件を満たしているなら
	if( *FieldNumber==Building[1].MapNum && Map.MapX==Building[1].MapX && Map.MapY==Building[1].MapY){
		DrawGraph( Building[1].x, Building[1].y, Building[1].Graph, TRUE);
		// もし城と勇者が当たっているなら
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