#include <stddef.h>
#include <stdalign.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "xarray.h"

#include "set.h"

// Use without brackets to substitute correct operation orders.
#define EXPAND_RATIO 3/4

struct list {
  struct link {
    struct link *next, *prev;
    alignas (max_align_t) unsigned char data[];
  } *first, *last;
};

struct set {
  size_t      size,
              key_size;
  struct list *buckets;
  set_hash    hash;
  set_key_cmp key_cmp;
};

DLL_LOCAL void *
load_set(
  const set_hash    hash,
  const set_key_cmp cmp,
  const size_t      key_size,
  size_t            n_buckets)
{
  if (!n_buckets) n_buckets = 1;
  struct set *const set = malloc(sizeof *set);
  *set = (struct set){
    .hash     = hash,
    .key_cmp  = cmp,
    .key_size = key_size,
    .buckets  = load_xarray(n_buckets, sizeof *set->buckets)
  };
  for (size_t i = 0; i < n_buckets; ++i) set->buckets[i] = (struct list){0};
  return set;
}

DLL_LOCAL void
free_set(void *const set)
{
  struct set *const set_i = set;
  struct list *const end = set_i->buckets + xarray_size(set_i->buckets);
  for (struct list *bucket = set_i->buckets; bucket != end; ++bucket) {
    struct link *link = bucket->first;
    while (link) {
      struct link *const next = link->next;
      free(link);
      link = next;
    }
  }
  free_xarray(set_i->buckets);
  free(set);
}

static struct list *
get_bucket(const struct set *const set, void *const key)
{
  return set->buckets + set->hash(key) % xarray_size(set->buckets);
}

static struct link *
get_link(
  const struct set  *const set,
  const struct list *const bucket,
  void              *const key)
{
  for (struct link *link = bucket->first; link; link = link->next)
    if (set->key_cmp(key, link->data, set->key_size)) return link;
  return NULL;
}

static inline size_t
expand_to(const size_t old_size)
{
  return 4*old_size;
}

static void
expand(struct set *const set)
{
  const size_t n_buckets     = xarray_size(set->buckets),
               new_n_buckets = expand_to(n_buckets);
  // Cache xarrays of link pointers to match the new buckets layout
  struct link ***const new_lists =
    malloc(sizeof (struct link ** [new_n_buckets]));
  for (size_t i = 0; i < new_n_buckets; ++i)
    new_lists[i] = load_xarray(0, sizeof *new_lists[i]);
  struct list *const end = set->buckets + n_buckets;
  for (struct list *bucket = set->buckets; bucket != end; ++bucket) {
    for (struct link *link = bucket->first; link; link = link->next) {
      const size_t i = set->hash(link->data) % (new_n_buckets);
      new_lists[i] = xarray_expand(new_lists[i]);
      new_lists[i][xarray_size(new_lists[i])-1] = link;
    }
  }
  // Re-form lists
  set->buckets = xarray_resize(set->buckets, new_n_buckets);
  for (size_t i = 0; i < new_n_buckets; ++i) {
    const size_t n_links = xarray_size(new_lists[i]);
    if (n_links) {
      set->buckets[i] = (struct list){
        .first = new_lists[i][0],
        .last  = new_lists[i][n_links-1]
      };
      for (size_t j = 0; j < n_links; ++j) {
        new_lists[i][j]->prev = j              ? new_lists[i][j-1] : NULL;
        new_lists[i][j]->next = j != n_links-1 ? new_lists[i][j+1] : NULL;
      }
    } else set->buckets[i] = (struct list){0};
    free_xarray(new_lists[i]);
  }
  free(new_lists);
}

DLL_LOCAL void *
set_insert(void *const set, void *const key)
{
  struct set *const set_i = set;
  if ((set_i->size + 1)*EXPAND_RATIO/xarray_size(set_i->buckets)) expand(set);
  struct list *const bucket = get_bucket(set_i, key);
  struct link *const last_link = bucket->last,
              *const new_link = malloc(sizeof (struct link) + set_i->key_size);
  new_link->next = NULL;
  new_link->prev = last_link;
  memcpy(new_link->data, key, set_i->key_size);
  bucket->last = new_link;
  if (!last_link) bucket->first = new_link;
  else last_link->next = new_link;
  ++set_i->size;
  return new_link->data;
}

DLL_LOCAL void *
set_get(void *const set, void *const key)
{
  struct link *const link = get_link(set, get_bucket(set, key), key);
  return link ? link->data : NULL;
}

static void
remove_link(
  struct set  *const set,
  struct link *const link,
  struct list *const bucket)
{
  struct link *const prev = link->prev,
              *const next = link->next;
  if (prev) prev->next = next;
  else bucket->first = next;
  if (next) next->prev = prev;
  else bucket->last = prev;
  free(link);
  --set->size;
}

DLL_LOCAL void
set_remove(void *const set, void *const key)
{
  struct list *const bucket = get_bucket(set, key);
  remove_link(set, get_link(set, bucket, key), bucket);
}

DLL_LOCAL void
set_remove_at(void *const set, void *const ptr)
{
  remove_link(
    set,
    (void *)((unsigned char *)ptr - offsetof(struct link, data)),
    get_bucket(set, ptr)
  );
}

DLL_LOCAL size_t
set_size(const void *const set)
{
  return ((const struct set *)set)->size;
}

DLL_LOCAL _Bool
set_memcmp(
  const void   *const key_1,
  const void   *const key_2,
  const size_t key_size)
{
  return !memcmp(key_1, key_2, key_size);
}

// 64-bit FNV-1a hash

#define FNV_1A_INIT 0xcbf29ce484222325ull
#define FNV_1A_PRIME 0x100000001b3ull

static inline size_t
hash_fnv_1a(const char *const str)
{
  size_t result = FNV_1A_INIT;
  for (size_t i = 0; str[i]; ++i) {
    result ^= str[i];
    result *= FNV_1A_PRIME;
  }
  return result;
}

DLL_LOCAL size_t
set_str_hash(const void *const str)
{
  return hash_fnv_1a(*(char *const *)str);
}

DLL_LOCAL size_t
set_str_hash_in_place(const void *const str)
{
  return hash_fnv_1a(str);
}
