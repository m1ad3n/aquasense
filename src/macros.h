#ifndef AQUASENSE_MACROS
#define AQUASENSE_MACROS

#include "deps.h"
#include <stdio.h>

// OpenGL ERRORS
extern inline void GLClearErrors() {
	while (glGetError() != GL_NO_ERROR);
}

extern inline void GLCheckError() {
	unsigned int code = glGetError();
	if (code) printf("[OPENGL ERROR][%d]\n", code);
}

//
// circle related macros
//
#define PI 3.141592
#define CIRCLE_AREA(r) (PI*(r*r))

#endif