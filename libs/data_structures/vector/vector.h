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
// Создаёт пустой вектор максимальной вместимостью n
vector createVector(size_t n);
// Создаёт вектор из массива a размера n
vector createVectorFromArray(int* a, size_t n);
// Изменяет максимальную вместимость вектора на newCapacity
void reserve(vector *v, size_t newCapacity);
// Очищает вектор от элементов
void clear(vector *v);
// Устанавливает вместимость вектора количеством элементов в нём
void shrinkToFit(vector *v);
// Очищает выделенную под вектор динамическую память
void deleteVector(vector *v);
// Возвращает true, если вектор пустой, иначе - false
bool isEmpty(vector *v);
// Возвращает true, если размер вектора равен его
// максимальной вместимости, иначе - false
bool isFull(vector *v);
// Возвращает значение i-го элемента вектора
int getVectorValue(vector *v, size_t i);
// Вставляет х в конец вектора v
void pushBack(vector *v, int x);
// Удаляет из вектора последний элемент и возвращает его
int popBack(vector *v);
// Возвращает указатель на index-ный элемент
int* atVector(vector *v, size_t index);
// Возвращает указатель на последний элемент
int* back(vector *v);
// Возвращает указатель на первый элемент
int* front(vector *v);

#endif //VECTOR_H
