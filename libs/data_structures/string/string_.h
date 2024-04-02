//
// Created by curo on 13.03.2024.
//

#ifndef BASICSOFPROGRAMMINGCOURSE_STRING__H
#define BASICSOFPROGRAMMINGCOURSE_STRING__H

#include <stdio.h>
int strcmp(const char *lhs, const char *rhs);

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end;
// позиция первого символа, после последнего символа слова
} WordDescriptor;

size_t strlen_(const char *begin);
char* find(char *begin, char *end, int ch);
char* findNonSpace(char *begin);
char* findSpace(char *begin);
char* findNonSpaceReverse(char *rbegin, const char *rend);
char* findSpaceReverse(char *rbegin, const char *rend);
int strcmp_(const char *lhs, const char *rhs);
char* copy_(const char *beginSource, const char *endSource, char *beginDestination);
char* copyIf(char *beginSource, const char *endSource,
             char *beginDestination, int (*f)(int));
char* copyIfReverse(char *rbeginSource, const char *rendSource,
                    char *beginDestination, int (*f)(int));

int getWord(const char *beginSearch, WordDescriptor *word);
void saveStrBin(const char *s, FILE* f);
char* loadStrBin(FILE* f);
int wordLen(WordDescriptor);
void printWord(WordDescriptor, char sep);
char *createCopyStr(const char *s);

#endif //BASICSOFPROGRAMMINGCOURSE_STRING__H
