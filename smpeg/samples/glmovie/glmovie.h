#ifndef _GLMOVIE_H_
#define _GLMOVIE_H_

#ifdef _XBOX
#include "xbox/fakeglx09.h"
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

GLenum glmovie_init( GLuint, GLuint );
void glmovie_quit( void );
void glmovie_draw( GLubyte* );
void glmovie_resize( GLuint, GLuint );
GLuint glmovie_next_power_of_2( GLuint seed );
GLboolean glmovie_is_power_of_2( GLuint value );

#ifdef __cplusplus
}
#endif

#endif
