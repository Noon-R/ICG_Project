#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "platform.h"

#include "common.h"

#include "sim.h"

#include "Vector.h"


#define PI 3.14159265

extern WindowDataT window;
extern SimDataT simdata;

//-------- prototypes for user functions

void setMaterialColor( float r, float g, float b );

void SetTransform(ObjDataT *objData);
void SetColor(ObjDataT *objData);

float gizmoDis = 1000000;

void setMaterial(Vec4 dif, Vec4 spe)
{
	float diffuse[] = { dif.x, dif.y, dif.z, dif.w }; /*ŠgU”½ËŒW”*/
	float specular[] = { spe.x, spe.y, spe.z, spe.w }; /*‹¾–Ê”½ËŒW”*/

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 64.0);
	return;
}

void Rotate(float row, float pitch, float yaw) {
	glRotatef(yaw, 0.0, 1.0, 0.0);
	glRotatef(pitch, 1.0, 0.0, 0.0);
	glRotatef(row, 0.0, 0.0, 1.0);
}

void DrawSphere(double radius, int slices, int stacks) {

	glPushMatrix();
	{
		glRotatef(-90, 1.0, 0.0, 0.0);
		glutSolidSphere(radius, slices, stacks);
		//glutSolidSphere(radius, slices, stacks);
	}
	glPopMatrix();

}

void DrawCone(double radius, double height, int slices, int stacks) {

	glPushMatrix();
	{
		glRotatef(-90, 1.0, 0.0, 0.0);
		glutSolidCone(radius, height, slices, stacks);
	}
	glPopMatrix();

}

void DrawTorus(double innerR, double outerR, int nSizes, int rings) {

	glPushMatrix();
	{
		glRotatef(-90, 1.0, 0.0, 0.0);
		glutSolidTorus(innerR, outerR, nSizes, rings);
	}
	glPopMatrix();

}

void drawGizmo() {

	//xAsid
	glBegin(GL_LINES);

	setMaterialColor(1.0, 0.0, 0.0);
	glVertex3f(-gizmoDis, 0.0, 0.0);
	glVertex3f(gizmoDis, 0.0, 0.0);

	glEnd();

	//yAsid
	glBegin(GL_LINES);

	setMaterialColor(0.0, 1.0, 0.0);
	glVertex3f(0.0, -gizmoDis, 0.0);
	glVertex3f(0.0, gizmoDis, 0.0);

	glEnd();

	//zAsid

	glBegin(GL_LINES);

	setMaterialColor(.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -gizmoDis);
	glVertex3f(0.0, 0.0, gizmoDis);

	glEnd();
}


void drawCharacter(void)
{
	glColor3f(1.0, 1.0, .9); /*•`‰æ‚·‚é}Œ`‚ÌF‚ğ”’‚Éw’è*/

	setMaterial(
		Vec4{ 1.0, 1.0, 0.8, 1.0 },
		Vec4{ 1.0, 1.0, 1.0, 1.0 });
	DrawSphere(1.0, 16, 16);

	float dis_eye = 0.7;

	//EYEs

	setMaterial(
		Vec4{ 0.1, 0.1, 0.1, 1.0 },
		Vec4{ 1.0,1.0,1.0,1.0 });

	glPushMatrix();
	{
		glTranslatef(
			dis_eye * cosf(PI / 4.5),
			dis_eye * sinf(PI / 4.5) - 0.3,
			cosf(PI / 4)
		);
		DrawSphere(0.15, 16, 16);


	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(
			-dis_eye * cosf(PI / 4.5),
			dis_eye * sinf(PI / 4.5) - 0.3,
			cosf(PI / 4)
		);
		DrawSphere(0.15, 16, 16);


	}
	glPopMatrix();

	//Legs

	setMaterial(
		Vec4{ 0.6, 0.8, 0.3, 1.0 },
		Vec4{ 1.0, 1.0, 1.0, 1.0 });
	glPushMatrix();
	{
		glTranslatef(
			cosf(PI / 3),
			-sinf(PI / 3) - 0.15,
			0
		);
		DrawCone(0.3, 0.2, 16, 16);


	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(
			-cosf(PI / 3),
			-sinf(PI / 3) - 0.15,
			0
		);
		DrawCone(0.3, 0.2, 16, 16);


	}
	glPopMatrix();

	//Shade

	setMaterial(
		Vec4{ 0.2, 0.2, 0.0, 1.0 },
		Vec4{ 1.0, 1.0, 1.0, 1.0 });
	glPushMatrix();
	{
		glNormal3f(0.0, 1.0, 0.0);
		glTranslatef(0.0, 1.4, 0.0);

		glBegin(GL_TRIANGLE_FAN); {

			glVertex3f(0, 0, 0);

			float r = 1.5;
			int n = 6;
			for (int i = 0; i <= n; i++) {
				glVertex3f(
					r * sin(2 * PI * i / n),
					-1,
					r * cos(2 * PI * i / n)
				);
			}
		}
		glEnd();

	}
	glPopMatrix();


	return;
}



