#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include "sim.h"
#include "calc.h"

//float PI = 3.14159;
float RADIAN = M_PI / 180.0;
float DEGREE = 180.0 / M_PI;

//���I�u�W�F�N�ga����I�u�W�F�N�gb�ւ̕����x�N�g�������߂�֐�
//�I�u�W�F�N�g�Ԃ̕����x�N�g��
void DirectionAtoB( ObjDataT *a, ObjDataT *b, vector_t *dir )
{
	dir->x = b->pos.x - a->pos.x;
	dir->y = b->pos.y - a->pos.y;
	dir->z = b->pos.z - a->pos.z;
}
//���x�N�g���̑傫�����v�Z����֐�
//�x�N�g���̑傫��
float VectorNorm( vector_t *v )
{
	return sqrtf( v->x * v->x + v->y * v->y + v->z * v->z );
}
//�����������߂�֐��i�u�Փ˔���v�ō�����֐��̕ʃo�[�W�����j
//�I�u�W�F�N�g�ԋ���
float DistanceAtoB( ObjDataT *a, ObjDataT *b )
{
	vector_t v;
 	DirectionAtoB( a, b, &v );
	return VectorNorm( &v );
}
//�������x�N�g��������ʊp�Ƌp�����߂�֐�
float VectorToPolar( vector_t *v,  euler_t *angle )
{
	float d = sqrtf( v->x * v->x + v->z * v->z );
	angle->pitch = DEGREE * atan2f( v->y, d );
	angle->yaw = DEGREE * atan2f( - v->x, - v->z );
	return VectorNorm( v );
}
//��
float EulerAtoB( ObjDataT *a, ObjDataT *b, euler_t *angle )
{
	vector_t dir;
	DirectionAtoB( a, b, &dir );
	VectorToPolar( &dir, angle );
	return VectorNorm( &dir );
}
//��
void MoveObject( ObjDataT *obj )
{
	obj->rot.z += obj->turn;
	obj->pos.x -= obj->move * sinf( obj->rot.z * RADIAN );
	obj->pos.z -= obj->move * cosf( obj->rot.z * RADIAN );
}

bool HitTest(ObjDataT *a, ObjDataT *b)

{
	if (DistanceAtoB(a, b) < a->radius + b->radius) {
		return true;
	} else {
		return false;
	}

}

float uniformRandom(float min, float max) {
	double r;
	r = (double)rand() / (double)RAND_MAX;
	r = r * (max - min) + min;
	return r;
}