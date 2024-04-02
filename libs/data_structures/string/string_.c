//
// Created by curo on 13.03.2024.
//

#include "string_.h"
#include <ctype.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <ctype.h>

size_t strlen_(const char *begin) {
    const char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}

char* find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;

    return begin;
}

char* findNonSpace(char *begin){
    while (*begin && isspace(*begin))
        begin++;

    return begin;
}

char* findSpace(char *begin){
    while (*begin && !isspace(*begin))
        begin++;

    return begin;
}

char* findNonSpaceReverse(char *rbegin, const char *rend){
    while (rbegin != rend && isspace(*rbegin))
        rbegin--;

    return rbegin;
}

char* findSpaceReverse(char *rbegin, const char *rend){
    while (rbegin != rend && !isspace(*rbegin))
        rbegin--;

    return rbegin;
}

int strcmp_(const char *lhs, const char *rhs){
    while (*lhs && *lhs == *rhs)
        lhs++, rhs++;

    return *lhs - *rhs;
}

char* copy_(const char *beginSource, const char *endSource, char *beginDestination){
    long long bytes_copy = endSource - beginSource;
    memcpy(beginDestination, beginSource, bytes_copy);

    return beginDestination + bytes_copy;
}

char* copyIf(char *beginSource, const char *endSource,
             char *beginDestination, int (*f)(int)){
    while (beginSource != endSource){
        if (f(*beginSource)) {
            *beginDestination = *beginSource;
            beginDestination++;
        }
        beginSource++;
    }

    return beginDestination;
}

char* copyIfReverse(char *rbeginSource, const char *rendSource,
                    char *beginDestination, int (*f)(int)){
    while (rbeginSource != rendSource){
        if (f(*rbeginSource)) {
            *beginDestination = *rbeginSource;
            beginDestination++;
        }
        rbeginSource--;
    }

    return beginDestination;
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
