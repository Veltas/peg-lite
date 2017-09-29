#include <stdalign.h>
#include <stdlib.h>

#include "stack_alloc.h"

struct stack_allocator {
  size_t size, capacity;
  alignas(max_align_t) unsigned char mem[];
};

#define MOD(a, b) (((a)%(b)+(b))%(b))

#define FUNDAMENTAL_ALIGN (sizeof (max_align_t))

static inline size_t
stack_next_size(const size_t current_size, const size_t add_size)
{
  return current_size + add_size + MOD(-add_size, FUNDAMENTAL_ALIGN);
}

void
stack_acc_size(size_t *const size_store, const size_t add_size)
{
  *size_store = stack_next_size(*size_store, add_size);
}

void *
load_stack_allocator(size_t capacity)
{
  struct stack_allocator *result =
    calloc(1, sizeof (struct stack_allocator) + capacity);
  if (result) result->capacity = capacity;
  return result;
}

void *
stack_alloc(void *const allocator, const size_t size)
{
  struct stack_allocator *const stack = allocator;
  void *result = NULL;
  const size_t proposed_size = stack_next_size(stack->size, size);
  if (proposed_size <= stack->capacity) {
    result = stack->mem + stack->size;
    stack->size = proposed_size;
  }
  return result;
}

void
free_stack_allocator(void *const allocator)
{
  free(allocator);
}
