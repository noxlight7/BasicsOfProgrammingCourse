#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stdbool.h"

typedef int at;
typedef long long it;
typedef bool(*PredicateFunc)(at);
typedef at(*ElementFunc)(at);

// реализация сортировки Шелла
void shellSortInt(int a[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            //сортировка подсписков, созданных с помощью gap
            int temp = a[i];

            int j;
            for (j = i; j >= gap && a[j - gap] > temp; j -= gap)
                a[j] = a[j - gap];

            a[j] = temp;
        }
    }
}

// реализация сортировки Шелла
void shellSortIntCriteriaArray(int *criteria, void* bind_array,
                               int bind_array_element_size, int n)
{
    char temp_bind[bind_array_element_size];

    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            //сортировка подсписков, созданных с помощью gap
            int temp = criteria[i];
            memcpy(temp_bind, bind_array + i * bind_array_element_size, bind_array_element_size);

            int j;
            for (j = i; j >= gap && criteria[j - gap] > temp; j -= gap) {
                criteria[j] = criteria[j - gap];
                memcpy(bind_array + j * bind_array_element_size,
                       bind_array + (j - gap) * bind_array_element_size,
                       bind_array_element_size);
            }

            criteria[j] = temp;
            memcpy(bind_array + j * bind_array_element_size, temp_bind, bind_array_element_size);
        }
    }
}

// реализация сортировки Шелла
void shellSortIntCriteriaArrayF(float *criteria, void* bind_array,
                               int bind_array_element_size, int n)
{
    char temp_bind[bind_array_element_size];

    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            //сортировка подсписков, созданных с помощью gap
            float temp = criteria[i];
            memcpy(temp_bind, bind_array + i * bind_array_element_size, bind_array_element_size);

            int j;
            for (j = i; j >= gap && criteria[j - gap] > temp; j -= gap) {
                criteria[j] = criteria[j - gap];
                memcpy(bind_array + j * bind_array_element_size,
                       bind_array + (j - gap) * bind_array_element_size,
                       bind_array_element_size);
            }

            criteria[j] = temp;
            memcpy(bind_array + j * bind_array_element_size, temp_bind, bind_array_element_size);
        }
    }
}

void shellSortLL(long long a[], long long n)
{
    for (long long gap = n / 2; gap > 0; gap /= 2)
    {
        for (long long i = gap; i < n; i += 1)
        {
            //сортировка подсписков, созданных с помощью gap
            long long temp = a[i];

            long long j;
            for (j = i; j >= gap && a[j - gap] > temp; j -= gap)
                a[j] = a[j - gap];

            a[j] = temp;
        }
    }
}

// Ввод массива a размера n
void inputArray(at *a, const size_t n) {
    for (size_t i = 0; i < n; i++, a++)
        scanf("%d", a);
}

// Вывод массива a размера n
void outputArray(at a[], const size_t n, const char* sep) {
    for (size_t i = 1; i < n; i++, a++)
        printf("%d%s", *a, sep);

    if(n)
        printf("%d", *a);

    putchar('\n');
}

// Вывод массива a размера n
void outputArrayF(at a[], const size_t n, const char* sep, FILE* f) {
    for (size_t i = 1; i < n; i++, a++)
        fprintf(f, "%d%s", *a, sep);

    if(n)
        fprintf(f, "%d", *a);

    fputc('\n', f);
}

bool isEqual(const at a[], const at b[], const size_t size) {
    return memcmp(a, b, size * sizeof(at)) == 0;
}

bool isZero(const at a[], const size_t size) {
    for (int i = 0; i < size; ++i)
        if (a[i])
            return false;

    return true;
}

bool isSorted(at a[], size_t size) {
    for (int i = 1; i < size; i++)
        if (a[i - 1] > a[i])
            return false;

    return true;
}

// Возвращает индекс первого положительного числа в массиве a размера n
it findFirstPositiveIndex(const at a[], const size_t n) {
    for (size_t i = 0; i < n; i++, a++)
        if (*a > 0)
            return i;

    return -1;
}

// Возвращает индекс первого числа в массиве a размера n,
// для которого истинна функция-предикат f, если такое число есть
// в массиве, иначе -1
it findFirstIndexPredicate(const at a[], const size_t n, PredicateFunc f) {
    for (size_t i = 0; i < n; i++, a++)
        if (f(*a))
            return i;

    return -1;
}

bool isEven(at x) {
    return (x & 1) == 0;
}

// Возвращает индекс последнего числа в массиве a размера n,
// для которого истинна функция-предикат f, если такое число есть
// в массиве, иначе -1
it findLastIndexPredicate(const at a[], const size_t n, PredicateFunc f) {
    for (it i = n - 1; i >= 0; i--)
        if (f(a[i]))
            return i;

    return -1;
}

// Возвращает число элементов массива a размера n,
// для которых истинна функция-предикат f
it countPredicate(const at a[], const size_t n, PredicateFunc f) {
    int counter = 0;
    for (int i = 0; i < n; i++)
        if (f(a[i]))
            counter++;

    return counter;
}

