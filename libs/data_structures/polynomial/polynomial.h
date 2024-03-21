//
// Created by curo on 13.03.2024.
//

#ifndef BASICSOFPROGRAMMINGCOURSE_POLYNOMIAL_H
#define BASICSOFPROGRAMMINGCOURSE_POLYNOMIAL_H

#include <stdio.h>

typedef struct monomial{
    int power;
    double factor;
} monomial;

typedef struct polynomial{
    int monomial_amount;
    struct monomial *data;
} polynomial;

// Для тестирования, аргументы должны передаваться по убыванию степеней
polynomial createPolynomialFromArray(int powers[], double factors[], int args_amount);
polynomial* createPolynomialsFromArray(int powers[], double factors[],
                                      int mon_amount[], int pol_amount);
polynomial loadPolynomial(FILE *f);
polynomial* loadPolynomials(FILE *f, int *pol_amount);
void savePolynomial(polynomial p, FILE *f);
void savePolynomials(polynomial *ps, FILE *f, int pol_amount);
double calculatePolynomial(polynomial p, double x);
void freePolynomial(polynomial* p);
void freePolynomials(polynomial* ps, int pol_amount);
void printPolynomial(polynomial p);
void printPolynomials(polynomial* ps, int pol_amount);

#endif //BASICSOFPROGRAMMINGCOURSE_POLYNOMIAL_H
