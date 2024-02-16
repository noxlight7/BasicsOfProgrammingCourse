//
// Created by curo on 16.02.2024.
//

#include "vector.h"
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "../array/array.h"

vector createVector(size_t n){
    vector vec;
    vec.size = 0;
    vec.capacity = n;

    if (n) {
        vec.data = malloc(n * sizeof(int));
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

vector createVectorFromArray(int* a, size_t n){
    vector v = createVector(n);
    copy(v.data, a, n);
    v.size = n;
    return v;
}

void reserve(vector *v, size_t newCapacity){
    if (newCapacity){
        if (v->data == NULL){
            v->data = malloc(newCapacity * sizeof(int));
        }
        else {
            int *data = realloc(v->data, newCapacity * sizeof(int));

            if (data == NULL) {
                fprintf(stderr, "bad alloc");
                exit(1);
            }

            if (data != v->data) {
                memcpy(data, v->data, v->size * sizeof(int));
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

void clear(vector *v){
    v->size = 0;
}

void shrinkToFit(vector *v){
    reserve(v, v->size);
}

void deleteVector(vector *v){
    if (v->data != NULL) {
        free(v->data);
        v->data = NULL;
        v->size = 0;
        v->capacity = 0;
    }
}

bool isEmpty(vector *v){
    return v->size == 0;
}

bool isFull(vector *v){
    return v->size == v->capacity;
}

int getVectorValue(vector *v, size_t i){
    return v->data[i];
}

void pushBack(vector *v, int x){
    if (isFull(v)){
        if (v->capacity)
            reserve(v, v->capacity << 1);
        else
            reserve(v, 1);
    }

    v->data[v->size++] = x;
}

int popBack(vector *v){
    if (v->size)
        return v->data[--v->size];

    fprintf(stderr, "vector is empty");
    exit(1);
}

int* atVector(vector *v, size_t index){
    if (index >= v->size){
        fprintf(stderr, "IndexError: a[%zu] is not exists", index);
        exit(1);
    }

    return v->data + index;
}

int* back(vector *v){
    return v->data + v->size;
}

int* front(vector *v){
    return v->data;
}