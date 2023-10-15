#ifndef MYMALLOC_H_
#define MYMALLOC_H_

/** @file
 *  @brief Memory Allocation Library Header
 *
 *  This header file defines data structures, macros, and function prototypes
 *  for a simple memory allocation library.
 */

#define _BSD_SOURCE
#include <stddef.h>

/** @def POOL_SIZE
 *  @brief The size of the memory pool used for allocations.
 */
#define POOL_SIZE 4096

/** @def HEADER_PTR(ptr)
 *  @brief Convert a pointer to a header pointer.
 *  @param ptr The pointer to convert.
 *  @return A header pointer.
 */
#define HEADER_PTR(ptr) (header_t *)ptr

/** @def NODE_PTR(ptr)
 *  @brief Convert a pointer to a node pointer.
 *  @param ptr The pointer to convert.
 *  @return A node pointer.
 */
#define NODE_PTR(ptr) (node_t *)ptr

/** @def FREESPACE_PTR(hptr)
 *  @brief Convert a header pointer to a free space pointer.
 *  @param hptr The header pointer to convert.
 *  @return A pointer to the beginning of the free space.
 */
#define FREESPACE_PTR(hptr) (void *)(hptr + 1)

/** @def GET_HPTR(ptr, size)
 *  @brief Calculate the header pointer given a pointer and block size.
 *  @param ptr The pointer to calculate the header pointer from.
 *  @param size The size of the block.
 *  @return A header pointer.
 */
#define GET_HPTR(ptr) (header_t *)ptr - 1

/** @def GET_NODE(ptr, size)
 *  @brief Calculate the node pointer given a pointer and block size.
 *  @param ptr The pointer to calculate the node pointer from.
 *  @param size The size of the block.
 *  @return A node pointer.
 */
#define GET_NODE(ptr, size) (node_t *)((char *)ptr + size)

/** @def HEADER_SIZE
 *  @brief The size of the header structure.
 */
#define HEADER_SIZE sizeof(header_t)

/** @struct header_t
 *  @brief Header structure for allocated memory blocks.
 */
typedef struct
{
    size_t size;  /**< The size of the allocated block. */
    int magic; /**< Magic number for integrity checking. */
} header_t;

/** @struct node_t
 *  @brief Node structure for free memory blocks.
 */
typedef struct __node_t
{
    size_t size; /**< The size of the free block. */
    struct __node_t *next; /**< Pointer to the next free block. */
} node_t;

/**
 * @brief Initializes the memory pool.
 * 
 * This function sets up the initial memory pool using mmap and initializes the head node
 * for the linked list of free blocks.
 */
void initialize();

/**
 * @brief Allocates memory of the given size.
 * 
 * This function allocates memory of the specified size using a "fit first" algorithm. It
 * iterates through the free blocks and finds the first block that is large enough to
 * accommodate the requested size. If the block is larger than the requested size, it
 * splits the block and adds the remaining part to the free list.
 * 
 * @param size The size of the memory block to allocate.
 * @return A pointer to the allocated memory block.
 */
void *mymalloc(size_t size);

/**
 * @brief Frees memory previously allocated with mymalloc.
 * 
 * This function frees memory previously allocated with mymalloc. It also coalesces
 * adjacent free blocks if necessary and updates the free list accordingly.
 * 
 * @param ptr A pointer to the memory block to free.
 */
void myfree(void *ptr);

/**
 * @brief Prints the state of the free block list.
 * 
 * This function prints the current state of the free block list, including the address
 * and size of each free block.
 */
void print_freelist();

/**
 * @brief Cleans up allocated memory.
 * 
 * This function should be called when the program is done using the memory allocation
 * system. It cleans up the allocated memory using munmap.
 */
void cleanup();

#endif