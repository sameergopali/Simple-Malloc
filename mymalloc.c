#include "mymalloc.h"
#include "assert.h"
#include <stdio.h>
#include <sys/mman.h>

/**< Global variable for the head of the free block list. */
node_t *head = NULL;


void initialize()
{
    head = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    head->size = POOL_SIZE - HEADER_SIZE;
    head->next = NULL;
}


void * mymalloc(size_t size)
{
    if (size == 0)
    {
        return NULL;
    }
    if (head == NULL)
    {
        printf("info:: mymalloc:: Initializing new pool\n");
        initialize();
        print_freelist();
    }

    void *block_ptr;
    node_t *curr = head;
    node_t *prev = NULL;


    /**< Traverse free block list to find first node greater or equal to requested size */
    while (curr)
    {
        if (curr->size >= size)
        {
            /**< pointer to the free space*/
            block_ptr = FREESPACE_PTR(HEADER_PTR(curr));

            if (curr->size > size)
            {
                
                /**< node greater than requested size, split it */
                node_t *node_new = GET_NODE(block_ptr, size);
                node_new->size = curr->size - (size + HEADER_SIZE);
                node_new->next = curr->next;
                curr->next = node_new;
            }
            
            /**< Remove/adjust links from freelist*/
            if (prev)
            {
                prev->next = curr->next;
            }
            else
            {
                head = curr->next;
            }

            /**< insert header above the free space*/
            header_t *header = HEADER_PTR(curr);
            header->size = size;
            header->magic = 12345679;

            return block_ptr;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }

    printf("Error: No free memory of given size\n");
    return NULL;
}


void myfree(void *ptr)
{
    /**< Get Header of free space first*/
    header_t *hptr = GET_HPTR(ptr);
    assert(hptr->magic == 12345679);
    hptr->magic = 0;

    /**< Create new freelist node to claim the freed up space*/
    node_t *node = NODE_PTR(hptr);
    node_t *curr = head;
    node_t *prev = NULL;

    /**< Find the position of node in the freelist*/
    while (curr && curr < node)
    {
        prev = curr;
        curr = curr->next;
    }

    /**< Insert node in the freelist*/
    if (prev)
    {
        prev->next = node;
    }
    else
    {
        head = node;
    }

    node->next = curr;
    node->size = hptr->size;

    /**< Coalesce adjacent free blocks */
    if (prev && (char *)prev + (HEADER_SIZE + prev->size) == (char *)node)
    {
        prev->size += node->size + HEADER_SIZE;
        prev->next = node->next;
        node = prev;
    }

    if (curr && (char *)node + (HEADER_SIZE + node->size) == (char *)curr)
    {
        node->size += curr->size + HEADER_SIZE;
        node->next = curr->next;
    }
}



void cleanup()
{
    
    head = head->next;
    while (head) {
        node_t *ptr = head;
        head = head->next;
        munmap(head, head->size+HEADER_SIZE);
    }
}


void print_freelist()
{
    printf("Freelist: \n");
    node_t *ptr = head;
    int c = 0;
    while (ptr)
    {
        printf("(%d) <%p> (size: %d)\n", c, ptr, ptr->size);
        ptr = ptr->next;
        c++;
    }
}
