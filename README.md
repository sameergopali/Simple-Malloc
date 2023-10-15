# Advance OS HW-1

This is a simple `malloc` and `free` implementation. The `mymalloc` function uses the "fit first" algorithm to find free space in the free list, and `myfree` frees the given pointer and coalesces adjacent free blocks.

## Building

To build the project, run the make  command:

```bash
make
``````
## Running
To run the project, execute the main executable:

```bash
./main
```

## Generate static library:

To only generate the static library, run the following command:

```bash
make libmymalloc.a
```

## Clean project

To delete project binaries, run make clean

```bash
make clean
```