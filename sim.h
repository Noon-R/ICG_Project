#include "Vector.h"

// sim.cpp
void InitScene( void );
void UpdateScene( void );

// draw.cpp
void DrawScene( void );

//-------- object data
typedef struct {
    Vec3 pos;
	Vec3 rot; //roll,pitch,yaw
	Vec3 scale = {1,1,1};
	Vec4 color; // r,g,b
	int state;
	bool visible;
	int frameCount;

	float turn;
	float move;
	float radius;
} ObjDataT;

//-------- simulation data
typedef struct {
	
	float clip_near;
	float clip_far;
	float air_color[4];
	float sky_color[4];
    //////// ユーザ定義のシーンについてのデータをここにまとめる

	//フィールド情報
	float mapSize = 500;
	Vec3 groundVertex[4] = {
		Vec3{ mapSize / 2, -1, mapSize / 2},
		Vec3{ mapSize / 2, -1, -mapSize / 2},
		Vec3{ -mapSize / 2,-1, -mapSize / 2},
		Vec3{ -mapSize / 2,-1, mapSize / 2}
	};					//地面の頂点座標群


	//Objのデータがかいてあるお

	ObjDataT player;

	int enemy_count = 10;
	ObjDataT enemies[10]; //state 0: 待機　1：行動　2：死亡　3：対消滅（＝GAMEOVER）4: 外部待機 5: 前方に進むぜ
	
	int bullet_count = 10;
	ObjDataT bullets[10];


	//おみくじ
	int fortuneBox_count = 100; 
	ObjDataT fortuneBoxes[100];

	bool isCheckFortune = false;
	char *fortune[3] = { "Super Lucky!!! +999999990 ","Lucky!! +1000","Unlucky -900000"};
	int displayFrame = 3;
	int frameCount = 0;
	int fortuneNum = 0; 

	//敵消去ゾーンね
	ObjDataT trashZone;

	ObjDataT *active_camera;
	

	////////
	//Game データ
	int currentState;//0: ,1:ゲーム ,2:　終了
	int currentScore;
	int clearScore;

	//FPS
	int errapsedFrame;
	float currentFps;




} SimDataT;
