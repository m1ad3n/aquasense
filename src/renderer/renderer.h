#ifndef AQUASENSE_RENDERER
#define AQUASENSE_RENDERER

#include "buffers/shader.h"
#include "buffers/vertex_array.h"
#include "buffers/texture.h"

namespace as
{

class Renderer {
public:
    static void Draw(VertexArray* vao, unsigned int method, Shader* shader, int count = 0);
    static void Clear(float red, float green, float blue, float alpha);
    
    static void Quad(VertexArray* vao, Shader* shader_object, Texture* texture_object, const char* texture_uniform = "textureIndex", int texture_index = 0);
    static void Quad(VertexArray* vao, int indicies_count, Shader* shader_object, Texture* texture_object, const char* texture_uniform = "textureIndex", int texture_index = 0);

    static void Background(int width, int height, Shader* shader, Texture* texture);
};

}

#endif
