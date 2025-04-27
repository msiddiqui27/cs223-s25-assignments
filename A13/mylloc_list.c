/**
 * name: Maryam
 * date: 04/25/2025
 * description: This implementation uses a header to keep track of the memory requested from sbrk. When we re-use memory that is freed, we typically will not re-use the entire block of memory. Modify the implementation from the reading to Extend this header to keep track of both the requested size and the amount of memory currently used in the chu
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk
{
  int size;
  int used;
  struct chunk *next;
};
struct chunk *flist = NULL;

void *malloc(size_t size)
/**
 * allocates memory of given size
 * uses free list with a first fit strategy to find available memory
 * if no free block is found, it extends heap using sbrk()
 * @param size: # of bytes requested
 */
{
  if (size == 0) // if 0 bytes requested, return null; base case
  {
    return NULL;
  }

  struct chunk *prev = NULL;  // previous chunk in free list
  struct chunk *curr = flist; // curent chunk in free list

  while (curr != NULL) // search through flist
  {
    if (curr->size >= size)
    {
      if (prev == NULL) // remove big enough chunk from flist
      {
        flist = curr->next;
      }
      else
      {
        prev->next = curr->next; // or link around it
      }
      curr->used = size;         // set how much of chunk being used
      return (void *)(curr + 1); // return pointer to mem after header
    }
    prev = curr; // move to next chunk
    curr = curr->next;
  }

  void *memory = sbrk(sizeof(struct chunk) + size); // if no suitable chunk is found, request more mem from system

  struct chunk *new_chunk = (struct chunk *)memory; // initialize newly allocated chunk
  new_chunk->size = size;                           // total sizde of block
  new_chunk->used = size;                           // entire block being used
  new_chunk->next = NULL;                           // not part of flist
  return (void *)(new_chunk + 1);                   // return pointer to mem after header
}

void free(void *memory)
/**
 * frees previously allocated mem
 * marks chunk as unusaed and returns to front of flist
 */
{
  struct chunk *chunk_to_free = ((struct chunk *)memory) - 1; // get pointer to chunk header
  chunk_to_free->used = 0;                                    // unused

  chunk_to_free->next = flist; // return to front of flist
  flist = chunk_to_free;
}
