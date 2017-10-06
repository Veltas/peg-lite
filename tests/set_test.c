#include "../set.h"
#include <stddef.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define IGNORE(x) ((void)sizeof (x))
#define MIN(a, b) ((a) <= (b) ? (a) : (b))

#define N_HASH_BYTES (sizeof (size_t))

// 64-bit FNV-1a
size_t
string_hash(const void *const str_p)
{
  size_t result = 0xcbf29ce484222325ull;
  const char *const str = str_p;
  for (size_t i = 0; i<7; ++i) {
    result *= 0x100000001b3ull;
    result ^= str[i];
  }
  return result;
}

bool
string_cmp(const void *const s1, const void *const s2, const size_t len)
{
  IGNORE(len);
  return !strcmp(s1, s2);
}

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

#define N MIN((size_t)-1, 40000000ull)

int
main(void)
{
  void *const set_test = load_set(string_hash, string_cmp, 8, 0);
  unsigned char str[8] = {0};
  not_zero(str);
  for (size_t i = 0; i < N; ++i) {
    set_insert(set_test, str);
    inc_str(str);
    not_zero(str);
  }
  memset(str, 0, sizeof str - 1);
  not_zero(str);
  for (size_t i = 0; i < N; ++i) {
    if (!set_get(set_test, str)) {
      fprintf(stderr, "String not found: %s\n", str);
      exit(EXIT_FAILURE);
    }
    inc_str(str);
    not_zero(str);
  }
  free_set(set_test);
}
