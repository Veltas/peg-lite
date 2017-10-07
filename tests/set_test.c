#include "../set.h"
#include <stddef.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MIN(a, b) ((a) <= (b) ? (a) : (b))

static void
inc_str(unsigned char str[const 8])
{
  size_t i = 0;
  while (i < 7 && !++str[i++]);
}

static void
not_zero(unsigned char str[const 8])
{
  for (size_t i = 0; i < 7; ++i) if (!str[i]) ++str[i];
}

#define N MIN((size_t)-1, 20000ull)

int
main(void)
{
  // Create set
  void *const set_test = load_set(
    set_str_hash_in_place,
    set_strcmp_in_place,
    8,
    0
  );
  // Check size
  assert(!set_size(set_test));
  // Insert strings
  unsigned char str[8] = {0};
  not_zero(str);
  for (size_t i = 0; i < N; ++i) {
    set_insert(set_test, str);
    inc_str(str);
    not_zero(str);
  }
  // Check for never-inserted string
  assert(!set_get(set_test, str));
  // Lookup inserted strings
  memset(str, 0, sizeof str - 1);
  not_zero(str);
  for (size_t i = 0; i < N; ++i) {
    assert(set_get(set_test, str));
    inc_str(str);
    not_zero(str);
  }
  // Check size
  assert(set_size(set_test) == N);
  // Remove some strings with set_remove
  memset(str, 0, sizeof str - 1);
  not_zero(str);
  for (size_t i = 0; i < N/2; ++i) {
    set_remove(set_test, str);
    inc_str(str);
    not_zero(str);
  }
  // Check size
  assert(set_size(set_test) == N/2);
  // Remove rest of strings with set_remove_at
  for (size_t i = N/4; i < N/2; ++i) {
    set_remove_at(set_test, set_get(set_test, str));
    inc_str(str);
    not_zero(str);
  }
  // Check for previously given string
  memset(str, 0, sizeof str - 1);
  not_zero(str);
  assert(!set_get(set_test, str));
  // Check size
  assert(set_size(set_test) == N/4);
  // Cleanup set
  free_set(set_test);
}
