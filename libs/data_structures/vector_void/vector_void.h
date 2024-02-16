#ifndef INC_VECTORVOID_H
#define INC_VECTORVOID_H

#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct vectorVoid {
    void *data;
// указатель на нулевой элемент вектора
    size_t size;
// размер вектора
    size_t capacity;
// вместимость вектора
    size_t baseTypeSize; // размер базового типа:
// например, если вектор хранит int -
// то поле baseTypeSize = sizeof(int)
// если вектор хранит float -
// то поле baseTypeSize = sizeof(float)
} vectorVoid;

// Создаёт пустой вектор максимальной вместимостью n
vectorVoid createVectorV(size_t capacity, size_t baseTypeSize);
// Создаёт вектор из массива a размера n
vectorVoid createVectorFromArrayV(void* a, size_t n, size_t baseTypeSize);
// Изменяет максимальную вместимость вектора на newCapacity
void reserveV(vectorVoid *v, size_t newCapacity);
// Очищает вектор от элементов
void clearV(vectorVoid *v);
// Устанавливает вместимость вектора количеством элементов в нём
void shrinkToFitV(vectorVoid *v);
// Очищает выделенную под вектор динамическую память
void deleteVectorV(vectorVoid *v);
// Возвращает true, если вектор пустой, иначе - false
bool isEmptyV(vectorVoid *v);
// Возвращает true, если размер вектора равен его
// максимальной вместимости, иначе - false
bool isFullV(vectorVoid *v);
// Записывает по адресу x i-й элемента вектора
void getVectorValueV(vectorVoid *v, size_t i, void *x);
// Записывает i-й элемент вектора элементом по адресу x
void setVectorValueV(vectorVoid *v, size_t i, void *x);
// Вставляет х в конец вектора v
void pushBackV(vectorVoid *v, void* x);
// Удаляет из вектора последний элемент и возвращает его
void popBackV(vectorVoid *v);
// Возвращает указатель на index-ный элемент
void* atVectorV(vectorVoid *v, size_t index);
// Возвращает указатель на последний элемент
void* backV(vectorVoid *v);
// Возвращает указатель на первый элемент
void* frontV(vectorVoid *v);

#endif