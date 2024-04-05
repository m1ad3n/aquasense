#ifndef AQUASENSE_SHADER
#define AQUASENSE_SHADER

#include "buffer.h"
#include "../string_functions.h"

class Shader : public BufferBase {
public:
    unsigned int ID;

    Shader(Path shader_path);
    ~Shader() override {};

    void Bind() override;
    void Unbind() override;
    void Delete() override;

    void SetBool(const char* name, int value);
    void SetInt(const char* name, int value);
    void SetFloat(const char* name, float value);
    void SetVec4(const char* name, float values[4]);
    void SetMat4(const char* name, float* value);

private:
    int checkCompileErrors(unsigned int shader, const std::string& type);
};

#endif
