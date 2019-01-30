#include "xrealloc.h"

// refer to: https://en.cppreference.com/w/c/memory/realloc
void *base_realloc(const char *file, const char *function, int line, void *ptr,
                   size_t size) {
  // If ptr is NULL, the behavior is the same as calling malloc(new_size).
  if (ptr == NULL) {
    return base_malloc(file, function, line, size);
  }

  // If new_size is zero, the behavior is implementation defined.
  if (size == 0) {
    printf("%s:%d(%s) realloc(): warning: reallocating with size = 0, use free "
           "instead\n",
           file, line, function);

    base_free(ptr);
    return NULL;
  }

  for (BaseAllocInfo *ai = base_alloc_info; ai; ai = ai->next) {
    if (ai->p == ptr) {
      void *newptr = realloc(ptr, size);

      if (newptr == NULL) {
        printf("%s:%d(%s) realloc(): error: realloc(%p, %zu) returned NULL\n",
               file, line, function, ptr, size);

        exit(EXIT_FAILURE);
      }

      ai->p = newptr;
      ai->size = size;
      ai->file = file;
      ai->function = function;
      ai->line = line;

      return newptr;
    }
  }

  // It must be previously allocated by malloc(), calloc() or realloc() and not
  // yet freed with a call to free or realloc.
  printf("%s:%d(%s) realloc(): warning: trying to reallocate unknown pointer "
         "%p\n",
         file, line, function, ptr);

  BaseAllocInfo *ai = malloc(sizeof(BaseAllocInfo));
  ai->p = realloc(ptr, size);
  ai->size = size;
  ai->file = file;
  ai->function = function;
  ai->line = line;
  ai->next = base_alloc_info;
  base_alloc_info = ai;

  return ai->p;
}

