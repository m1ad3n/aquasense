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

/**
 * items       array of pointer to the elements
 * capacity    vectors capacity
 * size        element count
 */
typedef struct {
    void** items;
    unsigned int capacity;
    unsigned int size;
} cvec;

/**
 * @brief      Creates and returns a new pointer to the vector
 */
cvec* cvec_new();

/**
 * @brief      Creates a new vector and adds given arguments to it
 *
 * @param[in]  count      The count
 * @param[in]  <unnamed>  arguments (elements)
 *
 * @return     vector
 */
cvec* cvec_from(int count, ...);

/**
 * @brief      resizes vector to a given capacity
 *
 * @param      vec       The pointer to the vector
 * @param[in]  capacity  The new capacity
 *
 * @return     status code
 */
int cvec_resize(cvec* vec, unsigned int capacity);

/**
 * @brief      Pushes new element to the end
 *
 * @param      vec   The pointer to the vector
 * @param      item  The item
 *
 * @return     status code
 */
int cvec_push(cvec* vec, void* item);

/**
 * @brief      Removes last element
 *
 * @param      vec   The pointer to the vector
 *
 * @return     status code
 */
int cvec_pop(cvec* vec);

/**
 * @brief      Removes element at given position
 *
 * @param      vec    The pointer to the vector
 * @param[in]  index  The index
 *
 * @return     status code
 */
int cvec_remove(cvec* vec, unsigned int index);

/**
 * @brief      Removes all the elements
 *
 * @param      vec   The pointer to the vector
 *
 * @return     status code
 */
int cvec_clean(cvec* vec);

/**
 * @brief      Inserts new element at given position
 *
 * @param      vec    The pointer to the vector
 * @param[in]  index  The index
 * @param      item   The item
 *
 * @return     status code
 */
int cvec_insert(cvec* vec, unsigned int index, void* item);

/**
 * @brief      Returns size of the vector
 *
 * @param      vec   The pointer to the vector
 */
int cvec_size(cvec* vec);

/**
 * @brief      Destroys the vector (free its memory)
 *
 * @param      vec   The pointer to the vector
 *
 * @return     status code
 */
int cvec_free(cvec* vec);

/**
 * @brief      Returns a element of the vector at the current count and increments the count
 *
 * @param      vec   The pointer to the vector
 */
void* cvec_iter(cvec* vec);

/**
 * @brief      Returns a element at given position (index)
 *
 * @param      vec    The vector
 * @param[in]  index  The index
 */
void* cvec_at(cvec* vec, unsigned int index);

/**
 * @brief      Returns a last element 
 *
 * @param      vec   The pointer to the vector
 */
void* cvec_front(cvec* vec);

/**
 * @brief      Returns a first element
 *
 * @param      vec   The pointer to the vector
 */
void* cvec_back(cvec* vec);

/**
 * End for C++ support
 */
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CVEC_H
