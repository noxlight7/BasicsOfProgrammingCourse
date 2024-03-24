//
// Created by curo on 02.03.2024.
//

#include "matrix.h"
#include <malloc.h>
#include <string.h>
#include "array/array.h"

matrix getMemMatrix(int nRows, int nCols){
    matrix m;
    m.nCols = nCols;
    m.nRows = nRows;
    m.values = (int**) malloc(nRows * sizeof(int*));

    for (int row_index = 0; row_index < nRows; ++row_index)
        m.values[row_index] = (int*) malloc(nCols * sizeof(int));

    return m;
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols){
    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);

    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);

    return ms;
}

void freeMemMatrix(matrix *m){
    for (int row_index = 0; row_index < m->nRows; ++row_index)
        free(m->values[row_index]);

    free(m->values);
    m->nRows = 0;
    m->nCols = 0;
}

void freeMemMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; ++i)
        freeMemMatrix(ms + i);
}

void inputMatrix(matrix *m){
    for (int row_index = 0; row_index < m->nRows; ++row_index)
        for (int col_index = 0; col_index < m->nCols; ++col_index)
            scanf("%i", m->values[row_index] + col_index);
}

void inputMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; ++i)
        inputMatrix(ms + i);
}

void outputMatrix(matrix m){
    printf("%d %d\n", m.nRows, m.nCols);
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        outputArray(m.values[row_index], m.nCols, ", ");
    }
}

void outputMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; ++i)
        outputMatrix(ms[i]);
}

void inputMatrixF(matrix *m, FILE* f){
    for (int row_index = 0; row_index < m->nRows; ++row_index)
        for (int col_index = 0; col_index < m->nCols; ++col_index)
            fscanf(f, "%i", m->values[row_index] + col_index);
}

void inputMatrixFBin(matrix *m, FILE* f){
    for (int row_index = 0; row_index < m->nRows; ++row_index)
        fread(m->values[row_index], sizeof(int), m->nCols, f);
}

void inputMatricesF(matrix *ms, int nMatrices, FILE* f){
    for (int i = 0; i < nMatrices; ++i)
        inputMatrixF(ms + i, f);
}

matrix createMatrixF(FILE* f){
    int rows_amount, columns_amount;
    fscanf(f, "%i%i", &rows_amount, &columns_amount);

    matrix m = getMemMatrix(rows_amount, columns_amount);
    inputMatrixF(&m, f);
    return m;
}

matrix createMatrixFBin(FILE* f){
    int rows_amount, columns_amount;
    fread(&rows_amount, sizeof (int), 1, f);
    fread(&columns_amount, sizeof (int), 1, f);

    matrix m = getMemMatrix(rows_amount, columns_amount);
    inputMatrixFBin(&m, f);
    return m;
}

matrix createMatrixSquareFBin(FILE* f){
    int n;
    fread(&n, sizeof (int), 1, f);

    matrix m = getMemMatrix(n, n);
    inputMatrixFBin(&m, f);
    return m;
}

matrix createMatrixSquareF(FILE* f){
    int n;
    fscanf(f, "%i", &n);

    matrix m = getMemMatrix(n, n);
    inputMatrixF(&m, f);
    return m;
}

matrix* createArrayOfMatricesF(FILE* f, int *n){
    fscanf(f, "%d", n);

    matrix *ms = malloc(*n * sizeof (matrix));
    for (int i = 0; i < *n; ++i) {
        ms[i] = createMatrixF(f);
    }

    return ms;
}

matrix* createArrayOfMatricesSquareF(FILE* f, int *n){
    fscanf(f, "%d", n);

    matrix *ms = malloc(*n * sizeof (matrix));
    for (int i = 0; i < *n; ++i) {
        ms[i] = createMatrixSquareF(f);
    }

    return ms;
}

matrix* createArrayOfMatricesSquareFBin(FILE* f, int *n){
    fread(n, sizeof (int), 1, f);

    matrix *ms = malloc(*n * sizeof (matrix));
    for (int i = 0; i < *n; ++i) {
        ms[i] = createMatrixSquareFBin(f);
    }

    return ms;
}

