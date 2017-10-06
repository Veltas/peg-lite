#include "../set.h"
#include <stddef.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define IGNORE(x) ((void)sizeof (x))
#define MIN(a, b) ((a) <= (b) ? (a) : (b))

#define N_HASH_BYTES (sizeof (size_t))

size_t
string_hash(const void *const str_p)
{
  const char *const str = *(char *const *)str_p;
  size_t result = 0;
  for (size_t i = 0; i < sizeof (size_t) && str[i]; ++i)
    result |= (size_t)str[i] << CHAR_BIT*i;
  return result;
}

bool
string_cmp(const void *const s1, const void *const s2, const size_t len)
{
  IGNORE(len);
  return !strcmp(*(char *const *)s1, *(char *const *)s2);
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

int
main(void)
{
  void *const set_test = load_set(string_hash, string_cmp, sizeof (char *), 0);
  unsigned char str[8] = {0};
  for (size_t i = 0; i < MIN((size_t)-1, 4000000); ++i) {
    char *copy_str = malloc(8);
    for (size_t i = 0; i < 8; ++i) copy_str[i] = str[i];
    set_insert(set_test, &copy_str);
    inc_str(str);
    not_zero(str);
  }
  free_set(set_test);
}
