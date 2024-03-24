#ifndef AQUASENSE_VERTEX_BUFFER
#define AQUASENSE_VERTEX_BUFFER

typedef struct sBuffer ASBuffer;

#define VertexBuffer struct sBuffer
#define VBuffer      struct sBuffer

#define IndexBuffer  struct sBuffer
#define IBuffer      struct sBuffer

struct sBuffer {
	unsigned int ID;
	long long TARGET;
};

struct sBuffer* sBuffer_new(long long _target, void* _data, unsigned int size);

void sBuffer_bind(struct sBuffer* svb);
void sBuffer_unbind(struct sBuffer* svb);
void sBuffer_destroy(struct sBuffer* svb);

#endif