void swap(at* a, at* b) {
    at c = *a;
    *a = *b;
    *b = c;
}

// Меняет порядок элементов массиве a размера n на обратный
void reverse(at* a, const size_t n) {
    for (size_t i = 0, j = n - 1; i < j; i++, j--)
        swap(a + i, a + j);
}

// Возвращает true, если массив a размера n является
// палиндромом, иначе false
bool isPalindrome(const at *a, const it n) {
    it i, j;
    for (i = 0, j = n - 1; i < j && a[i] == a[j]; i++, j--);
    return i >= j;
}

// Возвращает индекс максимального элемента массива a размера n
it findMaxUnsortedIndex(const at* a, const it n) {
    int max_value = a[0];
    int max_index = 0;
    for (int i = 1; i < n; i++)
        if (max_value < a[i]) {
            max_value = a[i];
            max_index = i;
        }

    return max_index;
}

// Возвращает индекс минимального элемента массива a размера n
it findMinUnsortedIndex(const at* a, const it n) {
    int min_value = a[0];
    int min_index = 0;
    for (int i = 1; i < n; i++)
        if (min_value > a[i]) {
            min_value = a[i];
            min_index = i;
        }

    return min_index;
}

at findMaxElement(const at* a, const it n) {
    return a[findMaxUnsortedIndex(a, n)];
}

// Сортировка выбором массива a размера n
void sortByChoice(at* a, const it n) {
    for (it i = n - 1; i > 0; i--) {
        it max = findMaxUnsortedIndex(a, i + 1);
        if (max != i)
            swap(a + max, a + i);
    }
}

// Удаляет из массива a размера n все элементы, для которых
// истинна функция-предикат f. Порядок элементов в массиве сохраняется
void delSaveOrderByPredicate(at* a, size_t* n, PredicateFunc f) {
    size_t i_read = 0;
    size_t size = *n;
    while (i_read < size && !f(a[i_read]))
        i_read++;
    size_t i_write = i_read;
    while (i_read < size) {
        if (!f(a[i_read]))
            a[i_write++] = a[i_read];
        i_read++;
    }

    *n = i_write;
}

// Удаляет из массива a размера n все элементы, для которых
// истинна функция-предикат f. Порядок элементов в массиве не сохраняется
void delPredicateUnsaveOrder(at* a, size_t* n, PredicateFunc f) {
    size_t size = *n;
    size_t i_read = 0;
    while (i_read < size) {
        if (f(a[i_read]))
            a[i_read] = a[--size];
        else
            i_read++;
    }

    *n = size;
}

// Перемещает shift первых элементов массива a размера n в конец массива
void shiftLeft(at* a, const size_t n, int shift) {
    shift = shift % n;
    if (shift) {
        size_t bytes_first = sizeof(at) * shift;
        size_t second_elements_amount = n - shift;
        at* temp = (at*)malloc(bytes_first);
        memcpy(temp, a, bytes_first);
        memcpy(a, a + shift, second_elements_amount * sizeof(at));
        memcpy(a + second_elements_amount, temp, bytes_first);
        free(temp);
    }
}

// Присваивает каждому элементу массива a размера n значение
// f(a[i]), где i - индекс элемента в массиве
void forEach(at* a, const size_t n, ElementFunc f) {
    for (int i = 0; i < n; i++)
        a[i] = f(a[i]);
}

// Возвращает true, если хотя бы для одного элемента массива
// a размера n истинна функция-предикат f, иначе false
bool any(at* a, const size_t n, PredicateFunc f) {
    for (int i = 0; i < n; i++)
        if (f(a[i]))
            return true;

    return false;
}

// Возвращает true, если хотя для всех элементов массива
// a размера n истинна функция-предикат f, иначе false
bool all(at* a, const size_t n, PredicateFunc f) {
    for (int i = 0; i < n; i++)
        if (!f(a[i]))
            return false;

    return true;
}


// Помещает в массив b все элементы массива a, для которых
// истинна функция-предикат f, а в массив c - оставшиеся
// Записывает по адресам b_size и c_size размеры массивов
// b и c соответственно.
void arraySplit(
        const at* a, const size_t a_size,
        at* b, size_t *b_size,
        at* c, size_t *c_size,
        PredicateFunc f) {
    size_t b_index = 0;
    size_t c_index = 0;
    for (size_t a_index = 0; a_index < a_size; a_index++)
        if (f(a[a_index]))
            b[b_index++] = a[a_index];
        else
            c[c_index++] = a[a_index];

    *b_size = b_index;
    *c_size = c_index;
}

int getSumOfDigits(int x) {
    x = abs(x);
    int sum = 0;
    while (x) {
        sum += x % 10;
        x /= 10;
    }

    return sum;
}

int countNumbersSumOfDigitsIO(it* a, const size_t n, int sum_digits) {
    int numbers_amount = 0;
    for (size_t i = 0; i < n; i++)
        if (getSumOfDigits(a[i]) == sum_digits)
            numbers_amount++;

    return numbers_amount;
}

