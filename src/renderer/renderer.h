#ifndef AQUASENSE_RENDERER
#define AQUASENSE_RENDERER

#include "buffers/shader.h"
#include "buffers/vertex_array.h"

namespace as
{

class Renderer {
public:
    static void Draw(VertexArray* vao, unsigned int method, Shader* shader, int count = 0);
    static void Clear(float red, float green, float blue, float alpha);
};

}

#endif
