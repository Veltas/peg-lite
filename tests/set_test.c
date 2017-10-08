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

static void
check_size(void *const set, size_t expected_size)
{
  assert(set_size(set) == expected_size);
}

#define N MIN((size_t)-1, 20000ull)

static void
check_set(void)
{
  // Create set
  void *const set_test = load_set(
    set_str_hash_in_place, set_strcmp_in_place, 8, 0
  );

  check_size(set_test, 0);

  // Iterate over strings
  size_t count = 0;
  for (char *str = set_next(set_test, NULL); str; str = set_next(set_test, str))
    ++count;
  check_size(set_test, count);

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

  check_size(set_test, N);

  // Iterate over strings
  count = 0;
  for (char *str = set_next(set_test, NULL); str; str = set_next(set_test, str))
    ++count;
  check_size(set_test, count);

  // Remove some strings with set_remove
  memset(str, 0, sizeof str - 1);
  not_zero(str);
  for (size_t i = 0; i < N/2; ++i) {
    set_remove(set_test, str);
    inc_str(str);
    not_zero(str);
  }

  check_size(set_test, N/2);

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

  check_size(set_test, N/4);

  // Cleanup set
  free_set(set_test);
}

int
main(void)
{
  check_set();
}
