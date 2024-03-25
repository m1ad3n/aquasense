#ifndef AQUASENSE_VERTEX_BUFFER
#define AQUASENSE_VERTEX_BUFFER

/**
 * ASBuffer - AquaSense Buffer
 */
typedef struct sBuffer ASBuffer;

/**
 * Different names for buffers
 */
#define VertexBuffer struct sBuffer
#define VBuffer      struct sBuffer

#define IndexBuffer  struct sBuffer
#define IBuffer      struct sBuffer

/**
 * ID     - opengl generated ID
 * TARGET - (GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, ...)
 */
struct sBuffer {
	unsigned int ID;
	long long TARGET;
};

/**
 * @brief
 *
 * @param[in]  _target  The target (GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, ...)
 * @param      _data    The data (array)
 * @param[in]  _size    The size (sizeof array)
 *
 * @return     A reference to a new buffer
 */
struct sBuffer* sBuffer_new(long long _target, void* _data, unsigned int _size);

/**
 * @brief      Instructs OpenGL to utilize this buffer
 *
 * @param      svb   A reference to a buffer
 * @return     void
 */
void sBuffer_bind(struct sBuffer* svb);

/**
 * @brief      Instructs OpenGL to disengage from using this buffer
 *
 * @param      svb   A reference to a buffer
 * @return     void
 */
void sBuffer_unbind(struct sBuffer* svb);

/**
 * @brief      Destroys a buffer object and deallocates its resources
 *
 * @param      svb   The buffer object to be destroyed
 * @return     void
 */
void sBuffer_destroy(struct sBuffer* svb);

#endif