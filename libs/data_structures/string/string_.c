//
// Created by curo on 13.03.2024.
//

#include "string_.h"
#include <ctype.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>

size_t strlen_(const char *begin) {
    const char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}

int strcmp(const char *s1, const char *s2){
    while (*s1 && *s1 == *s2)
        s1++, s2++;

    return *s1 == *s2 ? 0 : (*s1 < *s2 ? -1 : 1);
}

char *createCopyStr(const char *s){
    size_t len = strlen_(s) + 1;
    char *result = (char *) malloc(len);
    memcpy(result, s, len);
    return result;
}

void saveStrBin(const char *s, FILE* f){
    size_t len = strlen_(s);
    fwrite(&len, sizeof(size_t), 1, f);
    fwrite(s, 1, len, f);
}

char* loadStrBin(FILE* f){
    size_t len;
    fread(&len, sizeof(size_t), 1, f);

    char *s = (char*) malloc(len + 1);
    fread(s, 1, len, f);
    s[len] = 0;

    return s;
}

const char *skipSpaces(const char *s){
    if (isspace(*s))
        s++;

    return s;
}


int getWord(const char *beginSearch, WordDescriptor *word){
    if (isspace(*beginSearch))
        beginSearch = skipSpaces(beginSearch);

    if (*beginSearch == 0)
        return 0;

    word->begin = beginSearch;
    while (*beginSearch && !isspace(*beginSearch))
        beginSearch++;

    word->end = beginSearch;
    return 1;
}

int wordLen(WordDescriptor wd){
    return wd.end - wd.begin;
}

void printWord(WordDescriptor wd, char sep){
    for (char *s = wd.begin; s != wd.end; s++)
        putchar(*s);

    putchar(sep);
}
