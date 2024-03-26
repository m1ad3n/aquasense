/**
 * @author Mladen Stanimirovic
 * @file cvec.h
 *
 * @brief Header file containing cvec struct (vector implementation in c)
 */

#ifndef CVEC_H
#define CVEC_H

/**
 * C++ support
 */
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void** items;
    unsigned int capacity;
    unsigned int size;
} cvec;

cvec* cvec_new();
cvec* cvec_from(int count, ...);

int cvec_resize(cvec* vec, unsigned int capacity);
int cvec_push(cvec* vec, void* item);
int cvec_pop(cvec* vec);
int cvec_remove(cvec* vec, unsigned int index);
int cvec_clean(cvec* vec);
int cvec_insert(cvec* vec, unsigned int index, void* item);
int cvec_size(cvec* vec);
int cvec_free(cvec* vec);

void* cvec_iter(cvec* vec);
void* cvec_at(cvec* vec, unsigned int index);
void* cvec_front(cvec* vec);
void* cvec_back(cvec* vec);

/**
 * End for C++ support
 */
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CVEC_H
