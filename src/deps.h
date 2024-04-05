/**
 * @author Mladen Stanimirovic
 * @file deps.h
 *
 * @brief Header file containing dependencies
 */

#ifndef AQUASENSE_DEPS
#define AQUASENSE_DEPS

// standard library's for c
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

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

#endif // AQUASENSE_DEPS