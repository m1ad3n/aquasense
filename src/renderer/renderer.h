#ifndef AQUASENSE_RENDERER
#define AQUASENSE_RENDERER

#include "buffers/shader.h"
#include "buffers/vertex_array.h"

namespace as
{

class Renderer {
public:
    static void Draw(VertexArray* vao, int indicies_to_draw, Shader* shader);
    static void Clear(float red, float green, float blue, float alpha);
};

}

#endif
