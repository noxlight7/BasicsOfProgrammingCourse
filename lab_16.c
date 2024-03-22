//
// Created by curo on 22.03.2024.
//
#include "matrix/matrix.h"
#include <assert.h>

void swapRowsWithMinMax(matrix m){
    swapRows(m, getMaxValuePos(m).rowIndex, getMinValuePos(m).rowIndex);
}

void test_swapRowsWithMinMax(){
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                         2, 3, 9,
                         4, 5, 6,
                         1, 3, 6
                     },
                     3, 3
            );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            1, 3, 6,
                            4, 5, 6,
                            2, 3, 9,
                     },
            3, 3
    );

    swapRowsWithMinMax(m1);
    assert(areTwoMatricesEqual(&m1, &m2));
}

void test_lab_16_all(){
    test_swapRowsWithMinMax();
}