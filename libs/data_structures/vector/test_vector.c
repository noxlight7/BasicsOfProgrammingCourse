//
// Created by curo on 16.02.2024.
//

#include <assert.h>
#include "test_vector.h"
#include "vector.h"
#include "../array/array.h"


void test_pushBack_emptyVector(){
    vector v = createVector(0);
    pushBack(&v, 5);
    assert(v.capacity == 1 && v.size == 1 && v.data[0] == 5);
}

void test_pushBack_fullVector(){
    int input_array[] = {4, 6};
    int output_array[] = {4, 6, 5};
    vector v = createVectorFromArray(input_array, 2);
    pushBack(&v, 5);
    assert(v.capacity == 4 && v.size == 3 && isEqual(v.data, output_array, v.size));

}

void test_popBack_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(v.size == 1);
    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
}

void test_vector(){
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_popBack_notEmptyVector();
}