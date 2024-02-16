//
// Created by curo on 16.02.2024.
//

#include "test_vector_void.h"
#include "vector_void.h"
#include <stdio.h>

void testVectorVoidInt() {
    size_t n;
    scanf("%zd", &n);

    vectorVoid v = createVectorV(0, sizeof(int));
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);

        pushBackV(&v, &x);
    }

    for (int i = 0; i < n; i++) {
        int x;
        getVectorValueV(&v, i, &x);

        printf("%d ", x);
    }
}

void testVectorVoidDouble() {
    size_t n;
    scanf("%zd", &n);

    vectorVoid v = createVectorV(0, sizeof(double));
    for (int i = 0; i < n; i++) {
        double x;
        scanf("%lf", &x);

        pushBackV(&v, &x);
    }

    for (int i = 0; i < n; i++) {
        double x;
        getVectorValueV(&v, i, &x);

        printf("%lf ", x);
    }
}
