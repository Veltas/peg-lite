#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED

#include <peg-lite.h>

// Return hash of given key.
typedef size_t
(*set_hash)(const void *);

// Return whether inputs are 'comparable', is also given the element size.
typedef _Bool
(*set_key_cmp)(const void *, const void *, size_t);

// Create hash set, with given hash, comparison function, key size, and initial
// number of buckets.
DLL_LOCAL void *
load_set(set_hash hash, set_key_cmp cmp, size_t key_size, size_t n_buckets);

// Frees resources of set, and all stored keys.
DLL_LOCAL void
free_set(void *set);

// Inserts copy of key into set, returns stored copy.
DLL_LOCAL void *
set_insert(void *set, void *key);

// Returns pointer to the stored key, or NULL if comparable key not stored.
DLL_LOCAL void *
set_get(void *set, void *key);

// Removes comparable key. UB if no comparable key in set.
DLL_LOCAL void
set_remove(void *set, void *key);

// Removes given key, works with non-null results of set_get or set_insert. UB
// otherwise.
DLL_LOCAL void
set_remove_at(void *set, void *ptr);

// Gets the number of keys stored in the set.
DLL_LOCAL size_t
set_size(const void *set);

// Basic memcmp implementation of load_set's cmp argument. memcmp will not work
// on its own.
DLL_LOCAL _Bool
set_memcmp(const void *key_1, const void *key_2, size_t key_size);

// Provided implementation of string hash. Key is char*
DLL_LOCAL size_t
set_str_hash(const void *str);

// Provided implementation of string hash. Key is in-place char[n]
DLL_LOCAL size_t
set_str_hash_in_place(const void *str);

#endif // SET_H_INCLUDED
