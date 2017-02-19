#ifndef EMREGEX_DYNARRAY_H
#define EMREGEX_DYNARRAY_H

/// A dynamically-allocated, resizable, type-safe array type.
#define reDynArray(elemtype) elemtype##DynArray

/// Emits a definition of the array specialized for the given element type.
#define reDefineDynArrayOf(elemtype) typedef struct reDynArray(elemtype) { \
    elemtype* data; \
    int count; \
    int capacity; \
} reDynArray(elemtype)

/// Initializes a pre-allocated array with enough space to hold `initialCapacity`
/// elements.
#define reDynArrayInitWithCapacity(initialCapacity, array) do { \
    (array).data = malloc(initialCapacity * sizeof(*(array).data)); \
    (array).count = 0; \
    (array).capacity = initialCapacity; \
} while (0)

/// Appends the given element at the end of the array, reallocating if necessary.
#define reDynArrayPush(elem, array) do { \
    if ((array).count >= (array).capacity) { \
        (array).capacity = (array).capacity ? (array).capacity * 2 : 1; \
        (array).data = realloc((array).data, (array).capacity * sizeof(*(array).data)); \
        assert((array).data); \
    } \
    ((array).data[(array).count++]) = elem; \
} while (0)

/// Erases the element at the given index, shifting all elements after that
/// position back by one.
#define reDynArrayRemoveAt(index, array) do { \
    assert((index) >= 0 && (index) < (array).count); \
    int count = (array).count - (index) - 1; \
    memmove((array).data + (index), (array).data + (index) + 1, count * sizeof(*(array).data)); \
    (array).count--; \
} while (0)

/// Removes and returns the last element from the array.
#define reDynArrayPop(array) ((array).data[--(array).count])

#endif
