/**
 * @author Mladen Stanimirovic
 * @file deps.h
 *
 * @brief Header file containing dependencies
 */

#ifndef AQUASENSE_DEPS
#define AQUASENSE_DEPS

// standard library's for c
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <filesystem>

// for windows support
#ifdef _WIN32
#   include <windows.h>
#endif

// opengl (must be included before any other opengl library's)
#include <GL/glew.h>

// glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "macros.h"

namespace as {
	using std::filesystem::path;
}

#endif // AQUASENSE_DEPS
