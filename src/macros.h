/**
 * @author Mladen Stanimirovic
 * @file macros.h
 *
 * @brief macros and inline functions
 */

#ifndef AQUASENSE_MACROS
#define AQUASENSE_MACROS

#include <GL/glew.h>
#include <ostream>

#define GLClearErrors() while (glGetError() != GL_NO_ERROR)
#define GLCall(x) GLClearErrors(); x;\
	if (auto error = glGetError()) {\
		std::cerr << "OPENGL ERROR (" << error << ") : " << error << " " << #x << " " << __FILE__ << " " << __LINE__ << std::endl;\
		exit(1);\
	}

//
// circle related macros
//
#define PI 3.141592
#define CIRCLE_AREA(r) (PI*(r*r))

#endif
