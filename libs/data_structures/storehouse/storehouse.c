//
// Created by curo on 17.03.2024.
//

#include "storehouse.h"
#include "string/string_.h"
#include <malloc.h>
#include <memory.h>
#include <stdbool.h>

productExInfo createProductExInfo(const char *name, int amount, double cost){
    productExInfo info;
    info.base_info = createProductInfo(name, amount);
    info.cost = cost;
    info.total_cost = cost * amount;

    return info;
}

productInfo createProductInfo(const char *name, int amount){
    productInfo info;
    info.amount = amount;

    info.name = (char*) malloc(strlen(name) + 1);
    strcpy(info.name, name);

    return info;
}

productExInfo loadProductExInfo(FILE *f){
    productExInfo info;
    info.base_info = loadProductInfo(f);
    fread(&info.cost, sizeof (double ), 1, f);
    fread(&info.total_cost, sizeof (double ), 1, f);

    return info;
}

void saveProductExInfo(const productExInfo *info, FILE *f){
    saveProductInfo(&info->base_info, f);
    fwrite(&info->cost, sizeof (double ), 1, f);
    fwrite(&info->total_cost, sizeof (double ), 1, f);
}

void freeProductExInfo(productExInfo *info){
    freeProductInfo(&info->base_info);
    info->total_cost = info->cost = 0;
}

void printProductExInfo(productExInfo *info){
    printProductInfo(&info->base_info);
    printf("%lf, %lf, ", info->cost, info->total_cost);
}

productInfo loadProductInfo(FILE *f){
    productInfo info;
    info.name = loadStrBin(f);
    fread(&info.amount, sizeof(int), 1, f);

    return info;
}

bool cmpProductInfo(productInfo *info1, productInfo *info2){
    return info1->amount == info2->amount &&
           !strcmp(info1->name, info2->name);
}

bool cmpProductExInfo(productExInfo *info1, productExInfo *info2){
    return info1->total_cost == info2->total_cost &&
           info1->cost == info2->cost &&
           cmpProductInfo(&info1->base_info, &info2->base_info);
}

void saveProductInfo(const productInfo *info, FILE *f){
    saveStrBin(info->name, f);
    fwrite(&info->amount, sizeof(int), 1, f);
}

void freeProductInfo(productInfo *info){
    free(info->name);
    info->name = NULL;
    info->amount = 0;
}

void printProductInfo(productInfo *info){
    printf("%s, %d, ", info->name, info->amount);
}

storehouse loadStorehouse(FILE *f){
    storehouse sh;
    fread(&sh.records_amount, sizeof(int), 1, f);

    sh.records = malloc(sh.records_amount * sizeof(productExInfo));
    for (int i = 0; i < sh.records_amount; ++i) {
        sh.records[i] = loadProductExInfo(f);
    }

    return sh;
}

productExInfo* findProductExInfo(storehouse *sh, productInfo pi){
    for (int i = 0; i < sh->records_amount; ++i) {
        if (strcmp(sh->records[i].base_info.name, pi.name) == 0){
            return sh->records + i;
        }
    }

    return NULL;
}

void saveStorehouse(const storehouse *sh, FILE *f){
    fwrite(&sh->records_amount, sizeof(int), 1, f);

    for (int i = 0; i < sh->records_amount; ++i) {
        saveProductExInfo(&sh->records[i], f);
    }
}

void freeStorehouse(storehouse *sh){
    for (int i = 0; i < sh->records_amount; ++i) {
        freeProductExInfo(sh->records + i);
    }

    free(sh->records);
    sh->records = NULL;
    sh->records_amount = 0;
}

void updateStorehouse(storehouse *sh, FILE *f){
    int n;
    fread(&n, sizeof (int), 1, f);

    for (int i = 0; i < n; ++i) {
        productInfo info = loadProductInfo(f);
        productExInfo *st_rec = findProductExInfo(sh, info);
        if (st_rec != NULL) {
            if (st_rec->base_info.amount > info.amount) {
                st_rec->base_info.amount -= info.amount;
                st_rec->total_cost = st_rec->base_info.amount * st_rec->cost;
            }
            else {
                freeProductExInfo(st_rec);
                memcpy(st_rec, &sh->records[--sh->records_amount], sizeof(productExInfo));
            }
        }

    }
}

void printStorehouse(storehouse *sh){
    for (int i = 0; i < sh->records_amount; ++i) {
        printProductExInfo(&sh->records[i]);
        putchar('\n');
    }
}