//
// Created by curo on 03.04.2024.
//

#include <matrix/matrix.h>
#include "array/array.h"
#include <file/file.h>
#include <assert.h>
#include <vector_void/vector_void.h>
#include <string.h>
#include <signal.h>
#include <ncurses.h>


void lab20_task01(const char* read_file, const char* write_file){
    FILE *f = fopen(read_file, "r");

    int n, query_amount;
    fscanf(f, "%d%d", &n, &query_amount);

    matrix m = getMemMatrix(n, n);
    zeroMatrix(m);

    for (int i = 0; i < query_amount; ++i) {
        int row1, col1, row2, col2;
        fscanf(f, "%d%d%d%d", &row1, &col1, &row2, &col2);

        for (int row_index = row1; row_index <= row2; ++row_index) {
            for (int col_index = col1; col_index <= col2; ++col_index) {
                m.values[row_index][col_index]++;
            }
        }
    }

    fclose(f);

    f = fopen(write_file, "w");
    outputMatrixSquareF(m, f);
    fclose(f);

    freeMemMatrix(&m);
}

void test_lab20_01(){
    char lab20_task01_str[] = "3\n"
                              "2\n"
                              "1 1 2 2\n"
                              "0 0 1 1";

    char lab20_task01_out_str[] = "3\n"
                                  "1 1 0\n"
                                  "1 2 1\n"
                                  "0 1 1\n";

    const char read_file[] = "20_1_r.txt";
    const char write_file[] = "20_1_w.txt";
    writeAnyway(read_file, lab20_task01_str);
    lab20_task01(read_file, write_file);

    assert(cmpStrF(lab20_task01_out_str, write_file));
}

int countNeighbours(matrix m, int row_index, int col_index){
    int amount = 0;
    int row_border = m.nRows - 1;
    int col_border = m.nCols - 1;
    amount += row_index > 0 && m.values[row_index - 1][col_index] != 0;
    amount += row_index < row_border && m.values[row_index + 1][col_index] != 0;
    amount += col_index > 0 && m.values[row_index][col_index - 1] != 0;
    amount += col_index < col_border && m.values[row_index][col_index + 1] != 0;
    amount += col_index > 0 && row_index > 0 &&
            m.values[row_index - 1][col_index - 1] != 0;
    amount += col_index > 0 && row_index < row_border &&
              m.values[row_index + 1][col_index - 1] != 0;
    amount += col_index < col_border && row_index > 0 &&
              m.values[row_index - 1][col_index + 1] != 0;
    amount += col_index < col_border && row_index < row_border &&
              m.values[row_index + 1][col_index + 1] != 0;

    return amount;
}

void lab20_task02(const char* read_file, const char* write_file){
    FILE *f = fopen(read_file, "r");
    matrix source_matrix = createMatrixF(f);
    fclose(f);

    matrix new_matrix = {NULL, 0, 0};
    new_matrix = copyFromMatrix(new_matrix, source_matrix);

    for (int row_index = 0; row_index < source_matrix.nRows; ++row_index) {
        for (int col_index = 0; col_index < source_matrix.nCols; ++col_index) {
            int neighbours = countNeighbours(source_matrix, row_index, col_index);
            int old_value = source_matrix.values[row_index][col_index];
            int new_value;

            if (old_value == 1)
                new_value = neighbours == 2 || neighbours == 3;
            else
                new_value = neighbours == 3;

            new_matrix.values[row_index][col_index] = new_value;
        }
    }

    f = fopen(write_file, "w");
    outputMatrixF(new_matrix, f);
    fclose(f);

    freeMemMatrix(&new_matrix);
    freeMemMatrix(&source_matrix);
}

void test_lab20_02(){
    char lab20_task02_str[] = "4 3\n"
                              "0 1 0\n"
                              "0 0 1\n"
                              "1 1 1\n"
                              "0 0 0";

    char lab20_task02_out_str[] = "4 3\n"
                                  "0 0 0\n"
                                  "1 0 1\n"
                                  "0 1 1\n"
                                  "0 1 0\n";

    const char read_file[] = "20_2_r.txt";
    const char write_file[] = "20_2_w.txt";
    writeAnyway(read_file, lab20_task02_str);
    lab20_task02(read_file, write_file);

    assert(cmpStrF(lab20_task02_out_str, write_file));
}

int getMedian(matrix *m, int row_index, int col_index, int *buffer){
    row_index++;
    col_index++;
    int k = 0;
    for (int i = row_index - 2; i <= row_index; ++i) {
        for (int j = col_index - 2; j <= col_index; ++j) {
            buffer[k++] = m->values[i][j];
        }
    }

    shellSortInt(buffer, 9);

    return buffer[4];
}

