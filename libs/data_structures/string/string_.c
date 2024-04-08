//
// Created by curo on 13.03.2024.
//

#include "string_.h"
#include <ctype.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <ctype.h>
#include "array/array.h"

char _stringBuffer[MAX_STRING_SIZE + 1];
BagOfWords _bag;
BagOfWords _bag2;

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

int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
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

char* getEndOfString(char *s) {
    char *end = s + strlen_(s);
    return end;
}

// проверить
void removeAdjacentEqualLetters(char* s) {
    char *p_read = s + 1;
    char *p_write = p_read;
    char current_symbol = *s;

    while (*p_read) {
        if (current_symbol != *p_read){
            current_symbol = *p_read;
            *p_write = current_symbol;
            p_write++;
        }

        p_read++;
    }
    *p_write = 0;
}

void removeNonLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

void digitToStart(WordDescriptor word) {
    char *endStringBuffer = copy_(word.begin, word.end,
                                 _stringBuffer);
    char *recPosition = copyIfReverse(endStringBuffer - 1,
                                      _stringBuffer - 1,
                                      word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}

int getWordReverse(char *rbegin, char *rend, WordDescriptor *word){
    word->end = findNonSpaceReverse(rbegin, rend);
    if (word->end == rend)
        return 0;
    word->begin = findSpaceReverse(word->end, rend) + 1;
    word->end++;
    return 1;
}

void reverseWordsInStr(char *s){
    WordDescriptor wd;
    while (getWord(s, &wd)){
        s = wd.end;
        wd.end--;

        while (wd.begin < wd.end){
            char c = *wd.begin;
            *wd.begin = *wd.end;
            *wd.end = c;
            wd.end--;
            wd.begin++;
        }
    }
}

void strcpy_(char *dst, char *src){
    while (*src){
        *dst = *src;
        dst++, src++;
    }
}

void replaceDigitSpaces(char *s){
    strcpy_(_stringBuffer, s);
    char *read_ptr = _stringBuffer;
    char *write_ptr = s;
    while (*read_ptr){
        if (isdigit(*read_ptr)) {
            int digit = *read_ptr - '0';
            for (int i = 0; i < digit; ++i) {
                *write_ptr = ' ';
                write_ptr++;
            }
        } else{
            *write_ptr = *read_ptr;
            write_ptr++;
        }
        read_ptr++;
    }
}

int wordCmp(WordDescriptor w1, WordDescriptor w2){
    int w1len = wordLen(w1);
    int w2len = wordLen(w2);

    if(w1len == w2len){
        return memcmp(w1.begin, w2.begin, w1len);
    } else{
        if(w1len > w2len) {
            int res = memcmp(w1.begin, w2.begin, w2len);
            return res != 0 ? res : 1;
        } else{
            int res = memcmp(w1.begin, w2.begin, w1len);
            return res != 0 ? res : -1;
        }
    }
}

char* wordCpy(char *dst, WordDescriptor src){
    copy_(src.begin, src.end, dst);
}

void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);
    size_t source_len = strlen_(source);
    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};
    char *readPtr, *recPtr;

    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        copy_(source, getEndOfString(source), _stringBuffer);
        readPtr = _stringBuffer;
        recPtr = source;
    }

    WordDescriptor wd = {NULL, readPtr};
    while(getWord(wd.end, &wd)) {
        if (!wordCmp(wd, word1)) {
            recPtr = wordCpy(recPtr, word2);
        } else {
            recPtr = wordCpy(recPtr, wd);
        }
        *recPtr = ' ';
        recPtr++;
    }

    recPtr--;
    *recPtr = 0;
}

bool areWordsOrdered(char *s){
    WordDescriptor undo;
    getWord(s, &undo);

    WordDescriptor current;
    int order;
    while(getWord(undo.end, &current)){
        if((order = wordCmp(undo, current)) != 0) {
            undo = current;
            break;
        }
        undo = current;
    }

    while (getWord(undo.end, &current)){
        int res = wordCmp(undo, current);
        if (res != 0 && res != order)
            return false;
        undo = current;
    }

    return true;
}

void getBagOfWords(BagOfWords *bag, char *s) {
    WordDescriptor word1 = {s,s};
    bag->size = 0;

    while (getWord(word1.end, &word1)) {
        bag->words [bag->size++] = word1;
    }

    for (int i = ((int) bag->size) - 1; i >= 0 ; --i) {
        printWord(bag->words[i], '\n');
    }
}