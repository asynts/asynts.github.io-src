#pragma once

void *base_realloc(const char *file, const char *function, int line, void *ptr,
                   size_t size);

#define xrealloc(ptr, size)                                                    \
  base_realloc(__FILE__, __func__, __LINE__, ptr, size)

