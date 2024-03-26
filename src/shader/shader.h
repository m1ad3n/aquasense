#ifndef AQUASENSE_SHADER
#define AQUASENSE_SHADER

/**
 * ASShader - AquaSense Shader
 */
typedef struct sShader ASShader;

/**
 * @brief Represents an OpenGL shader object.
 */
struct sShader {
    unsigned int ID;
};

struct sShader* sShader_new(const char* _vpath, const char* _fpath);
void sShader_use(const struct sShader* shader);
void sShader_setBool(const struct sShader* shader, const char* name, int value);
void sShader_setInt(const struct sShader* shader, const char* name, int value);
void sShader_setFloat(const struct sShader* shader, const char* name, float value);
void sShader_setVec4(const struct sShader* shader, const char* name, float values[4]);
void sShader_destroy(struct sShader* shader);
void sShader_checkCompileErrors(unsigned int shader, const char* type);

char* sReadDataFromFile(const char* _path);

#endif