#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "mymalloc.h"
int main(){


 printf("Test Case 1: Allocate and free memory\n");
    int *int_ptr1 = (int *)mymalloc(sizeof(int));
    if (int_ptr1 != NULL)
    {
        *int_ptr1 = 42;
        printf("Allocated int_ptr1: %d\n", *int_ptr1);
        myfree(int_ptr1);
        printf("Freed int_ptr1\n");
    }
    else
    {
        printf("Allocation failed for int_ptr1\n");
    }

    // Test Case 2: Allocate an array of integers.
    printf("\nTest Case 2: Allocate an array of integers\n");
    int *int_array = (int *)mymalloc(5 * sizeof(int));
    if (int_array != NULL)
    {
        for (int i = 0; i < 5; i++)
        {
            int_array[i] = i * 2;
            printf("int_array[%d]: %d\n", i, int_array[i]);
        }
        myfree(int_array);
        printf("Freed int_array\n");
    }
    else
    {
        printf("Allocation failed for int_array\n");
    }

    // Test Case 3:Out of memory for larger than heap request
    printf("\nTest Case 3: Out of memory for larger than heap request\n");
    size_t large_size = 1024 * 1024; // 1 MB
    char *large_block = (char *)mymalloc(large_size);
    if (large_block != NULL)
    {
        printf("Allocated a large block of size %zu bytes\n", large_size);
        myfree(large_block);
        printf("Freed the large block\n");
    }
    else
    {
        printf("Allocation failed for the large block\n");
    }

    // Test Case 4: Merging  adjacent free nodes.
    printf("\nTest Case 4: Merging of adjacent free nodes\n");
	printf("\nAllocating 10 bytes each for ptr1, ptr2, ptr3. (In reality 26 bytes is allocated as header size is 16 bytes) \n");
    void *ptr1 = mymalloc(10);
    void *ptr2 = mymalloc(10);
    void *ptr3 = mymalloc(10);
	printf("\nPrinting single node heap with remaining memory\n");
	print_freelist();
	printf("\nFreeing ptr2\n");
	myfree(ptr2);
	print_freelist();
	printf("\nFreeing ptr1,freespace from ptr1 and ptr2 are now merged\n");
	myfree(ptr1);
	print_freelist();
	printf("\nFreeing ptr3, ptr3 is now merged\n");
	myfree(ptr3);
	print_freelist();
    

    

    // Clean up allocated memory and resources.
    cleanup();

  
    return 0;
}
