#ifndef XARRAY_H_INCLUDED
#define XARRAY_H_INCLUDED

// Creates new xarray with given type, and starting size
#define load_xarray(type, start_size) load_xarray_impl(sizeof(type), start_size)
void *
load_xarray_impl(size_t element_size, size_t start_size);

// Sets size of xarray to new_size
#define xarray_resize(xarray, new_size) \
  xarray_resize_impl(xarray, (sizeof *(xarray)), new_size)
void *
xarray_resize_impl(void *xarray, size_t element_size, size_t new_size);

// Increases size of xarray by 1
#define xarray_expand(xarray) xarray_expand_impl(xarray, sizeof *(xarray))
void *
xarray_expand_impl(void *xarray, size_t element_size);

// Get length of xarray
size_t
xarray_size(void *xarray);

// Destroy xarray
void
free_xarray(void *xarray);

#endif // XARRAY_H_INCLUDED
