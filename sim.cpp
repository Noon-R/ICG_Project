#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "common.h"

#include "sim.h"
#include "calc.h"

#define PI 3.14159265

SimDataT simdata;
extern int time;


/*---------------------------------------------------------------- InitScene
 * InitScene:
 *--------*/
void InitScene(void)
{
	
	////// シーンデータの初期化
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


    return;
}


void UpdateGame() {
	
}


/*-------------------------------------------------------------- UpdateScene
 * UpdateScene:
 *--------*/
void UpdateScene( void )
{

    return;
}


