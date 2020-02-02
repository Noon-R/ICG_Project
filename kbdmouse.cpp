/******************************************************************************
 * keybdmouse.cpp: keyboard and mouse callback functions 
 */
#include <stdlib.h>
#include <stdio.h>

#include "platform.h"

#include "common.h"

#include "sim.h"
#include "Vector.h"
#include "calc.h"

extern SimDataT simdata;
extern WindowDataT window;

//-------- modifier key status
bool isShiftKeyDown( void );
bool isCtrlKeyDown( void );
bool isAltKeyDown( void );

/*-------------------------------------------------- modifier key status
 * Shift, Ctrl, Alt key status
 */
bool isShiftKeyDown( void )
{ return (bool)(glutGetModifiers() & GLUT_ACTIVE_SHIFT); }
bool isCtrlKeyDown( void )
{ return (bool)(glutGetModifiers() & GLUT_ACTIVE_CTRL); }
bool isAltKeyDown( void )
{ return (bool)(glutGetModifiers() & GLUT_ACTIVE_ALT); }

/*------------------------------------------------------------- charKeyDown/Up
 * charKeyDown/Up - GLUT keyboard callback function
 * key: ASCII code
 * x, y: mouse position
 *--------*/
void charKeyDown( unsigned char key, int x, int y )
{
    switch( key ){
      case 'h': // help
        printf( "Instruction\n" );
        printf( "[H]:Help\n" );
        printf( "[Q]:Quit\n" );
        break;
      case 'q': // quit
        exit(0);
        break;

	  case 'a': //左旋回

		  //simdata.player.x -= 0.05;

		  simdata.player.turn = 20.0/simdata.currentFps;

		  break;

	  case 's': //後退

			//simdata.player.z += 0.05;

		  simdata.player.move = 8.0/ simdata.currentFps;

		  break;

	  case 'd': //右旋回

			//simdata.player.x += 0.05;

		  simdata.player.turn = -20.0/ simdata.currentFps;

		  break;

	  case 'w': //前進

			//simdata.player.z -= 0.05;

		  simdata.player.move = -8.0/ simdata.currentFps;

		  break;

      default:
        break;
    }
    return;
}
void charKeyUp( unsigned char key, int x, int y )
{
	switch (key) {

	case 'a': //左旋回

		//simdata.player.x -= 0.05;

		simdata.player.turn = 0;

		break;

	case 's': //後退

		  //simdata.player.z += 0.05;

		simdata.player.move = 0;

		break;

	case 'd': //右旋回

		  //simdata.player.x += 0.05;

		simdata.player.turn = 0;

		break;

	case 'w': //前進

		  //simdata.player.z -= 0.05;

		simdata.player.move = 0;

		break;

	case 'r':
		if (simdata.currentState == 2 || simdata.currentState == 3) {
			simdata.currentState = 0;
		}
		break;

	default:
		break;
	}
}
/*--------------------------------------------------------------- funcKeyDown/Up
 * funcKeyDown/Up - GLUT special key callback
 * key: GLUT key code
 * x, y: mouse position
 */
void funcKeyDown( int key, int x, int y )
{
	//ファンクションキー
	//[F*]: GLUT_KEY_F*(*は1～12)
	//[F1]: GLUT_KEY_F1
	//[F12]:GLUT_KEY_F12
	//その他の機能キー
    //[PageUp]  : GLUT_KEY_PAGE_UP:
    //[PageDown]: GLUT_KEY_PAGE_DOWN:
    //[Home]    : GLUT_KEY_HOME:
    //[End]     : GLUT_KEY_END:
    //[Insert]  : GLUT_KEY_INSERT:

	//カーソルキー
	switch( key ){
	  case GLUT_KEY_LEFT: //[←]

		break;
  	  case GLUT_KEY_RIGHT://[→]

		break;
	  case GLUT_KEY_UP: //[↑]

		break;
	  case GLUT_KEY_DOWN://[↓]

		break;
	}
}
void funcKeyUp( int key, int x, int y )
{
	switch( key ){
	  case GLUT_KEY_LEFT: //[←]

		break;
  	  case GLUT_KEY_RIGHT://[→]

		break;
	  case GLUT_KEY_UP: //[↑]

		break;
	  case GLUT_KEY_DOWN://[↓]

		break;
	}
}
/*------------------------------------------------------------- mouseClick
 * mouseClick - GLUT mouse callback function
 * button: mouse button
 * state：press or release
 * x, y：mouse position
 *--------*/
void mouseClick( int button , int state, int x, int y )
{

	static int canShoot = 0;

    switch( button ){
      case GLUT_LEFT_BUTTON:
        switch( state ){
          case GLUT_DOWN: // press
			  if (canShoot == 0) {
				  
				  

				  canShoot = 1;
				  for (int i = 0; i < simdata.bullet_count; i++)
				  {
					  if (simdata.bullets[i].state == 0) {

						  simdata.bullets[i].pos.x = simdata.player.pos.x;

						  simdata.bullets[i].pos.y = simdata.player.pos.y + 0.5; //発射高さ調整

						  simdata.bullets[i].pos.z = simdata.player.pos.z;

						  simdata.bullets[i].rot.z = simdata.player.rot.z;

						  simdata.bullets[i].state = 1;
						  break;
					  }
				  }

			  }
            break;
          case GLUT_UP: // release

			  canShoot = 0;

            break;
          default:
            break;
        }
        break;
      case GLUT_MIDDLE_BUTTON:
        switch( state ){
          case GLUT_DOWN: // press

            break;
          case GLUT_UP: // release

            break;
          default:
            break;
        }
        break;
      case GLUT_RIGHT_BUTTON:
        switch( state ){
          case GLUT_DOWN: // press
			  printf("Fortune!!!");

			  for (int i = 0; i < simdata.enemy_count; i++) {

				  if (simdata.enemies[i].state != 2)continue;
				  if (HitTest(&simdata.player, &simdata.enemies[i])) {
					  simdata.enemies[i].state = 5;
					  simdata.enemies[i].move = -3 / simdata.currentFps;
					  simdata.enemies[i].rot.z = simdata.player.rot.z;
					

				  }
	
			  }

			  for (int i = 0; i < simdata.fortuneBox_count; i++) {
				  if (simdata.fortuneBoxes[i].state == 2)continue;
				  if (HitTest(&simdata.player, &simdata.fortuneBoxes[i])) {
					  //大吉・吉・中吉・小吉・末吉・凶・大凶
					  int fortune = (int)uniformRandom(0, 100);
					  
					  simdata.isCheckFortune = true;
					  simdata.frameCount = 0;
					  
					  switch (fortune)
					  {
						case 1:
							simdata.fortuneNum = 0;
							simdata.currentScore += 999999990;
							 break;
						case 2:
						case 3:
						case 4:
							simdata.fortuneNum = 2;
							simdata.currentScore += -900000;
							break;
						
						default:
							simdata.fortuneNum = 1;
							simdata.currentScore += 1000;
							break;
					  }
					  simdata.fortuneBoxes[i].state = 2;
					  simdata.fortuneBoxes[i].color = {1.0,0.0,0.0,0.0};
				  }
			  }

            break;
          case GLUT_UP: // release

            break;
          default:
            break;
        }
        break;
      default:
        break;
    }
    return;
}
/*---------------------------------------------------------------- mouseDrag 
 * mouseDrag - mouse drag callback function
 */
void mouseDrag( int x, int y )
{
	////////


	////////
    return;
}
/*-------------------------------------------------------------- mouseMotion
 * mouseMotion - passive mouse motion callback function
 */
void mouseMotion( int x, int y )
{
	////////


	////////
    return;
}