//
// Created by curo on 13.03.2024.
//

#ifndef BASICSOFPROGRAMMINGCOURSE_STRING__H
#define BASICSOFPROGRAMMINGCOURSE_STRING__H
#define ASSERT_STRING(expected, got) assertString(expected, got, __FILE__, __FUNCTION__, __LINE__)
#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20


#include <stdio.h>
#include <stdbool.h>
int strcmp(const char *lhs, const char *rhs);

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end;
// позиция первого символа, после последнего символа слова
} WordDescriptor;

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

extern BagOfWords _bag;
extern BagOfWords _bag2;

typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;

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

void removeAdjacentEqualLetters(char* s);

int getWord(char *beginSearch, WordDescriptor *word);
int getWordReverse(char *rbegin, char *rend, WordDescriptor *word);
void digitToStart(WordDescriptor word);

void reverseWordsInStr(char *s);
void replaceDigitSpaces(char *s);
int wordCmp(WordDescriptor w1, WordDescriptor w2);
char* wordCpy(char *dst, WordDescriptor src);
void replace(char *source, char *w1, char *w2);
bool areWordsOrdered(char *s);
void getBagOfWords(BagOfWords *bag, char *s);

void saveStrBin(const char *s, FILE* f);
char* loadStrBin(FILE* f);
int wordLen(WordDescriptor);
void printWord(WordDescriptor, char sep);
char *createCopyStr(const char *s);
int countPalindromes(char *s);
void mergeStr(char* s1, char* s2, char* out);
void getWordsInReverseOrder(char *s);
WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(
        char *s, WordDescriptor *w);
void wordDescriptorToString(WordDescriptor word, char *destination);
WordDescriptor lastWordInFirstStringInSecondString(char* s1, char* s2);
bool haveEqualWords(char* s);
bool haveWordWithEqualSymbolSet(char* s);
void deleteEqualLastWord(char* s);
WordDescriptor getFirstWordS1InS2(char* s1, char* s2);
bool isPalindromeS(WordDescriptor word);
void deletePalindromes(char* ptr);
#endif //BASICSOFPROGRAMMINGCOURSE_STRING__H
