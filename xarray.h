#ifndef XARRAY_H_INCLUDED
#define XARRAY_H_INCLUDED

#include <peg-lite.h>

// Creates new xarray with given element size, and starting array length
DLL_LOCAL void *
load_xarray(size_t start_size, size_t element_size);

// Sets size of xarray to new_size. Old array object may be invalidated/moved.
// Returns the new array object.
#define xarray_resize(xarray, new_size) \
  xarray_resize_impl(xarray, (sizeof *(xarray)), new_size)
DLL_LOCAL void *
xarray_resize_impl(void *xarray, size_t element_size, size_t new_size);

// Increases size of array by 1.
#define xarray_expand(xarray) xarray_expand_impl(xarray, sizeof *(xarray))
DLL_LOCAL void *
xarray_expand_impl(void *xarray, size_t element_size);

// Get current length of array.
DLL_LOCAL size_t
xarray_size(void *xarray);

// Deallocate array.
DLL_LOCAL void
free_xarray(void *xarray);

#endif // XARRAY_H_INCLUDED
