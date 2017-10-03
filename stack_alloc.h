#ifndef STACK_ALLOC_H_INCLUDED
#define STACK_ALLOC_H_INCLUDED

#include <stddef.h>
#include <peg-lite.h>

DLL_LOCAL void
stack_acc_size(size_t *size_store, size_t add_size);

DLL_LOCAL void *
load_stack_allocator(size_t capacity);

DLL_LOCAL void *
stack_alloc(void *allocator, size_t size);

DLL_LOCAL void
free_stack_allocator(void *allocator);

#endif // STACK_ALLOC_H_INCLUDED
