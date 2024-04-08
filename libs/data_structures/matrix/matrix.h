//
// Created by curo on 02.03.2024.
//

#ifndef BASICSOFPROGRAMMINGCOURSE_MATRIX_H
#define BASICSOFPROGRAMMINGCOURSE_MATRIX_H

#include <stdbool.h>
#include <stdio.h>

typedef struct matrix {
    int **values; // элементы матрицы
    int nRows;
// количество рядов
    int nCols;
// количество столбцов
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

matrix getMemMatrix(int nRows, int nCols);
void zeroMatrix(matrix m);
matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);
matrix copyFromMatrix(matrix dst, matrix src);
matrix createMatrixF(FILE* f);
matrix createMatrixSquareF(FILE* f);
matrix* createArrayOfMatricesF(FILE* f, int *n);
matrix* createArrayOfMatricesSquareF(FILE* f, int *n);
matrix* createArrayOfMatricesSquareFBin(FILE* f, int *n);
void freeMemMatrix(matrix *m);
void freeMemMatrices(matrix *ms, int nMatrices);
void inputMatrix(matrix *m);
void inputMatrices(matrix *ms, int nMatrices);
void inputMatrixF(matrix *m, FILE* f);
void inputMatricesF(matrix *ms, int nMatrices, FILE* f);
void outputMatrixF(matrix m, FILE* f);
void outputMatricesF(matrix *ms, int nMatrices, FILE* f);
void outputMatrix(matrix m);
void outputMatrices(matrix *ms, int nMatrices);
void outputMatrixSquareF(matrix m, FILE* f);
void outputMatricesSquareF(matrix *ms, int nMatrices, FILE* f);
void outputMatricesSquareFBin(matrix *ms, int nMatrices, FILE* f);
void swapRows(matrix m, int i1, int i2);
void swapColumns(matrix m, int j1, int j2);
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int));
void insertionSortRowsMatrixByRowCriteriaF(matrix m, float (*criteria)(int *, int));
void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int));
bool isSquareMatrix(matrix *m);
bool areTwoMatricesEqual(matrix *m1, matrix *m2);
bool isEMatrix(matrix *m);
bool isSymmetricMatrix(matrix *m);
void transposeSquareMatrix(matrix *m);
void transposeMatrix(matrix *m);
position getMinValuePos(matrix m);
position getMaxValuePos(matrix m);
matrix createMatrixFromArray(const int *a, int nRows, int nCols);
int countZeroRows(matrix m);
matrix mulMatrices(matrix m1, matrix m2);
void fillRowCriteriaArray(matrix m, int* criteria_array, int (*criteria)(int*, int));
void fillRowCriteriaArrayL(matrix m,
                           long long* criteria_array,
                           long long (*criteria)(int*, int));

void sortRowsByMinElement(matrix m);
void sortRowsByMaxElement(matrix m);
void sortColsByMinElement(matrix m);
void sortColsByMaxElement(matrix m);
bool isMutuallyInverseMatrices(matrix m1, matrix m2);

int getMinInColumn(matrix m, int col_index, int row_start, int row_end);

#endif //BASICSOFPROGRAMMINGCOURSE_MATRIX_H
