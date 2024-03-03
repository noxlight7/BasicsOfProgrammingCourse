//
// Created by curo on 16.02.2024.
//

#include "vector_void.h"
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "array/array.h"

void* getAddress(vectorVoid* v, size_t index){
    return ((char*) v->data) + index * v->baseTypeSize;
}

vectorVoid createVectorV(size_t capacity, size_t baseTypeSize){
    vectorVoid vec;
    vec.size = 0;
    vec.capacity = capacity;
    vec.baseTypeSize = baseTypeSize;

    if (capacity) {
        vec.data = malloc(capacity * baseTypeSize);
        if (vec.data == NULL){
            fprintf(stderr, "bad alloc");
            exit(1);
        }
    }
    else{
        vec.data = NULL;
    }

    return vec;
}

vectorVoid createVectorFromArrayV(void* a, size_t n, size_t baseTypeSize){
    vectorVoid v = createVectorV(n, baseTypeSize);
    memcpy(v.data, a, n * baseTypeSize);
    v.size = n;
    return v;
}

void reserveV(vectorVoid *v, size_t newCapacity){
    if (newCapacity){
        if (v->data == NULL){
            v->data = malloc(newCapacity * v->baseTypeSize);
        }
        else {
            int *data = realloc(v->data, newCapacity * v->baseTypeSize);

            if (data == NULL) {
                fprintf(stderr, "bad alloc");
                exit(1);
            }

            if (data != v->data) {
                memcpy(data, v->data, v->size * v->baseTypeSize);
                free(v->data);
                v->data = data;
            }

            if (v->size > newCapacity)
                v->size = newCapacity;
        }

        v->capacity = newCapacity;
    }
    else{
        v->size = 0;
        v->capacity = 0;
        v->data = NULL;
    }
}

void clearV(vectorVoid *v){
    v->size = 0;
}

void shrinkToFitV(vectorVoid *v){
    reserveV(v, v->size);
}

void deleteVectorV(vectorVoid *v){
    if (v->data != NULL) {
        free(v->data);
        v->data = NULL;
        v->size = 0;
        v->capacity = 0;
    }
}

bool isEmptyV(vectorVoid *v){
    return v->size == 0;
}

bool isFullV(vectorVoid *v){
    return v->size == v->capacity;
}

void getVectorValueV(vectorVoid *v, size_t i, void *x){
    memcpy(x, getAddress(v, i), v->baseTypeSize);
}

void setVectorValueV(vectorVoid *v, size_t i, void *x){
    memcpy(getAddress(v, i), x,  v->baseTypeSize);
}

void pushBackV(vectorVoid *v, void* x){
    if (isFullV(v)){
        if (v->capacity)
            reserveV(v, v->capacity << 1);
        else
            reserveV(v, 1);
    }


    setVectorValueV(v, v->size++, x);
}

void popBackV(vectorVoid *v){
    if (v->size > 0) {
        fprintf(stderr, "vectorVoid is empty");
        exit(1);
    }

    v->size--;
}

void* atVectorV(vectorVoid *v, size_t index){
    if (index >= v->size){
        fprintf(stderr, "IndexError: a[%zu] is not exists", index);
        exit(1);
    }

    return getAddress(v, index);
}

void* backV(vectorVoid *v){
    return getAddress(v, v->size);
}

void* frontV(vectorVoid *v){
    return v->data;
}
