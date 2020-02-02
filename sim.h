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


	ObjDataT *active_camera;

} SimDataT;
