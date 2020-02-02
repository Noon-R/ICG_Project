#include <stdlib.h>
#include <stdio.h>

#include "platform.h"

#include "common.h"

#include "sim.h"

extern SimDataT simdata;
extern WindowDataT window;

/*---------------------------------------------------------------- Viewing
 * Viewing:
 *--------*/
void Viewing( void )
{
    gluLookAt( 0.0, 3, -5.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0 );
	glRotatef(-simdata.active_camera->rot.x, 0.0, 0.0, 1.0);

	glRotatef(-simdata.active_camera->rot.y, 1.0, 0.0, 0.0);

	glRotatef(-simdata.active_camera->rot.z, 0.0, 1.0, 0.0);

	//分かりやすいように改行していますが、改行なしでも構いません。

	glTranslatef(-simdata.active_camera->pos.x,

		-simdata.active_camera->pos.y,

		-simdata.active_camera->pos.z);
}
/*---------------------------------------------------------------- Projection
 * Projection:
 *--------*/
void Projection( void )
{
	//---- begin projection transformation
    gluPerspective( 45.0, window.aspect, simdata.clip_near, simdata.clip_far );
}