/*--------------------------------------------------------- setMaterialColor
 * setMaterialColor:
 *--------*/
void setMaterialColor( float r, float g, float b )
{
    float diffuse[4];
    float specular[] = { 0.8, 0.8, 0.8, 1.0 };

	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = 1.0;

    glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );
    glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
    glMaterialf( GL_FRONT, GL_SHININESS, 32.0 );

    return;
}

void SetTransform(ObjDataT *objData){

	glTranslatef(objData->pos.x, objData->pos.y, objData->pos.z);  //ƒIƒuƒWƒFƒNƒgˆÊ’u
	glRotatef(objData->rot.z, 0.0, 1.0, 0.0); //ƒIƒuƒWƒFƒNƒg‰ñ“]Fƒˆ[Šp
	glRotatef(objData->rot.y, 1.0, 0.0, 0.0); //ƒIƒuƒWƒFƒNƒg‰ñ“]Fƒsƒbƒ`Šp
	glRotatef(objData->rot.x, 0.0, 0.0, 1.0); //ƒIƒuƒWƒFƒNƒg‰ñ“]Fƒ[ƒ‹Šp
	glScalef(objData->scale.x, objData->scale.y, objData->scale.z);
	
}

void SetColor(ObjDataT *objData) {
	setMaterialColor(objData->color.x, objData->color.y, objData->color.z);//‚¨F
}
/*----------------------------------------------------------- drawSolidCube
 * drawSolidCube:
 *--------*/
void drawSolidCube( void )
{
	glPushMatrix();
	{
		glTranslatef( 0.0, 0.0, 0.0 );   //ƒIƒuƒWƒFƒNƒgŠî€ˆÊ’u’²®
		glRotatef( 0.0, 0.0, 1.0, 0.0 ); //ƒIƒuƒWƒFƒNƒgŠî€p¨’²®Fƒˆ[Šp
		glRotatef( 0.0, 1.0, 0.0, 0.0 ); //ƒIƒuƒWƒFƒNƒgŠî€p¨’²®Fƒsƒbƒ`Šp
		glRotatef( 0.0, 0.0, 0.0, 1.0 ); //ƒIƒuƒWƒFƒNƒgŠî€p¨’²®Fƒ[ƒ‹Šp
		glutSolidCube( 0.75 );
	}
	glPopMatrix();
    return;
}
/*--------------------------------------------------------- drawSolidSphere
 * drawSolidSphere:
 *--------*/
void drawSolidSphere( void )
{
	glPushMatrix();
	{
		glTranslatef( 0.0, 0.0, 0.0 );    //ƒIƒuƒWƒFƒNƒgŠî€ˆÊ’u’²®
		glRotatef( 0.0, 0.0, 1.0, 0.0 );  //ƒIƒuƒWƒFƒNƒgŠî€p¨’²®Fƒˆ[Šp
		glRotatef( 90.0, 1.0, 0.0, 0.0 ); //ƒIƒuƒWƒFƒNƒgŠî€p¨’²®Fƒsƒbƒ`Šp
		glRotatef( 0.0, 0.0, 0.0, 1.0 );  //ƒIƒuƒWƒFƒNƒgŠî€p¨’²®Fƒ[ƒ‹Šp
		glutSolidSphere( 0.5, 18, 16 );   //”¼ŒaCŒo“x•ûŒü•ªŠ„”CˆÜ“x•ûŒü•ªŠ„”
	}
	glPopMatrix();
    return;
}

