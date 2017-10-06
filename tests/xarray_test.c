#include "../xarray.h"
#include <stddef.h>
#include <assert.h>
#include <string.h>

#define MIN(a, b) ((a) <= (b) ? (a) : (b))
#define N MIN((size_t)-1, 1000000ul)

int
main(void)
{
  // Load test xarray
  size_t *test = load_xarray(0, sizeof *test);
  // Check size
  assert(xarray_size(test) == 0);
  // Insert some elements
  for (size_t i = 0; i < N/2; ++i) {
    test = xarray_expand(test);
    test[i] = i;
  }
  // Check size
  assert(xarray_size(test) == N/2);
  // Check their values
  for (size_t i = 0; i < N/2; ++i) assert(test[i] == i);
  // Insert multiple at once
  test = xarray_resize(test, N);
  memset(test + N/2, 0, sizeof (size_t [N/2]));
  // Check size
  assert(xarray_size(test) == N);
  // Check values
  for (size_t i = 0; i < N/2; ++i) assert(test[i] == i);
  for (size_t i = N/2; i < N; ++i) assert(!test[i]);
  // Free test xarray
  free_xarray(test);
}
