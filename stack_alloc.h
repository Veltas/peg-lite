#ifndef STACK_ALLOC_H_INCLUDED
#define STACK_ALLOC_H_INCLUDED

// This module defines a "stack allocator", this allows one to more easily
// allocate related objects *near* to each other. Once it is allocated it does
// not change size.

#include <stddef.h>
#include <peg-lite.h>

// Calculate additional needed allocator capacity. For first calc use 0 at
// *size_store. Call function with needed sizes *IN ORDER* of the future
// allocations.
DLL_LOCAL void
stack_acc_size(size_t *size_store, size_t add_size);

// Create stack allocator with given capacity. Use stack_acc_size to calculate
// needed capacity (this will account for alignment requirements).
DLL_LOCAL void *
load_stack_allocator(size_t capacity);

// Allocate an object of given size. See stack_acc_size for instructions on
// calculating exact required capacities in advance. Returned pointers are null
// pointers, or pointers (aligned to max. fundamental alignment) allocated with
// the requested size.
DLL_LOCAL void *
stack_alloc(void *allocator, size_t size);

// Frees the stack allocator (and destroys everything allocated with it).
DLL_LOCAL void
free_stack_allocator(void *allocator);

#endif // STACK_ALLOC_H_INCLUDED
