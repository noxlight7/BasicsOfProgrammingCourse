//
// Created by curo on 16.02.2024.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct vector {
    int *data;
// указатель на элементы вектора
    size_t size;
// размер вектора
    size_t capacity; // вместимость вектора
} vector;

vector createVector(size_t n);

void reserve(vector *v, size_t newCapacity);

void clear(vector *v);

void shrinkToFit(vector *v);

void deleteVector(vector *v);

#endif //BASICSOFPROGRAMMINGCOURSE_VECTOR_H
