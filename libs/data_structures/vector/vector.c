//
// Created by curo on 16.02.2024.
//

#include "vector.h"
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

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
}

void reserve(vector *v, size_t newCapacity){
    if (newCapacity){
        int *data = realloc(v->data, newCapacity * sizeof(int));

        if (data == NULL){
            fprintf(stderr, "bad alloc");
            exit(1);
        }

        if (data != v->data){
            memcpy(data, v->data, v->size * sizeof(int));
            free(v->data);
            v->data = data;
        }

        v->capacity = newCapacity;

        if (v->size > newCapacity)
            v->size = newCapacity;
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
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}