void outputMatrixF(matrix m, FILE* f){
    fprintf(f, "%d %d\n", m.nRows, m.nCols);
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        outputArrayF(m.values[row_index], m.nCols, " ", f);
    }
}

void outputMatrixSquareF(matrix m, FILE* f){
    fprintf(f, "%d\n", m.nRows);
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        outputArrayF(m.values[row_index], m.nCols, " ", f);
    }
}

void outputMatricesSquareF(matrix *ms, int nMatrices, FILE* f){
    fprintf(f, "%d\n", nMatrices);
    for (int i = 0; i < nMatrices; ++i)
        outputMatrixSquareF(ms[i], f);
}

void outputMatrixSquareFBin(matrix m, FILE* f){
    fwrite(&m.nRows, sizeof (int), 1, f);
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        fwrite(m.values[row_index], sizeof (int), m.nCols, f);
    }
}

void outputMatricesSquareFBin(matrix *ms, int nMatrices, FILE* f){
    fwrite(&nMatrices, sizeof (int), 1, f);
    for (int i = 0; i < nMatrices; ++i)
        outputMatrixSquareFBin(ms[i], f);
}

void swapRows(matrix m, int i1, int i2){
    int *t = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = t;
}

void swapColumns(matrix m, int j1, int j2){
    for (int row_index = 0; row_index < m.nRows; ++row_index)
        swap(&m.values[row_index][j1], &m.values[row_index][j2]);
}

void fillRowCriteriaArray(matrix m, int* criteria_array, int (*criteria)(int*, int)){
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        criteria_array[row_index] = criteria(m.values[row_index], m.nCols);
    }
}

void fillRowCriteriaArrayL(matrix m,
                           long long* criteria_array,
                           long long (*criteria)(int*, int)){
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        criteria_array[row_index] = criteria(m.values[row_index], m.nCols);
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)){
    int* criteria_array = (int *) malloc(m.nRows * sizeof(int));

    fillRowCriteriaArray(m, criteria_array, criteria);

    shellSortIntCriteriaArray(criteria_array, m.values, sizeof (int*), m.nRows);

    free(criteria_array);
}

void columnToArray(matrix m, int column_index, int* dst){
    for (int row_index = 0; row_index < m.nRows; ++row_index)
        dst[row_index] = m.values[row_index][column_index];
}

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int)){
    int* criteria_array = (int *) malloc(m.nCols * sizeof(int));
    int *temp_col = (int *) malloc(m.nRows * sizeof(int));

    for (int column_index = 0; column_index < m.nCols; ++column_index) {
        columnToArray(m, column_index, temp_col);
        criteria_array[column_index] = criteria(temp_col, m.nRows);
    }

    for (int i = m.nCols - 1; i > 0; i--) {
        int max = (int) findMaxUnsortedIndex(criteria_array, i + 1);
        if (max != i) {
            swap(criteria_array + max, criteria_array + i);
            swapColumns(m, max, i);
        }
    }

    free(criteria_array);
    free(temp_col);
}

bool isSquareMatrix(matrix *m){
    return m->nCols == m->nRows;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2){
    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols)
        return false;

    for (int row_index = 0; row_index < m1->nRows; ++row_index)
        if(!isEqual(m1->values[row_index], m2->values[row_index], m1->nCols))
            return false;

    return true;
}

bool isEMatrix(matrix *m){
    if(!isSquareMatrix(m))
        return false;

    for (int row_index = 0; row_index < m->nRows; ++row_index)
        for (int column_index = 0; column_index < m->nCols; ++column_index)
            if (m->values[row_index][column_index] != (row_index == column_index))
                return false;

    return true;
}

bool isSymmetricMatrix(matrix *m){
    if(!isSquareMatrix(m))
        return false;

    for (int diagonal_index = 1; diagonal_index < m->nCols; ++diagonal_index)
        for (int i = 0; i < diagonal_index; i++)
            if (m->values[i][diagonal_index] != m->values[diagonal_index][i])
                return false;

    return true;
}

