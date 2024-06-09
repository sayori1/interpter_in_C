#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

typedef struct
{
    void **data;
    int size;
    int capacity;
} Array;

Array *arrayCreate(int capacity, size_t size)
{
    Array *array = (Array *)malloc(sizeof(Array));
    array->data = (void **)malloc(size * capacity);
    array->size = 0;
    array->capacity = capacity;
    return array;
}

void arrayPush(Array *array, void *element, size_t size)
{
    if (array->size >= array->capacity)
    {
        array->capacity *= 2;
        array->data = (void **)realloc(array->data, size * array->capacity);
    }
    array->data[array->size] = element;
    array->size++;
}

void *arrayGet(Array *array, int index)
{
    if (index < 0 || index >= array->size)
    {
        return NULL;
    }
    return array->data[index];
}

void arraySet(Array *array, int index, void *element)
{
    if (index < 0 || index >= array->size)
    {
        return;
    }
    array->data[index] = element;
}

void arrayRemove(Array *array, int index)
{
    if (index < 0 || index >= array->size)
    {
        return;
    }
    for (int i = index; i < array->size - 1; i++)
    {
        array->data[i] = array->data[i + 1];
    }
    array->size--;
}

void arrayFree(Array *array)
{
    free(array->data);
    free(array);
}

int arrayFind(Array *array, int (*compare)(void *))
{
    for (int i = 0; i < array->size; i++)
    {
        if (compare(array->data[i]))
        {
            return i;
        }
    }
    return -1;
}

Array *arrayMap(Array *array, void (*map)(void *))
{
    Array *newArray = arrayCreate(array->capacity, sizeof(void *));
    for (int i = 0; i < array->size; i++)
    {
        map(array->data[i]);
        arrayPush(newArray, array->data[i], sizeof(void *));
    }
    return newArray;
}

#endif // !ARRAY_H