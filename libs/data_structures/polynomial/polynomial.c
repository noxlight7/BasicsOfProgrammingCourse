//
// Created by curo on 13.03.2024.
//

#include "polynomial.h"
#include <malloc.h>

polynomial createPolynomialFromArray(int powers[], double factors[], int args_amount){
    polynomial p;
    p.monomial_amount = args_amount;
    p.data = (monomial*) malloc(args_amount * sizeof(monomial));

    for (int i = 0; i < args_amount; ++i) {
        p.data[i].factor = factors[i];
        p.data[i].power = powers[i];
    }

    return p;
}

polynomial* createPolynomialsFromArray(int powers[], double factors[],
                                       int mon_amount[], int pol_amount){
    polynomial *buffer = malloc(pol_amount * sizeof(polynomial));
    for (int pol_index = 0; pol_index < pol_amount; ++pol_index) {
        buffer[pol_index] = createPolynomialFromArray(
                powers, factors, mon_amount[pol_index]);

        powers += mon_amount[pol_index];
        factors += mon_amount[pol_index];
    }

    return buffer;
}

polynomial loadPolynomial(FILE *f){
    polynomial p;
    fread(&p, sizeof(polynomial), 1, f);

    p.data = (monomial*) malloc(p.monomial_amount * sizeof (monomial));

    fread(p.data, sizeof (monomial), p.monomial_amount, f);

    return p;
}

polynomial* loadPolynomials(FILE *f, int *pol_amount){
    fread(pol_amount, sizeof (int), 1, f);

    polynomial *buffer = malloc(*pol_amount * sizeof(polynomial));
    for (int pol_index = 0; pol_index < *pol_amount; ++pol_index) {
        buffer[pol_index] = loadPolynomial(f);
    }

    return buffer;
}

void savePolynomial(polynomial p, FILE *f){
    fwrite(&p, sizeof(polynomial), 1, f);
    fwrite(p.data, sizeof (monomial), p.monomial_amount, f);
}

void savePolynomials(polynomial *ps, FILE *f, int pol_amount){
    fwrite(&pol_amount, sizeof (int), 1, f);

    for (int pol_index = 0; pol_index < pol_amount; ++pol_index) {
        savePolynomial(ps[pol_index], f);
    }
}

double calculatePolynomial(polynomial p, double x){
    double result = 0;
    double mul = 1;
    int index = p.monomial_amount - 1;

    for (int power = 0; power <= p.data[0].power; power++){
        if (p.data[index].power == power) {
            result += p.data[index].factor * mul;
            index--;
        }
        mul *= x;
    }

    return result;
}

void freePolynomial(polynomial* p){
    free(p->data);
    p->data = NULL;
    p->monomial_amount = 0;
}

void freePolynomials(polynomial* ps, int pol_amount){
    for (int pol_index = 0; pol_index < pol_amount; ++pol_index) {
        freePolynomial(ps + pol_index);
    }
}

void printPolynomial(polynomial p){
    for (int i = 0; i < p.monomial_amount; i++)
        printf("%lfx^%d+", p.data[i].factor, p.data[i].power);
    putchar('\n');
}

void printPolynomials(polynomial* ps, int pol_amount){
    for (int i = 0; i < pol_amount; ++i) {
        printPolynomial(ps[i]);
    }
}
