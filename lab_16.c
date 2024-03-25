//
// Created by curo on 22.03.2024.
//
#include "matrix/matrix.h"
#include "array/array.h"
#include <assert.h>
#include <limits.h>
#include <math.h>

long long findSumOfMaxesOfPseudoDiagonal(matrix m){

    int diag_amount = m.nRows + m.nCols - 1;
    int max_diag[diag_amount];
    for (int i = 0; i < diag_amount; ++i) {
        max_diag[i] = INT_MIN;
    }

    int shift = m.nCols - 1;

    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        for (int column_index = 0; column_index < m.nCols; ++column_index) {
            int index = row_index - column_index + shift;
            max_diag[index] = max2at(max_diag[index], m.values[row_index][column_index]);
        }
    }

    return getSumL(max_diag, diag_amount) - max_diag[shift];
}

void swapRowsWithMinMax(matrix m){
    swapRows(m, getMaxValuePos(m).rowIndex, getMinValuePos(m).rowIndex);
}

void getSquareOfMatrixIfSymmetric(matrix *m){
    if (isSymmetricMatrix(m)){
        matrix t = mulMatrices(*m, *m);
        freeMemMatrix(m);
        *m = t;
    }
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix *m){
    long long row_sums[m->nRows];
    fillRowCriteriaArrayL(*m, row_sums, getSumL);
    if (isUnique(row_sums, m->nRows))
        transposeMatrix(m);

}

int getMinInArea(matrix m){
    position max_pos = getMaxValuePos(m);

    int min = m.values[max_pos.rowIndex][max_pos.colIndex];
    for (int row_index = 0; row_index < max_pos.rowIndex; ++row_index) {
        int end_index = minInt(max_pos.colIndex - row_index + max_pos.rowIndex + 1, m.nCols);
        for (int col_index = maxInt(max_pos.colIndex + row_index - max_pos.rowIndex, 0);
                 col_index < end_index; ++col_index) {
            min = minInt(min, m.values[row_index][col_index]);
        }
    }

    return min;
}

float getDistance(int *a, int n){
    float dist = 0;

    for (int i = 0; i < n; ++i) {
        dist += (float) a[i] * (float) a[i];
    }

    return sqrtf(dist);
}

void sortByDistances(matrix m){
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}



void test_sortByDistances() {
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            -2, -2, -4,
                            2, -2, 1,
                            0, 3, -4,
                            100, 9, -3,
                    },
            4, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            2, -2, 1,
                            -2, -2, -4,
                            0, 3, -4,
                            100, 9, -3,
                    },
            4, 3
    );

    sortByDistances(m1);
    assert(areTwoMatricesEqual(&m1, &m2));
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

int countIntElementsOrdered(long long *a, int n){
    if (n == 0)
        return 0;

    int counter = 1;
    int current = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] != current){
            current = a[i];
            counter++;
        }
    }
    return counter;
}

int countEqClassesByRowsSum(matrix m){
    long long row_sums[m.nRows];
    fillRowCriteriaArrayL(m, row_sums, getSumL);
    shellSortLL(row_sums, m.nRows);

    return countIntElementsOrdered(row_sums, m.nRows);
}

void test_countEqClassesByRowsSum() {
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            2, -1, 7,
                            -3, 3, 4,
                            5, 1, 2,
                            -2, 9, -3,
                            0, -1, -3,
                    },
            5, 3
    );

    assert(countEqClassesByRowsSum(m1) == 3);
    freeMemMatrix(&m1);

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            7, 1,
                            2, 7,
                            5, 4,
                            4, 3,
                            1, 6,
                            8, 0
                    },
            6, 2
    );

    assert(countEqClassesByRowsSum(m2) == 3);
    freeMemMatrix(&m2);
}

void test_getMinInArea() {
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            2, 5, 7,
                            6, 3, 4,
                            5, 1, 2,
                            -2, 9, -3,
                            0, -1, -3,
                    },
            5, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            2, 5, 7, 5, 8,
                            6, 3, 4, 6, 10,
                            5, 1, 2, 3, 2
                    },
            3, 5
    );

    assert(getMinInArea(m1) == 1);
    assert(getMinInArea(m2) == 5);
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_findSumOfMaxesOfPseudoDiagonal() {
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            2, 5, 7,
                            6, 3, 4,
                            5, -2, -3,
                            -2, -2, -3,
                            0, -1, -3,
                    },
            5, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            3, 2, 5, 4,
                            1, 3, 6, 3,
                            3, 2, 1, 2
                    },
            3, 4
    );

    assert(findSumOfMaxesOfPseudoDiagonal(m1) == 22);
    assert(findSumOfMaxesOfPseudoDiagonal(m2) == 20);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_isMutuallyInverseMatrices() {
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            2, 5, 7,
                            6, 3, 4,
                            5, -2, -3
                    },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            1, -1, 1,
                            -38, 41, -34,
                            27, -29, 24
                    },
            3, 3
    );
    assert(isMutuallyInverseMatrices(m1, m2));
}

