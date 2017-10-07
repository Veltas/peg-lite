#include <assert.h>

#include "../stack_alloc.h"

#define MIN(a, b) ((a) <= (b) ? (a) : (b))
#define N MIN((size_t)-1, 200000ul)

int
main(void)
{
  // Calculate required capacity
  size_t test_cap = 0;
  stack_acc_size(&test_cap, sizeof (size_t *[N]));
  for (size_t i = 0; i < N; ++i) {
    stack_acc_size(&test_cap, sizeof (size_t));
  }
  // Load stack allocator with such a capacity
  void *const test = load_stack_allocator(test_cap);
  // Allocate some objects
  size_t **const ptrs = stack_alloc(test, sizeof (size_t *[N]));
  for (size_t i = 0; i < N; ++i) {
    ptrs[i] = stack_alloc(test, sizeof (size_t));
  }
  // Try to allocate too much
  assert(!stack_alloc(test, 1));
  // Cleanup stack allocator
  free_stack_allocator(test);
}
