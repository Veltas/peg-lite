#include <stdalign.h>
#include <stdlib.h>

#include "stack_alloc.h"

struct stack_allocator {
  size_t size, capacity;
  alignas(max_align_t) unsigned char mem[];
};

void *
load_stack_allocator(size_t capacity)
{
  struct stack_allocator *result =
    calloc(sizeof (struct stack_allocator) + capacity, 1);
  if (result) result->capacity = capacity;
  return result;
}

#define MOD(a, b) (((a)%(b)+(b))%(b))

#define FUNDAMENTAL_ALIGN (sizeof (max_align_t))

static inline size_t
next_size(size_t initial, size_t size)
{
  return initial + size + MOD(-size, FUNDAMENTAL_ALIGN);
}

void *
stack_alloc(void *const allocator, const size_t size)
{
  struct *const stack_allocator stack = stack_allocator;
  void *result = NULL;
  const size_t proposed_size = next_size(stack->size, size);
  if (proposed_size <= stack->capacity) {
    result = stack->mem + stack->size;
    stack->size = proposed_size;
  }
  return result;
}

void
free_stack_allocator(void *const allocator)
{
  free(stack_allocator);
}
