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

int getNSpecialElement(matrix m) {
    int counter = 0;
    for (int col_index = 0; col_index < m.nCols; ++col_index) {
        int max = m.values[0][col_index];
        int s = max;
        for (int row_index = 1; row_index < m.nRows; ++row_index) {
            s += m.values[row_index][col_index];
            max = maxInt(max, m.values[row_index][col_index]);
        }
        counter += (max << 1) > s;
    }

    return counter;
}

position getLeftMin(matrix m){
    position min_pos = {0, 0};
    int min_el = m.values[0][0];

    for(int col_index = 0; col_index < m.nCols; col_index++) {
        for (int row_index = 0; row_index < m.nRows; ++row_index) {
            if (min_el > m.values[row_index][col_index]){
                min_pos.rowIndex = row_index;
                min_pos.colIndex = col_index;
                min_el = m.values[row_index][col_index];
            }
        }
    }

    return min_pos;
}

void swapPenultimateRow(matrix m, int n){
    position min_pos = getLeftMin(m);
    int el = m.values[n][min_pos.colIndex];
    for (int i = 0; i < m.nCols; ++i)
        if (i == n)
            m.values[n][i] = el;
        else
            m.values[n][i] = m.values[i][min_pos.colIndex];
}

bool hasAllNonDescendingRows(matrix m){
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        if(!isSorted(m.values[row_index], m.nCols))
            return false;
    }

    return true;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix){
    int counter = 0;
    for (int i = 0; i < nMatrix; ++i) {
        counter += hasAllNonDescendingRows(ms[i]);
    }

    return counter;
}

void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix){
    int max = 0;
    int max_index = 0;
    for (int i = 0; i < nMatrix; ++i) {
        int current = countZeroRows(ms[i]);
        if (current > max) {
            max_index = i;
            max = current;
        }
    }

    outputMatrix(ms[max_index]);
}

int getMatrixNorm(matrix m){
    int max_abs = abs(m.values[0][0]);
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        for (int col_index = 0; col_index < m.nCols; ++col_index) {
            if (max_abs < abs(m.values[row_index][col_index]))
                max_abs = abs(m.values[row_index][col_index]);
        }
    }

    return max_abs;
}

void printMatrixWithMinNorm(matrix *ms, int n){
    int norms[n];
    int min_norm = getMatrixNorm(ms[0]);
    norms[0] = min_norm;

    for (int i = 1; i < n; ++i) {
        norms[i] = getMatrixNorm(ms[i]);
        if (min_norm > norms[i])
            min_norm = norms[i];
    }

    for (int i = 0; i < n; ++i) {
        if (norms[i] == min_norm) {
            outputMatrix(ms[i]);
        }
    }
}

void test_printMatrixWithMinNorm() {
    matrix m01 = createMatrixFromArray(
            (int[])
                    {
                            1, -2, 3,
                            -4, 5, 6,
                            1, -8, 1
                    },
            3, 3
    );

    matrix m02 = createMatrixFromArray(
            (int[])
                    {
                            0, 0, 0,
                            1, 4, -7,
                            -10, 8, -10
                    },
            3, 3
    );

    matrix m03 = createMatrixFromArray(
            (int[])
                    {
                            0, 0, 0,
                            0, 0, 0,
                            1, 2, 10
                    },
            3, 3
    );

    matrix m04 = createMatrixFromArray(
            (int[])
                    {
                            3, 0, 0,
                            0, 0, 3,
                            0, 0, 8
                    },
            3, 3
    );


    matrix ms1[] = {m01, m02, m03, m04};

    printMatrixWithMinNorm(ms1, 4);
    freeMemMatrix(&m01);
    freeMemMatrix(&m02);
    freeMemMatrix(&m03);
    freeMemMatrix(&m04);
}

void test_printMatrixWithMaxZeroRows() {
    matrix m01 = createMatrixFromArray(
            (int[])
                    {
                            1, 2, 3,
                            4, 5, 6,
                            1, 8, 1
                    },
            3, 3
    );

    matrix m02 = createMatrixFromArray(
            (int[])
                    {
                            0, 0, 0,
                            1, 4, 7,
                            10, 8, 10
                    },
            3, 3
    );

    matrix m03 = createMatrixFromArray(
            (int[])
                    {
                            0, 0, 0,
                            0, 0, 0,
                            1, 2, 10
                    },
            3, 3
    );

    matrix m04 = createMatrixFromArray(
            (int[])
                    {
                            0, 0, 0,
                            0, 0, 3,
                            0, 0, 10
                    },
            3, 3
    );

    matrix m11 = createMatrixFromArray(
            (int[])
                    {
                            0, 0, 0,
                            4, 5, 6,
                            7, 8, 1
                    },
            3, 3
    );

    matrix m12 = createMatrixFromArray(
            (int[])
                    {
                            0, 0, 0,
                            0, 4, 0,
                            0, 8, 0
                    },
            3, 3
    );

    matrix m13 = createMatrixFromArray(
            (int[])
                    {
                            0, 2, 3,
                            0, 2, 7,
                            1, 2, 10
                    },
            3, 3
    );

    matrix m14 = createMatrixFromArray(
            (int[])
                    {
                            0, 0, 0,
                            0, 0, 0,
                            0, 0, 0
                    },
            3, 3
    );

    matrix ms1[] = {m01, m02, m03, m04};
    matrix ms2[] = {m11, m12, m13, m14};

    printMatrixWithMaxZeroRows(ms1, 4);
    printMatrixWithMaxZeroRows(ms2, 4);
    freeMemMatrix(&m11);
    freeMemMatrix(&m12);
    freeMemMatrix(&m13);
    freeMemMatrix(&m14);
    freeMemMatrix(&m01);
    freeMemMatrix(&m02);
    freeMemMatrix(&m03);
    freeMemMatrix(&m04);
}

