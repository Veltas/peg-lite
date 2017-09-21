#ifndef STACK_ALLOC_H_INCLUDED
#define STACK_ALLOC_H_INCLUDED

#include <stddef.h>

void
stack_acc_size(size_t *size_store, size_t add_size);

void *
load_stack_allocator(size_t capacity);

void *
stack_alloc(void *allocator, size_t size);

void
free_stack_allocator(void *allocator);

#endif // STACK_ALLOC_H_INCLUDED
