//
// Created by curo on 13.03.2024.
//

#ifndef BASICSOFPROGRAMMINGCOURSE_STRING__H
#define BASICSOFPROGRAMMINGCOURSE_STRING__H

#include <stdio.h>
int strcmp(const char *s1, const char *s2);

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end;
// позиция первого символа, после последнего символа слова
} WordDescriptor;

int getWord(const char *beginSearch, WordDescriptor *word);
void saveStrBin(const char *s, FILE* f);
char* loadStrBin(FILE* f);
int wordLen(WordDescriptor);
void printWord(WordDescriptor, char sep);
char *createCopyStr(const char *s);

#endif //BASICSOFPROGRAMMINGCOURSE_STRING__H
