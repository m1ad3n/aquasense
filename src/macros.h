#ifndef AQUASENSE_MACROS
#define AQUASENSE_MACROS

//
// printf related macros
//
#define ERROR(PREFIX, MESSAGE) fprintf(stderr, "%s %s\n", PREFIX, MESSAGE)
#define GLFW_ERROR(MESSAGE) ERROR("GLFW ERROR:", MESSAGE)
#define OPENGL_ERROR(MESSAGE) ERROR("OPENGL ERROR:", MESSAGE)

//
// circle related macros
//
#define PI 3.141592
#define CIRCLE_AREA(r) (PI*(r*r))

#endif