#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl/glut.h>

#include "common.h"

#include "sim.h"
#include "calc.h"

#define PI 3.14159265

SimDataT simdata;
extern int time;

void SetObjData(ObjDataT *data, Vec3 pos, Vec3 rot, Vec4 col, int state, bool visible,float radius);
void ChangeColor(ObjDataT *data, Vec4 col);
void BulletsUpdate();
void EnemiesUpdate();
void TrashAreaUpdate();

void CalcFPS() {
	simdata.currentFps = simdata.errapsedFrame / ( glutGet(GLUT_ELAPSED_TIME) / 1000.0);
}

void CheckScore() {
	if (simdata.currentScore > simdata.clearScore)
	{
		simdata.currentScore = 999999999;	
		simdata.currentState = 2;
	}
}

void AddScore(int score) {

	simdata.currentScore += score;
	CheckScore();
}

void SetScore(int score) {

	simdata.currentScore = score;
	CheckScore();
}

/*---------------------------------------------------------------- InitScene
 * InitScene:
 *--------*/
void InitScene(void)
{
	simdata.errapsedFrame++;
	CalcFPS();

	////// ÉVÅ[ÉìÉfÅ[É^ÇÃèâä˙âª
	simdata.clip_far = 1000.0;
	simdata.clip_near = 0.1;
	simdata.air_color[0] = 1.0;
	simdata.air_color[1] = 1.0;
	simdata.air_color[2] = 1.0;
	simdata.air_color[3] = 0.5; // fog density factor
	simdata.sky_color[0] = 0.2;
	simdata.sky_color[1] = 0.3;
	simdata.sky_color[2] = 0.4;
	simdata.sky_color[3] = 0.5; // sky color factor
	//////

	SetObjData(&simdata.player,
		Vec3{0,0,0},
		Vec3{0.0,0.0,0.0},
		Vec4{0,0,0,0},
		0,
		true,
		1
		);


	for (int i = 0; i < simdata.enemy_count; i++)
	{
		Vec3 pos = Vec3{
			uniformRandom(-250,250),
			0,
			uniformRandom(-250,250)
		};
		SetObjData(&simdata.enemies[i],
			pos,
			Vec3{ 0.0,0.0,0.0 },
			Vec4{ 0.0,0.0,1.0, 1.0},
			0,
			true,
			2
		);
	}

	for (int i = 0; i < simdata.fortuneBox_count; i++)
	{
		Vec3 pos = Vec3{
			uniformRandom(-250,250),
			0,
			uniformRandom(-250,250)
		};
		SetObjData(&simdata.fortuneBoxes[i],
			pos,
			Vec3{ 0.0,0.0,0.0 },
			Vec4{ 0.0,1.0,1.0, 1.0 },
			0,
			true,
			2
		);
	}

	simdata.active_camera = &simdata.player;

	for (int i = 0; i < simdata.bullet_count; i++) {
		SetObjData(&simdata.bullets[i],
			Vec3{ 100,100,100 },
			Vec3{ 0.0,0.0,0.0 },
			Vec4{ 0.0,1.0,1.0, 1.0 },
			0,
			true,
			1
		);

		
	}

	//
	SetObjData(&simdata.trashZone,
			Vec3{0,0,0},
			Vec3{0.0,0.0,0.0},
			Vec4{0.0,1.0,1.0, 1.0 },
			0,
			true,
			6
		);
	simdata.trashZone.scale = Vec3{ 
		simdata.trashZone.radius*2,
		simdata.trashZone.radius*2,
		simdata.trashZone.radius*2
	};

	//GameDataInit
	simdata.currentScore = 0;
	simdata.clearScore = 999999999;
	simdata.currentState = 1;

    return;
}


void UpdateGame() {
	//////// ÉfÅ[É^çXêV ////////
	simdata.errapsedFrame++;
	CalcFPS();
	printf("%f\n", glutGet(GLUT_ELAPSED_TIME)/1000.0);
	printf("%d\n",simdata.errapsedFrame);
	AddScore(1);

	MoveObject(&simdata.player);

	////////

	EnemiesUpdate();
	BulletsUpdate();
	TrashAreaUpdate();
}


/*-------------------------------------------------------------- UpdateScene
 * UpdateScene:
 *--------*/
