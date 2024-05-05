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
#include <thread>
#include <chrono>

// opengl (must be included before any other opengl library's)
#include <GL/glew.h>

// glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "macros.h"

// glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#endif // AQUASENSE_DEPS
