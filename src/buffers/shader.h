#ifndef AQUASENSE_SHADER
#define AQUASENSE_SHADER

#include "buffers/buffer.h"
#include "deps.h"

namespace as
{

class Shader : public BufferBase {
public:
    unsigned int ID;

    Shader(const char* shader_path);
    ~Shader() override {};

    void Bind() override;
    void Unbind() override;
    void Delete() override;

    void SetBool(const char* name, int value);
    void SetInt(const char* name, int value);
    void SetFloat(const char* name, float value);
    void SetVec2(const char* name, float values[2]);
    void SetVec3(const char* name, float values[3]);
    void SetVec4(const char* name, float values[4]);
    void SetMat4(const char* name, float* value);


private:
    int checkCompileErrors(unsigned int shader, const std::string& type);
};

}

#endif
