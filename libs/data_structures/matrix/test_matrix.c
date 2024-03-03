//
// Created by curo on 03.03.2024.
//

#include "test_matrix.h"
#include <assert.h>
#include "matrix.h"
#include "array/array.h"

void test_matrix_count_zero_rows() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 1, 0,
                    0, 0, 0,
                    0, 0, 1,
                    0, 0, 0,
                    0, 1, 1,
            },
            5, 3
    );
    assert(countZeroRows(m) == 2);

    freeMemMatrix(&m);
}

void test_matrix_insertionSortRowsMatrixByRowCriteria(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    4, 5, 7,
                    0, 0, 0,
                    2, 3, 1,
                    2, 0, 1,
                    0, 1, 1,
            },
            5, 3
    );
    matrix res = createMatrixFromArray(
            (int[]) {

                    0, 0, 0,
                    0, 1, 1,
                    2, 0, 1,
                    2, 3, 1,
                    4, 5, 7,
            },
            5, 3
    );

    insertionSortRowsMatrixByRowCriteria(m, getSum);
    assert(areTwoMatricesEqual(&m, &res));

    freeMemMatrix(&m);
    freeMemMatrix(&res);
}

void test_matrix_selectionSortColsMatrixByColCriteria(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    7, 5, 4,
                    0, 0, 0,
                    1, 3, 2,
                    1, 0, 2,
                    1, 1, 0,
            },
            5, 3
    );
    matrix res = createMatrixFromArray(
            (int[]) {
                    4, 5, 7,
                    0, 0, 0,
                    2, 3, 1,
                    2, 0, 1,
                    0, 1, 1,
            },
            5, 3
    );

    selectionSortColsMatrixByColCriteria(m, getSum);
    assert(areTwoMatricesEqual(&m, &res));

    freeMemMatrix(&m);
    freeMemMatrix(&res);
}

void test_matrix_isEMatrix(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7, 5, 4,
                    0, 0, 0,
                    1, 3, 2,
            },
            3, 3
    );

    assert(!isEMatrix(&m1));

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1
            },
            4, 4
    );

    assert(isEMatrix(&m2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_matrix_isSymmetricMatrix(){
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7, 5, 4,
                    0, 0, 0,
                    1, 3, 2,
            },
            3, 3
    );

    assert(!isSymmetricMatrix(&m1));

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1
            },
            4, 4
    );

    assert(isSymmetricMatrix(&m2));

    matrix m3 = createMatrixFromArray(
            (int[]) {
                    1, 0, 9, 2,
                    0, 3, 1, 7,
                    9, 1, 5, 0,
                    2, 7, 0, 4
            },
            4, 4
    );

    assert(isSymmetricMatrix(&m3));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    freeMemMatrix(&m3);
}

void test_matrix_transposeMatrix(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    7, 5, 4,
                    0, 0, 0,
                    1, 3, 2,
                    1, 0, 2,
                    1, 1, 0,
            },
            5, 3
    );

    matrix res = createMatrixFromArray(
            (int[]) {
                    7, 0, 1, 1, 1,
                    5, 0, 3, 0, 1,
                    4, 0, 2, 2, 0,
            },
            3, 5
    );

    transposeMatrix(&m);

    assert(areTwoMatricesEqual(&m, &res));

    freeMemMatrix(&m);
    freeMemMatrix(&res);
}

void test_matrix_getMinMaxValuePos(){
    matrix m = createMatrixFromArray(
            (int[]) {
                    0, 5, 4,
                    -1, 0, 0,
                    1, 3, 0,
                    1, 0, 7,
                    1, 1, 0,
            },
            5, 3
    );

    position min_pos = getMinValuePos(m);
    assert(min_pos.rowIndex == 1 && min_pos.colIndex == 0);

    position max_pos = getMaxValuePos(m);
    assert(max_pos.rowIndex == 3 && max_pos.colIndex == 2);
}

void test_matrix_all(){
    test_matrix_count_zero_rows();
    test_matrix_insertionSortRowsMatrixByRowCriteria();
    test_matrix_selectionSortColsMatrixByColCriteria();
    test_matrix_isEMatrix();
    test_matrix_isSymmetricMatrix();
    test_matrix_transposeMatrix();
    test_matrix_getMinMaxValuePos();
}