void UpdateScene( void )
{

	switch (simdata.currentState)
	{
		case 0:
			InitScene();
			simdata.currentState = 1;
			break;
		case 1:
			UpdateGame();
			break;
		case 2:
			//GameClear
			break;
		case 3:
			//GameOver;
			break;
		default:
			break;
	}
	


    return;
}


void SetObjData(ObjDataT *data, Vec3 pos, Vec3 rot, Vec4 col, int state, bool visible,float radius) {
	data->pos = pos;

	data->rot = rot;

	data->color = col;

	data->state = state;
	data->visible = visible;

	data->turn = 0;
	data->move = 0;

	data->radius = radius;
}

void BulletsUpdate() {

	for (int i = 0; i < simdata.bullet_count; i++) {
		if (!simdata.bullets[i].visible)continue;

		switch (simdata.bullets[i].state) {

		case 0:
			break;
		case 1:
			simdata.bullets[i].move = -100.0 / simdata.currentFps;
			MoveObject(&simdata.bullets[i]);

			for (int j = 0; j < simdata.enemy_count; j++)
			{

			//ã Ç∆ìGÇÃìñÇΩÇËîªíËÇ∆ìñÇΩÇ¡ÇΩéûÇÃèàóùÇÊÅ`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`ÅIÅIÅIÅIÅIÅI
				if (HitTest(&simdata.bullets[i], &simdata.enemies[j])) {
					if (simdata.enemies[j].state == 1) {
						simdata.enemies[j].rot.y = 90;
						simdata.bullets[i].state = 2;
						AddScore(500);
						simdata.enemies[j].state = 2;
						simdata.enemies[j].frameCount = 0;
					}

				}

			}

			if (DistanceAtoB(&simdata.bullets[i], &simdata.player) > 50) {
				simdata.bullets[i].state = 2;
			}
			break;

		case 2:
			simdata.bullets[i].pos.x = 1000;
			simdata.bullets[i].state = 0;
			break;
		}

	}
}


void EnemiesUpdate() {
	for (int i = 0; i < simdata.enemy_count; i++) {

		//state 0: ë“ã@Å@1ÅFçsìÆÅ@2ÅFéÄñSÅ@3ÅFëŒè¡ñ≈ÅiÅÅGAMEOVERÅj4: äOïîë“ã@
		float dist;
		euler_t angle ;
		float k_move = 7.5/simdata.currentFps; //ë¨ìxÉpÉâÉÅÅ[É^ÅiÅ{ÇÕí«ê’ÅAÅ|ÇÕì¶îÅ`å„ÇÎå¸Ç´ÇÃå„Ç∏Ç≥ÇËÅ¶Åj

		dist = EulerAtoB(&simdata.enemies[i], &simdata.player, &angle);

		switch (simdata.enemies[i].state)
		{
			case 0:
				simdata.enemies[i].visible = false;
				simdata.enemies[i].state = 1;
				break;

			case 1:
				simdata.enemies[i].visible = true;

				simdata.enemies[i].move = k_move;
				simdata.enemies[i].turn = 0.0;
				simdata.enemies[i].rot.z = angle.yaw; //playerÇ÷ÇÃï˚å¸Çê›íËÅ¶
				MoveObject(&simdata.enemies[i]);
				
				if (HitTest(&simdata.enemies[i], &simdata.player)) {
					simdata.currentState = 3;
				}

				break;

			case 2:
				simdata.enemies[i].frameCount++;
				simdata.enemies[i].visible = true;

				simdata.enemies[i].move = 0;

				if (simdata.enemies[i].frameCount >= 5*simdata.currentFps) {
					simdata.enemies[i].state = 3;
					simdata.enemies[i].frameCount = 0;
				}

				break;

			case 3:
				simdata.enemies[i].visible = false;
				simdata.enemies[i].pos = Vec3{ 100,100,100 };
				simdata.currentState = 3;
				break;

			case 4:
				simdata.enemies[i].visible = false;
				break;
			case 5:
				
				MoveObject(&simdata.enemies[i]);
				break;

			default:
				break;
		}



	}
}

void TrashAreaUpdate() {

	for (int i = 0; i < simdata.enemy_count; i++) {
		if (simdata.enemies[i].state != 5)continue;

		if (HitTest(&simdata.trashZone,&simdata.enemies[i])) {

			simdata.enemies[i].pos = Vec3{100,100,100};
			simdata.enemies[i].state = 0;
			AddScore(10000);

		}

	}

}