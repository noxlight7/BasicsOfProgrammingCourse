//
// Created by curo on 16.02.2024.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct vector {
    int *data;
// указатель на элементы вектора
    size_t size;
// размер вектора
    size_t capacity; // вместимость вектора
} vector;

vector createVector(size_t n);
vector createVectorFromArray(int* a, size_t n);

void reserve(vector *v, size_t newCapacity);

void clear(vector *v);

void shrinkToFit(vector *v);

void deleteVector(vector *v);

bool isEmpty(vector *v);

bool isFull(vector *v);

int getVectorValue(vector *v, size_t i);

void pushBack(vector *v, int x);

int popBack(vector *v);

#endif //VECTOR_H
