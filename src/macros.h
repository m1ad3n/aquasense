/**
 * @author Mladen Stanimirovic
 * @file macros.h
 *
 * @brief macros and inline functions
 */

#ifndef AQUASENSE_MACROS
#define AQUASENSE_MACROS

#include "deps.h"

#define GLClearErrors() while (glGetError() != GL_NO_ERROR)
#define GLCall(x) GLClearErrors(); x; if (GLLog(#x, __FILE__, __LINE__)) exit(1);

static bool GLLog(const char* func, const char* file, int line) {
	int code = glGetError();
	if (code)
		fprintf(stderr, "OPENGL ERROR (%d): %s %s:%d\n", code, func, file, line);
	return code;
}

//
// circle related macros
//
#define PI 3.141592
#define CIRCLE_AREA(r) (PI*(r*r))

#endif