void drawString(float x, float y, float xscl, float yscl,
	void *font, char *string)
{
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glScalef(xscl*0.01, yscl*0.01, 1.0);

	/* $B%9%H%m!<%/%U%)%s%HJ8;zNs$NIA2h(B */
	while (*string) {
		glutStrokeCharacter(font, *string++);
	}
	glPopMatrix();
	return;
}

/*---------------------------------------------------------------- DrawScene
 * DrawScene:
 *--------*/

void DrawScene( void )
{

	//Fileld

	setMaterialColor(0,0.6,0.5);
	glBegin(GL_POLYGON); {

		for (int i = 0; i < 4; i++) {
			glVertex3f(
				simdata.groundVertex[i].x,
				simdata.groundVertex[i].y,
				simdata.groundVertex[i].z
				);
		}
				
	}
	glEnd();

	//PlayerCharacter
	glPushMatrix();
	{
		SetTransform(&simdata.player);
		SetColor(&simdata.player);
		drawCharacter();
	}
	glPopMatrix();

	//Enemy

	for (int i = 0; i < simdata.enemy_count; i++)
	{

		if (!simdata.enemies[i].visible) continue;
		glPushMatrix();
		{
			SetTransform(&simdata.enemies[i]);
			SetColor(&simdata.enemies[i]);
			drawCharacter();
		}
		glPopMatrix();

	}

	


	//Bullets
	for (int i = 0; i < simdata.bullet_count; i++)
	{
		if (!simdata.bullets[i].visible) continue;
		glPushMatrix();
		{
			SetTransform(&simdata.bullets[i]);
			SetColor(&simdata.bullets[i]);
			drawSolidSphere();
		}
		glPopMatrix();

	}

	//TrashArea

	glPushMatrix();
	{
		SetTransform(&simdata.trashZone);
		SetColor(&simdata.trashZone);
		drawSolidSphere();
	}
	glPopMatrix();

	//fortuneBox
	for (int i = 0; i < simdata.fortuneBox_count; i++)
	{
		if (!simdata.fortuneBoxes[i].visible) continue;
		glPushMatrix();
		{
			SetTransform(&simdata.fortuneBoxes[i]);
			SetColor(&simdata.fortuneBoxes[i]);
			drawSolidCube();
		}
		glPopMatrix();

	}

	drawGizmo();

	//=========HUD==========

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,640,0,480); //•Às“Š‰e‚Éİ’èi2D•\Œ»‚É•ÏXj
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	//======================

	char score_str[10];
	
	sprintf(score_str,"%09d",simdata.currentScore);

	drawString(5.0, 5.0, 15.0, 15.0,
				GLUT_STROKE_ROMAN,
		"SCORE: ");
	drawString(80, 5.0, 15.0, 15.0,
		GLUT_STROKE_ROMAN,
		score_str);

	if (simdata.isCheckFortune) {

		simdata.frameCount++;
		if (simdata.frameCount >= simdata.displayFrame * simdata.currentFps) {
			simdata.isCheckFortune = false;
		}
		drawString(100, 250, 50, 50,
			GLUT_STROKE_ROMAN,
			simdata.fortune[simdata.fortuneNum]);
	}

	switch (simdata.currentState)
	{
		case 2:
			drawString(100, 250, 50, 50,
				GLUT_STROKE_ROMAN,
				"GAME CLEAR!!!!!!");
			break;
		case 3:
			drawString(100, 200, 50, 50,
				GLUT_STROKE_ROMAN,
				"GAME OVER");
			break;
	}
	//======END===HUD========

    return;
}
