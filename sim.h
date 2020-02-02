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
    //////// ���[�U��`�̃V�[���ɂ��Ẵf�[�^�������ɂ܂Ƃ߂�

	//�t�B�[���h���
	float mapSize = 500;
	Vec3 groundVertex[4] = {
		Vec3{ mapSize / 2, -1, mapSize / 2},
		Vec3{ mapSize / 2, -1, -mapSize / 2},
		Vec3{ -mapSize / 2,-1, -mapSize / 2},
		Vec3{ -mapSize / 2,-1, mapSize / 2}
	};					//�n�ʂ̒��_���W�Q


	//Obj�̃f�[�^�������Ă��邨

	ObjDataT player;

	int enemy_count = 10;
	ObjDataT enemies[10]; //state 0: �ҋ@�@1�F�s���@2�F���S�@3�F�Ώ��Łi��GAMEOVER�j4: �O���ҋ@ 5: �O���ɐi�ނ�
	
	int bullet_count = 10;
	ObjDataT bullets[10];


	//���݂���
	int fortuneBox_count = 100; 
	ObjDataT fortuneBoxes[100];

	bool isCheckFortune = false;
	char *fortune[3] = { "Super Lucky!!! +999999990 ","Lucky!! +1000","Unlucky -900000"};
	int displayFrame = 3;
	int frameCount = 0;
	int fortuneNum = 0; 

	//�G�����]�[����
	ObjDataT trashZone;

	ObjDataT *active_camera;
	

	////////
	//Game �f�[�^
	int currentState;//0: ,1:�Q�[�� ,2:�@�I��
	int currentScore;
	int clearScore;

	//FPS
	int errapsedFrame;
	float currentFps;




} SimDataT;
