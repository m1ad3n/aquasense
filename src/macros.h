/**
 * @author Mladen Stanimirovic
 * @file macros.h
 *
 * @brief macros and inline functions
 */

#ifndef AQUASENSE_MACROS
#define AQUASENSE_MACROS

#include <GL/glew.h>
#include <iostream>
#include <fstream>

#define GLClearErrors() while (glGetError() != GL_NO_ERROR)
#define GLCall(x) GLClearErrors(); x;\
	if (auto error = glGetError()) {\
		std::cerr << "OPENGL ERROR (" << error << ") : " << error << " " << #x << " " << __FILE__ << " " << __LINE__ << std::endl;\
		exit(1);\
	}


#define READ_FROM_FILE(file_path, var) std::ifstream ss(file_path);\
	std::stringstream sbuffer;\
	sbuffer << ss.rdbuf();\
	var = sbuffer.str()

//
// circle related macros
//
#define PI 3.141592
#define CIRCLE_AREA(r) (PI*(r*r))

#endif
