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

void test_atVector_notEmptyVector(){
    int input_array[] = {4, 6};
    vector v = createVectorFromArray(input_array, 2);
    reserve(&v, 5);
    assert(*atVector(&v, 1) == 6);
}

void test_atVector_requestToLastElement(){
    int input_array[] = {4, 6, 7};
    vector v = createVectorFromArray(input_array, 2);
    reserve(&v, 5);
    assert(*atVector(&v, 1) == 6);
}

void test_back_oneElementInVector(){
    int input_array[] = {4, 6, 7};
    vector v = createVectorFromArray(input_array, 2);
    assert(*back(&v) == 7);
}

void test_front_oneElementInVector(){
    int input_array[] = {4, 6, 7};
    vector v = createVectorFromArray(input_array, 2);
    assert(*front(&v) == 4);
}

void test_vector(){
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_popBack_notEmptyVector();
    test_atVector_notEmptyVector();
    test_atVector_requestToLastElement();
}