it max2it(it x, it y) {
    return x >= y ? x : y;
}

at max2at(at x, at y) {
    return x >= y ? x : y;
}

it getMaxEvenChainLen(const at* a, const size_t n) {
    it max_len = 0;
    it curr_len = 0;
    for (size_t i = 0; i < n; i++)
        if (a[i] % 2 == 0) {
            curr_len++;
            max_len = max2it(max_len, curr_len);
        }
        else
            curr_len = 0;

    return max_len;
}

void delNegative(at* a, size_t *n) {
    size_t i_read = 0;
    size_t size = *n;
    while (i_read < size && !(a[i_read] < 0))
        i_read++;
    size_t i_write = i_read;
    while (i_read < size) {
        if (!(a[i_read] < 0))
            a[i_write++] = a[i_read];

        i_read++;
    }

    *n = i_write;
}

void insert(at* a, size_t* n, const it pos, int value) {
    for (it i = *n - 1; i >= pos; i--)
        a[i + 1] = a[i];

    a[pos] = value;
    (*n)++;
}

void deletePosSaveOrder(at* a, size_t* n, const size_t pos) {
    (*n)--;
    for (size_t i = pos; i < *n; i++)
        a[i] = a[i + 1];
}

bool isNonDecreasing(const at* a, const size_t n) {
    for (size_t i = 1; i < n; i++)
        if (a[i - 1] > a[i])
            return 0;

    return 1;
}

void append(at* a, size_t* n, const int value) {
    a[*n] = value;
    (*n)++;
}

void deletePos(at* a, size_t* n, const size_t pos) {
    a[pos] = a[*n - 1];
    (*n)--;
}

bool isNegative(at x) {
    return x < 0;
}

bool isNonNegative(at x) {
    return x >= 0;
}

int countIf(const at* a, const size_t n, int (*f)(const at)) {
    int counter = 0;
    for (size_t i = 0; i < n; i++)
        if (a[i] < 0)
            counter++;

    return counter;
}

void inputArrayVar(at** a, size_t *size) {
    it max_size = 1;
    *a = (at*) malloc(sizeof(at) * max_size);
    it i = 0;
    at value;

    do {
        scanf("%d", &value);

        if (value != 0) {
            if (i == max_size) {
                max_size *= 2;
                *a = (at*)realloc(a, sizeof(at) * max_size);
            }
            (*a)[i++] = value;
        }
    } while (value);

    *a = (at*) realloc(*a, sizeof(at) * i);
    *size = i;
}

size_t linearSearch(at* a, const size_t n, const int value) {
    size_t i = 0;
    while (i < n && a[i] != value)
        i++;

    return i;
}

size_t binarySearch(const at* a, size_t n, at value) {
    it left = 0;
    it right = n - 1;
    while (left <= right) {
        it middle = (left + right) / 2;
        if (a[middle] < value)
            left = middle + 1;
        else if (a[middle] > value)
            right = middle - 1;
        else
            return middle;
    }
    return n;
}

it binarySearchEqualOrMore(const at* a, const size_t n, const int value) {
    it left = -1;
    it right = n;
    while (right - left > 1) {
        it middle = (left + right) / 2;
        if (a[middle] < value)
            left = middle;
        else
            right = middle;
    }
    return right;
}

it binarySearchEqualOrLess(const at* a, const size_t n, const int value) {
    it left = -1;
    it right = n;
    while (right - left > 1) {
        it middle = (left + right) / 2;
        if (a[middle] <= value)
            left = middle;
        else
            right = middle;
    }
    return left;
}

// Предикаты только вида больше / меньше / равно / положительные / отрицательные
it binarySearchEqualOrLessCriteria(const at* a, const size_t n, PredicateFunc fcriteria) {
    int left = -1;
    int right = n;
    while (right - left > 1) {
        int middle = (left + right) / 2;
        if (fcriteria(a[middle]))
            left = middle;
        else
            right = middle;
    }
    return left;
}

void copy(at *dst, const at *src, size_t size){
    memcpy(dst, src, size * sizeof(at));
}

int getSum(at *a, int n){
    int result = 0;
    for (int i = 0; i < n; i++)
        result += a[i];

    return result;
}

int maxInt(int a, int b){
    return a >= b ? a : b;
}

int minInt(int a, int b){
    return a <= b ? a : b;
}

int getMax(int *a, int n){
    int max = *a;
    for (int i = 1; i < n; ++i) {
        max = maxInt(max, a[i]);
    }
    return max;
}

int getMin(int *a, int n){
    int min = *a;
    for (int i = 1; i < n; ++i) {
        min = minInt(min, a[i]);
    }
    return min;
}

long long getSumL(int *a, int n){
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
    }

    return sum;
}

bool isUnique(long long *a, int n){
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; j++)
            if (a[i] == a[j])
                return false;

    return true;
}

