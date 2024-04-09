/**
 * @author Mladen Stanimirovic
 * @file deps.h
 *
 * @brief Header file containing dependencies
 */

#ifndef AQUASENSE_DEPS
#define AQUASENSE_DEPS

// for windows support
#include <windows.h>

// standard library's for c
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>


// opengl (must be included before any other opengl library's)
#include <GL/glew.h>

// glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "macros.h"

#endif // AQUASENSE_DEPS
