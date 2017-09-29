#include <stddef.h>
#include <stdalign.h>
#include <stdlib.h>

#include "xarray.h"

#define MAX(a, b) ((a) >= (b) ? (a) : (b))

struct xarray {
  size_t size, capacity;
  alignas(max_align_t) unsigned char mem[];
};

void *
load_xarray_impl(const size_t element_size, const size_t start_size)
{
  struct xarray *const xarray = calloc(
    1, sizeof (struct xarray) + start_size*element_size
  );
  xarray->capacity = xarray->size = start_size;
  return xarray->mem;
}

static inline struct xarray *
get_internals(void *xarray)
{
  return (void *)((unsigned char *)xarray - (offsetof(struct xarray, mem)));
}

void *
xarray_expand_impl(void *xarray, const size_t element_size)
{
  struct xarray *internals = get_internals(xarray);
  if (++internals->size > internals->capacity) {
    internals->capacity = MAX(2 * internals->capacity, 1);
    internals = realloc(
      internals, sizeof (struct xarray) + internals->capacity*element_size
    );
    xarray = internals->mem;
  }
  return xarray;
}

void *
xarray_resize_impl(void *xarray, const size_t element_size, size_t new_size)
{
  struct xarray *internals = get_internals(xarray);
  internals->size = new_size;
  if (new_size > internals->capacity) {
    internals->capacity = MAX(new_size, 2 * internals->capacity);
    internals = realloc(
      internals, sizeof (struct xarray) + internals->capacity*element_size
    );
    xarray = internals->mem;
  }
  return xarray;
}

size_t
xarray_size(void *xarray)
{
  return get_internals(xarray)->size;
}

void
free_xarray(void *xarray)
{
  free(get_internals(xarray));
}