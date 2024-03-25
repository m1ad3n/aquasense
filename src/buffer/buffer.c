#include "buffer.h"
#include "../deps.h"

struct sBuffer* sBuffer_new(long long _target, void* _data, unsigned int _size) {
	if (_data == NULL) return NULL;

	struct sBuffer* tmp = (struct sBuffer*)malloc(sizeof(struct sBuffer));
	tmp->TARGET = _target;
	
	glGenBuffers(1, &tmp->ID);
    glBindBuffer(tmp->TARGET, tmp->ID);
    glBufferData(tmp->TARGET, _size, _data, GL_STATIC_DRAW);

    return tmp;
}

void sBuffer_bind(struct sBuffer *svb) {
	if (svb == NULL) return;
	glBindBuffer(svb->TARGET, svb->ID);
}

void sBuffer_unbind(struct sBuffer *svb) {
	glBindBuffer(svb->TARGET, 0);
}

void sBuffer_destroy(struct sBuffer *svb) {
	if (svb == NULL) return;
	glDeleteBuffers(1, &svb->ID);
	free(svb);
	svb = NULL;
}