void processFilterWindow(matrix m, position start, position end, int *buffer){
    for (int row_index = start.rowIndex + 1;
             row_index < end.rowIndex;
             ++row_index) {
        for (int col_index = start.colIndex + 1;
                 col_index < end.colIndex;
                 ++col_index) {
            m.values[row_index][col_index] =
                    getMedian(&m, row_index, col_index, buffer);
        }
    }
}

void lab20_task03(matrix m, int filter){
    int buffer[9];
    int k = filter - 1;
    for (int row_index = 0; row_index < m.nRows; row_index += filter) {
        for (int col_index = 0; col_index < m.nCols; col_index += filter) {
            processFilterWindow(
                    m,
                    (position) {row_index, col_index},
                    (position) {row_index + k, col_index + k},
                    buffer);
        }
    }
}

void test_lab20_03(){
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                            10, 20, 30,
                            25, 35, 45,
                            15, 25, 35
                    }, 3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            10, 20, 30,
                            25, 25, 45,
                            15, 25, 35
                    }, 3, 3
    );

    lab20_task03(m1, 3);
    assert(areTwoMatricesEqual(&m1, &m2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void addDomainParseStrToVec(vectorVoid *vec,
                         char *write_ptr,
                         char *buffer){
    long str_len = write_ptr - buffer + 1;
    char *add_str = malloc(str_len);
    memcpy(add_str, buffer, str_len);
    pushBackV(vec, &add_str);
}

vectorVoid parseDomainStr(const char *s){
    char buffer[256];
    char *write_ptr = buffer;
    vectorVoid vec = createVectorV(2, sizeof (char*));

    while (*s){
        if (*s == '.' || *s == '\n'){
            *write_ptr = 0;
            addDomainParseStrToVec(&vec, write_ptr, buffer);
            write_ptr = buffer;
        } else {
            *write_ptr = *s;
            write_ptr++;
        }
        
        s++;
    }

    return vec;
}

void lab20_task04(const char* read_file, const char* write_file){
    FILE *f = fopen(read_file, "r");
    
    int n;
    fscanf(f, "%d", &n);

    vectorVoid domains[n];
    int visits_amounts[n];
    int visits_amounts_c[n];

    const int buffer_size = 1024;
    char buffer[buffer_size];
    for (int i = 0; i < n; ++i) {
        fscanf(f, "%d ", visits_amounts + i);
        fgets(buffer, buffer_size, f);

        domains[i] = parseDomainStr(buffer);
    }

    fclose(f);

    f = fopen(write_file, "w");

    char *unique_str[n];
    int unique_visits_amounts[n];
    char *p_str[n];
    while(n) {
        for (int vec_index = 0; vec_index < n;) {
            if (!isEmptyV(&domains[vec_index])) {
                getVectorValueV(&domains[vec_index],
                                domains[vec_index].size - 1,
                                p_str + vec_index);

                if (domains[vec_index].size > 1){
                    char *undo_str;
                    getVectorValueV(&domains[vec_index],
                                    domains[vec_index].size - 2,
                                    &undo_str);

                    strcpy(buffer, undo_str);
                    int undo_len = strlen(undo_str);
                    buffer[undo_len++] = '.';
                    strcpy(buffer + undo_len, p_str[vec_index]);
                    undo_len += strlen(p_str[vec_index]) + 1;
                    free(undo_str);
                    undo_str = malloc(undo_len);
                    memcpy(undo_str, buffer, undo_len);

                    setVectorValueV(&domains[vec_index],
                                    domains[vec_index].size - 2,
                                    &undo_str);
                }
                popBackV(domains + vec_index);
                ++vec_index;
            } else {
                deleteVectorV(domains + vec_index);
                domains[vec_index] = domains[--n];
                visits_amounts[vec_index] = visits_amounts[n];
            }
        }
        if (n == 0)
            break;
        int k = n;
        unique_str[0] = p_str[0];
        int unique_amount = 1;
        unique_visits_amounts[0] = visits_amounts[0];
        int vec_index = 1;
        memcpy(visits_amounts_c, visits_amounts, n * sizeof (int));

        while (vec_index < k) {
            int i;
            for (i = 0; i < unique_amount; ++i) {
                if (!strcmp(p_str[vec_index], unique_str[i])) {
                    break;
                }
            }

            if (i == unique_amount) {
                unique_visits_amounts[unique_amount] = visits_amounts_c[vec_index];
                unique_str[unique_amount++] = p_str[vec_index++];
            } else {
                unique_visits_amounts[i] += visits_amounts_c[vec_index];
                k--;
                free(p_str[vec_index]);
                p_str[vec_index] = p_str[k];
                visits_amounts_c[vec_index] = visits_amounts_c[k];
            }
        }

        for (int i = 0; i < unique_amount; ++i) {
            fprintf(f, "%d %s\n", unique_visits_amounts[i], unique_str[i]);
            free(unique_str[i]);
        }
    }

    fclose(f);
}

void test_lab20_04(){
    char lab20_task04_str[] = "4\n"
                              "900 google.mail.com\n"
                              "50 yahoo.com\n"
                              "1 intel.mail.com\n"
                              "5 wiki.org\n";

    char lab20_task04_out_str[] = "901 mail.com\n"
                                  "50 yahoo.com\n"
                                  "900 google.mail.com\n"
                                  "5 wiki.org\n"
                                  "5 org\n"
                                  "1 intel.mail.com\n"
                                  "951 com\n";

    const char read_file[] = "20_4_r.txt";
    const char write_file[] = "20_4_w.txt";
    writeAnyway(read_file, lab20_task04_str);
    lab20_task04(read_file, write_file);

//    assert(cmpStrF(lab20_task04_out_str, write_file));
}

int lab20_task05(matrix m){
    int counter = 0;
    matrix inc_m = getMemMatrix(m.nRows, m.nCols);
    for (int row_index = 0; row_index < m.nRows; ++row_index) {
        inc_m.values[row_index][0] = m.values[row_index][0];
        for (int col_index = 0; col_index < m.nCols; ++col_index) {
            if(m.values[row_index][col_index])
                inc_m.values[row_index][col_index] =
                        inc_m.values[row_index][col_index - 1] + 1;
            else
                inc_m.values[row_index][col_index] = 0;

            int min = inc_m.values[row_index][col_index];
            for (int k = row_index; k >= 0; --k) {
                min = minInt(min, inc_m.values[k][col_index]);
                counter += min;
            }
        }
    }

    freeMemMatrix(&inc_m);

    return counter;
}

void test_lab20_05(){
    matrix m1 = createMatrixFromArray(
            (int[])
                    {
                        1, 0, 1,
                        1, 1, 0,
                        1, 1, 0
                    }, 3, 3
            );

    matrix m2 = createMatrixFromArray(
            (int[])
                    {
                            1, 1, 0, 1,
                            1, 1, 1, 1,
                            1, 1, 1, 1,
                            1, 1, 1, 1
                    }, 4, 4
    );

    assert(lab20_task05(m1) == 13);
    assert(lab20_task05(m2) == 76);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void lab20_task06(const char* input_str, char* output_str){
    char digit = '1';

    if (*input_str == 'I'){
        *output_str = digit++;
        output_str++;
    }
    else{
        const char *end_ptr = input_str + 1;
        while (*end_ptr == 'D')
            end_ptr++;

        output_str = output_str + (end_ptr - input_str);
        char *write_ptr = output_str;
        for (const char* cur_ptr = end_ptr + 1; cur_ptr != input_str; cur_ptr--){
            *write_ptr = digit++;
            write_ptr--;
        }

        input_str = end_ptr;
        output_str++;
    }

    while (*input_str) {
        while (*input_str == 'I') {
            input_str++;
            *output_str = digit++;
            output_str++;
        }

        if (*input_str) {
            const char *end_ptr = input_str;

            output_str--;
            digit--;

            while (*end_ptr == 'D')
                end_ptr++;

            long dif = end_ptr - input_str;
            char *write_ptr = output_str + dif;
            for (const char *cur_ptr = end_ptr; cur_ptr >= input_str; cur_ptr--) {
                *write_ptr = digit++;
                write_ptr--;
            }

            input_str = end_ptr;
            output_str += dif + 1;
        }
    }

    *output_str = 0;
    
}

void test_lab20_06(){
    char str1[] = "IIIDIDDD";
    char str2[] = "DDD";
    char str3[] = "IIDIDDII";
    char out_str1[] = "123549876";
    char out_str2[] = "4321";
    char out_str3[] = "124376589";
    char processed_str1[10];
    char processed_str2[10];
    char processed_str3[10];

    lab20_task06(str1, processed_str1);
    lab20_task06(str2, processed_str2);
    lab20_task06(str3, processed_str3);

    assert(!strcmp(processed_str1, out_str1));
    assert(!strcmp(processed_str2, out_str2));
    assert(!strcmp(processed_str3, out_str3));
}

typedef struct IntNode{
    int value;
    struct IntNode* left;
    struct IntNode* right;
} IntNode;

void deleteTreeRec(IntNode *tree){
    if (tree == NULL)
        return;

    deleteTreeRec(tree->left);
    deleteTreeRec(tree->right);
    free(tree);
}

// 3,2,1,6,0,5

IntNode *createTreeRec(int *nums, int n){
    if (n == 0)
        return NULL;

    int max = (int) findMaxUnsortedIndex(nums, n);
    IntNode *node = (IntNode*) malloc(sizeof (IntNode));
    node->value = nums[max];
    node->left = createTreeRec(nums, max);
    max++;
    node->right = createTreeRec(nums + max, n - max);
    return node;
}

void printTreeInDeep(IntNode *node, FILE *f){
    if (node == NULL) {
        fprintf(f, "null ");
    } else {
        fprintf(f, "%d ", node->value);
        printTreeInDeep(node->left, f);
        printTreeInDeep(node->right, f);
    }
}

void test_lab20_07(){
    int nums1[] = {3, 2, 1, 6, 0, 5};
    int nums1_size = sizeof(nums1) / sizeof(int);
    char filename[] = "20_7.txt";
    char result[] = "6 3 null 2 null 1 null null 5 0 null null null ";

    IntNode* tree = createTreeRec(nums1, nums1_size);

    FILE *f = fopen(filename, "w");
    printTreeInDeep(tree, f);
    fclose(f);

    deleteTreeRec(tree);

    assert(cmpStrF(result, filename));

}

void lab20_task08(const char* input_str, const int* array, char *output_str){
    int size = (int) strlen(input_str);
    for (int i = 0; i < size; ++i) {
        output_str[i] = input_str[array[i]];
    }
    output_str[size] = 0;
}

void test_lab20_08(){
    int nums1[] = {0, 3, 2, 1};
    int nums2[] = {0, 1, 2};
    char *input_str1 = "abap";
    char *input_str2 = "abc";
    char *output_str1 = "apab";
    char *output_str2 = "abc";

    char buffer[20];
    lab20_task08(input_str1, nums1, buffer);
    assert(!strcmp(buffer, output_str1));
    lab20_task08(input_str2, nums2, buffer);
    assert(!strcmp(buffer, output_str2));
}

void lab20_task09(const char* read_filename,
                  const char *write_filename,
                  int n){
    FILE *rf = fopen(read_filename, "r");
    FILE *wf = fopen(write_filename, "w");

    int value;
    while(fscanf(rf, "%d", &value) != EOF){
        if (value < n)
            fprintf(wf, "%d ", value);
    }

    fclose(rf);
    fclose(wf);
}

void test_lab20_09(){
    char str[] = "1 0 -12 6 -7 223 -422 857 -1214 84209 -1234 5 10 15 -16";

    const char available_file[] = "20_9_r.txt";
    writeAnyway(available_file, str);

    char read_file[100];
    char write_file[100];
    int n;

    printf("Введите имя файла для чтения (рекомендуется 20_9_r.txt):");
    scanf("%s", read_file);
    printf("Введите имя файла для записи:");
    scanf("%s", write_file);
    printf("Введите число, большее всех чисел в файле для записи:");
    scanf("%d", &n);

    lab20_task09(read_file, write_file, n);
}

bool processing;

void handler(int signal){
    if (signal == SIGINT) {
        exit(0);
        keypad(stdscr, FALSE);
        nocbreak();
        endwin();
    }
}

bool printNextNLines(FILE *f, int n, char *buffer, int buf_size){
    clear();
    for (int i = 0; i < n; ++i) {
        if (fgets(buffer, buf_size, f) == NULL)
            return false;

        addstr(buffer);
    }

    refresh();
    return true;
}

void lab20_task10(const char* filename, int n){
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    signal(SIGINT, handler);

    FILE *f = fopen(filename, "r");

    processing = true;

    const int buf_size = 1000;
    char buffer[buf_size];
    while (true){
        int c = getch();

        if (c == KEY_DOWN) {
            if (!printNextNLines(f, n, buffer, buf_size)) {
                addstr("\nEnd of file\nEnter 'q' for exit");
                while (getch() != 'q');
                break;
            }
        }
    }

    keypad(stdscr, FALSE);
    nocbreak();
    endwin();
}

void test_lab20_10(){
    char read_file[100];
    int n;

    printf("Введите имя файла для чтения: ");
    scanf("%s", read_file);
    printf("Введите число просматриваемых строк: ");
    scanf("%d", &n);

    lab20_task10(read_file, n);
}

void test_lab20_all(){
    test_lab20_01();
    test_lab20_02();
    test_lab20_03();
    test_lab20_04();
    test_lab20_05();
    test_lab20_06();
    test_lab20_07();
    test_lab20_08();
    test_lab20_09();
    test_lab20_10();
}