void transposeSquareMatrix(matrix *m){
    if(!isSquareMatrix(m))
        return;

    for (int diagonal_index = 1; diagonal_index < m->nCols; ++diagonal_index)
        for (int i = 0; i < diagonal_index; i++)
            swap(&m->values[i][diagonal_index], &m->values[diagonal_index][i]);
}

void transposeMatrix(matrix *m){
    if(isSquareMatrix(m))
        transposeSquareMatrix(m);
    else{
        matrix new_m = getMemMatrix(m->nCols, m->nRows);
        for (int column_index = 0; column_index < m->nCols; column_index++)
            columnToArray(*m, column_index, new_m.values[column_index]);

        freeMemMatrix(m);
        memcpy(m, &new_m, sizeof(matrix));
    }
}

position getMinValuePos(matrix m){
    position min_pos = {0, (int) findMinUnsortedIndex(m.values[0], m.nCols)};
    int min_el = m.values[min_pos.rowIndex][min_pos.colIndex];

    for(int row_index = 0; row_index < m.nRows; row_index++) {
        int cur_min_col = (int) findMinUnsortedIndex(m.values[row_index], m.nCols);
        int cur_min_el = m.values[row_index][cur_min_col];

        if (min_el > cur_min_el){
            min_pos.rowIndex = row_index;
            min_pos.colIndex = cur_min_col;
            min_el = cur_min_el;
        }
    }

    return min_pos;
}

position getMaxValuePos(matrix m){
    position max_pos = {0, (int) findMaxUnsortedIndex(m.values[0], m.nCols)};
    int max_el = m.values[max_pos.rowIndex][max_pos.colIndex];

    for(int row_index = 0; row_index < m.nRows; row_index++) {
        int cur_max_col = (int) findMaxUnsortedIndex(m.values[row_index], m.nCols);
        int cur_max_el = m.values[row_index][cur_max_col];

        if (max_el < cur_max_el){
            max_pos.rowIndex = row_index;
            max_pos.colIndex = cur_max_col;
            max_el = cur_max_el;
        }
    }

    return max_pos;
}

matrix createMatrixFromArray(const int *a, int nRows, int nCols) {
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}

int countZeroRows(matrix m){
    int zero_rows_amount = 0;
    for (int row_index = 0; row_index < m.nRows; ++row_index)
        zero_rows_amount += isZero(m.values[row_index], m.nCols);

    return zero_rows_amount;
}

matrix *createArrayOfMatrixFromArray(const int *values,
                                     size_t nMatrices, size_t nRows, size_t nCols) {
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;
    for (size_t k = 0; k < nMatrices; k++)
        for (size_t i = 0; i < nRows; i++)
            for (size_t j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];
    return ms;
}

void sortRowsByMinElement(matrix m){
    insertionSortRowsMatrixByRowCriteria(m, getMin);
}

void sortRowsByMaxElement(matrix m){
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}

void sortColsByMinElement(matrix m){
    selectionSortColsMatrixByColCriteria(m, getMin);
}

void sortColsByMaxElement(matrix m){
    selectionSortColsMatrixByColCriteria(m, getMax);
}

matrix mulMatrices(matrix m1, matrix m2){
    if (m1.nCols != m2.nRows){
        fprintf(
                stderr,
                "matrices multiplication impossible: m1.nCols != m2.nRows");
        exit(1);
    }

    matrix res = getMemMatrix(m1.nRows, m2.nCols);
    for (int row_index = 0; row_index < res.nRows; ++row_index) {
        for (int col_index = 0; col_index < res.nCols; ++col_index) {
            int s = 0;
            for (int i = 0; i < m1.nRows; ++i) {
                s += m1.values[row_index][i] * m2.values[i][col_index];
            }
            res.values[row_index][col_index] = s;
        }
    }

    return res;
}

bool isMutuallyInverseMatrices(matrix m1, matrix m2){
    matrix res = mulMatrices(m1, m2);
    bool ret = isEMatrix(&res);
    freeMemMatrix(&res);

    return ret;
}