void test_countNonDescendingRowsMatrices() {
    matrix m01 = createMatrixFromArray(
            (int[])
                    {
                            1, 2, 3,
                            4, 5, 6,
                            1, 8, 1
                    },
            3, 3
    );

    matrix m02 = createMatrixFromArray(
            (int[])
                    {
                            1, 2, 3,
                            1, 4, 7,
                            10, 8, 10
                    },
            3, 3
    );

    matrix m03 = createMatrixFromArray(
            (int[])
                    {
                            1, 2, 3,
                            -1, -1, -1,
                            1, 2, 10
                    },
            3, 3
    );

    matrix m04 = createMatrixFromArray(
            (int[])
                    {
                            1, 2, 3,
                            3, 4, 3,
                            1, 2, 10
                    },
            3, 3
    );

    matrix m11 = createMatrixFromArray(
            (int[])
                    {
                            1, 2, 3,
                            4, 5, 6,
                            7, 8, 1
                    },
            3, 3
    );

    matrix m12 = createMatrixFromArray(
            (int[])
                    {
                            1, 2, 3,
                            1, 4, 7,
                            1, 8, 10
                    },
            3, 3
    );

    matrix m13 = createMatrixFromArray(
            (int[])
                    {
                            1, 2, 3,
                            0, 2, 7,
                            1, 2, 10
                    },
            3, 3
    );

    matrix m14 = createMatrixFromArray(
            (int[])
                    {
                            1, 2, 3,
                            3, 2, 7,
                            1, 2, 10
                    },
            3, 3
    );

    matrix ms2[] = {m11, m12, m13, m14};
    matrix ms1[] = {m01, m02, m03, m04};

    assert(countNonDescendingRowsMatrices( ms1, 4) == 1);
    assert(countNonDescendingRowsMatrices( ms2, 4) == 2);
    freeMemMatrix(&m11);
    freeMemMatrix(&m12);
    freeMemMatrix(&m13);
    freeMemMatrix(&m14);
    freeMemMatrix(&m01);
    freeMemMatrix(&m02);
    freeMemMatrix(&m03);
    freeMemMatrix(&m04);
}

void test_swapPenultimateRow() {
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            1, 2, 3,
                            4, 5, 6,
                            7, 8, 1
                    },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            1, 2, 3,
                            1, 4, 7,
                            7, 8, 1
                    },
            3, 3
    );

    swapPenultimateRow(m1, 1);
    assert(areTwoMatricesEqual(&m1, &m2));
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    matrix m3 = createMatrixFromArray(
            (int[])
                    {
                            2, -1, 7, 4,
                            -3, 3, 4, 5,
                            5, 1, 2, 6,
                            -2, 9, -4, 7,
                    },
            4, 4
    );

    matrix m4 = createMatrixFromArray(
            (int[])
                    {
                            2, -1, 7, 4,
                            -3, 3, 4, 5,
                            7, 4, 2, -4,
                            -2, 9, -4, 7,
                    },
            4, 4
    );
    swapPenultimateRow(m3, 2);

    assert(areTwoMatricesEqual(&m3, &m4));
    freeMemMatrix(&m3);
    freeMemMatrix(&m4);
}

void test_getNSpecialElement() {
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            2, -1, 7, 4,
                            -3, 3, 4, 5,
                            5, 1, 2, 6,
                            -2, 9, -3, 7,
                            0, -1, -3, 8,
                    },
            5, 4
    );

    assert(getNSpecialElement(m1) == 3);
    freeMemMatrix(&m1);

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            3, 5, 5, 4,
                            2, 3, 6, 7,
                            12, 2, 1, 2

                    },
            3, 4
    );
    assert(getNSpecialElement(m2) == 2);
    freeMemMatrix(&m2);
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
    test_getNSpecialElement();
    test_swapPenultimateRow();
    test_countNonDescendingRowsMatrices();
    test_printMatrixWithMaxZeroRows();
    test_printMatrixWithMinNorm();
}