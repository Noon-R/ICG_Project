#include <math.h>

//▼ベクトル
typedef struct {
	float x, y, z;
} vector_t;
//▼オイラー角による回転の表現
typedef struct {
	float roll, pitch, yaw;
} euler_t;

void DirectionAtoB( ObjDataT *a, ObjDataT *b, vector_t *dir );
float VectorNorm( vector_t *v );
float DistanceAtoB( ObjDataT *a, ObjDataT *b );
float VectorToPolar( vector_t *v,  euler_t *angle );
float EulerAtoB( ObjDataT *a, ObjDataT *b, euler_t *angle );
void MoveObject( ObjDataT *obj );
bool HitTest(ObjDataT *a, ObjDataT *b);

float uniformRandom(float min, float max);