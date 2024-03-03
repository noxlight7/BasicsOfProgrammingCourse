# ifndef INC_ARRAY_H
# define INC_ARRAY_H

#include <stdbool.h>
#include <stdlib.h>

typedef int at;
typedef long long it;
typedef bool(*PredicateFunc)(at);
typedef at(*ElementFunc)(at);

// Ввод массива a размера n
void inputArray(at *a, const size_t n);

// Вывод массива a размера n
void outputArray(at a[], const size_t n, const char* sep);

bool isEqual(const at a[], const at b[], const size_t size);

bool isSorted(at a[], size_t size);

// Возвращает индекс первого положительного числа в массиве a размера n
it findFirstPositiveIndex(const at a[], const size_t n);

// Возвращает индекс первого числа в массиве a размера n,
// для которого истинна функция-предикат f, если такое число есть
// в массиве, иначе -1
it findFirstIndexPredicate(const at a[], const size_t n, PredicateFunc f);

bool isEven(at x);

// Возвращает индекс последнего числа в массиве a размера n,
// для которого истинна функция-предикат f, если такое число есть
// в массиве, иначе -1
it findLastIndexPredicate(const at a[], const size_t n, PredicateFunc f);

// Возвращает число элементов массива a размера n,
// для которых истинна функция-предикат f
it countPredicate(const at a[], const size_t n, PredicateFunc f);

void swap(at* a, at* b);

// Меняет порядок элементов массиве a размера n на обратный
void reverse(at* a, const size_t n);

// Возвращает true, если массив a размера n является
// палиндромом, иначе false
bool isPalindrome(const at *a, const it n);

// Возвращает индекс максимального элемента массива a размера n
it findMaxUnsortedIndex(const at* a, const it n);

it findMinUnsortedIndex(const at* a, const it n);

// Сортировка выбором массива a размера n
void sortByChoice(at* a, const it n);

// Удаляет из массива a размера n все элементы, для которых
// истинна функция-предикат f. Порядок элементов в массиве сохраняется
void delSaveOrderByPredicate(at* a, size_t* n, PredicateFunc f);

// Удаляет из массива a размера n все элементы, для которых
// истинна функция-предикат f. Порядок элементов в массиве не сохраняется
void delPredicateUnsaveOrder(at* a, size_t* n, PredicateFunc f);

// Перемещает shift первых элементов массива a размера n в конец массива
void shiftLeft(at* a, const size_t n, int shift);

// Присваивает каждому элементу массива a размера n значение
// f(a[i]), где i - индекс элемента в массиве
void forEach(at* a, const size_t n, ElementFunc f);

// Возвращает true, если хотя бы для одного элемента массива
// a размера n истинна функция-предикат f, иначе false
bool any(at* a, const size_t n, PredicateFunc f);

// Возвращает true, если хотя для всех элементов массива
// a размера n истинна функция-предикат f, иначе false
bool all(at* a, const size_t n, PredicateFunc f);

// Помещает в массив b все элементы массива a, для которых
// истинна функция-предикат f, а в массив c - оставшиеся
// Записывает по адресам b_size и c_size размеры массивов
// b и c соответственно.
void arraySplit(
        const at* a, const size_t a_size,
        at* b, size_t *b_size,
        at* c, size_t *c_size,
        PredicateFunc f);

int getSumOfDigits(int x);

int countNumbersSumOfDigitsIO(it* a, const size_t n, int sum_digits);

it max2it(it x, it y);

at max2at(at x, at y);

it getMaxEvenChainLen(const at* a, const size_t n);

void delNegative(at* a, size_t *n);

void insert(at* a, size_t* n, const size_t pos, int value);

void deletePosSaveOrder(at* a, size_t* n, const size_t pos);

bool isNonDecreasing(const at* a, const size_t n);

void append(at* a, size_t* n, const int value);

void deletePos(at* a, size_t* n, const size_t pos);

bool isNegative(at x);

bool isNonNegative(at x);

int countIf(const at* a, const size_t n, int (*f)(const at));

void inputArrayVar(at** a, size_t *size);

it linearSearch(at* a, const size_t n, const int value);

size_t binarySearch(const at* a, size_t n, at value);

it binarySearchEqualOrMore(const at* a, const size_t n, const at value);

it binarySearchEqualOrLess(const at* a, const size_t n, const at value);

// Предикаты только вида больше / меньше / равно / положительные / отрицательные
it binarySearchEqualOrLessCriteria(const at* a, const size_t n, PredicateFunc fcriteria);

// Копирует массив src в dst
void copy(at *dst, const at *src, size_t size);

void shellSortInt(int a[], int n);
void shellSortIntCriteriaArray(int criteria[], void* bind_array,
                               int bind_array_element_size, int n);
void shellSortLL(long long a[], long long n);

bool isZero(const at a[], const size_t size);

int getSum(int *a, int n);

# endif