void test_transposeIfMatrixHasNotEqualSumOfRows(){
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            2, 3, 9, 5,
                            3, 5, 6, 3,
                            9, 6, 6, 5
                    },
            3, 4
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            2, 3, 9,
                            3, 5, 6,
                            9, 6, 6,
                            5, 3, 5
                    },
            4, 3
    );

    transposeIfMatrixHasNotEqualSumOfRows(&m1);
    assert(areTwoMatricesEqual(&m1, &m2));

    matrix m3 = createMatrixFromArray(
            (int[])
                    {
                            8, 3, 1,
                            3, 5, 4,
                            2, 4, 6
                    },
            3, 3
    );

    matrix m4 = createMatrixFromArray(
            (int[])
                    {
                            8, 3, 1,
                            3, 5, 4,
                            2, 4, 6
                    },
            3, 3
    );

    transposeIfMatrixHasNotEqualSumOfRows(&m3);
    assert(areTwoMatricesEqual(&m3, &m4));
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    freeMemMatrix(&m3);
    freeMemMatrix(&m4);
}

void test_getSquareOfMatrixIfSymmetric(){
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            2, 3, 9,
                            3, 5, 6,
                            9, 6, 6
                    },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            94, 75, 90,
                            75, 70, 93,
                            90, 93, 153,
                    },
            3, 3
    );

    matrix m3 = createMatrixFromArray(
            (int[])
                    {
                            2, 3, 9,
                            3, 5, 6,
                            1, 6, 6
                    },
            3, 3
    );

    matrix m4 = createMatrixFromArray(
            (int[])
                    {
                            2, 3, 9,
                            3, 5, 6,
                            1, 6, 6
                    },
            3, 3
    );

    getSquareOfMatrixIfSymmetric(&m1);
    getSquareOfMatrixIfSymmetric(&m3);
    assert(areTwoMatricesEqual(&m1, &m2));
    assert(areTwoMatricesEqual(&m3, &m4));
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

void test_sortRowsByMinElement(){
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
                            2, 3, 9,
                            4, 5, 6,
                    },
            3, 3
    );

    sortRowsByMinElement(m1);
    assert(areTwoMatricesEqual(&m1, &m2));
}

void test_sortRowsByMaxElement(){
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            2, 3, 9,
                            4, 5, 6,
                            1, 3, 10
                    },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            4, 5, 6,
                            2, 3, 9,
                            1, 3, 10,

                    },
            3, 3
    );

    sortRowsByMaxElement(m1);
    assert(areTwoMatricesEqual(&m1, &m2));
}

void test_sortColsByMinElement() {
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            3, 4, 9,
                            5, 2, 6,
                            3, 1, 10
                    },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            4, 3, 9,
                            2, 5, 6,
                            1, 3, 10,

                    },
            3, 3
    );

    sortColsByMinElement(m1);
    assert(areTwoMatricesEqual(&m1, &m2));
}

void test_sortColsByMaxElement(){
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            9, 3, 2,
                            6, 5, 4,
                            10, 3, 1
                    },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            2, 3, 9,
                            4, 5, 6,
                            1, 3, 10
                    },
            3, 3
    );

    sortColsByMaxElement(m1);
    assert(areTwoMatricesEqual(&m1, &m2));
}

void test_lab_16_all(){
    test_swapRowsWithMinMax();
    test_sortRowsByMinElement();
    test_sortRowsByMaxElement();
    test_sortColsByMaxElement();
    test_sortColsByMinElement();
    test_getSquareOfMatrixIfSymmetric();
    test_transposeIfMatrixHasNotEqualSumOfRows();
    test_isMutuallyInverseMatrices();
    test_findSumOfMaxesOfPseudoDiagonal();
    test_getMinInArea();
    test_sortByDistances();
    test_countEqClassesByRowsSum();
}