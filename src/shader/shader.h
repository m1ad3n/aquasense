#ifndef AQUASENSE_SHADER
#define AQUASENSE_SHADER

#include "../deps.h"

#define MAX_PATH 50

typedef struct {
    unsigned int ID;
    char vertex_path[MAX_PATH];
    char fragment_path[MAX_PATH];
} sShader;

sShader* sShader_new(const char* _vpath, const char* _fpath);

void sShader_use(const sShader* shader);
void sShader_setBool(const sShader* shader, const char* name, bool value);
void sShader_setInt(const sShader* shader, const char* name, int value);
void sShader_setFloat(const sShader* shader, const char* name, float value);
void sShader_setVec4(const sShader* shader, const char* name, float values[4]);
void sShader_destroy(sShader* shader);

#endif