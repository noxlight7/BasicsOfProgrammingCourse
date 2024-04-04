//
// Created by curo on 01.04.2024.
//

#include "test_string.h"
#include "string_.h"
#include <assert.h>
#include <memory.h>
#include <ctype.h>
#include <assert.h>

void test_strlen_(){
    assert(strlen_("12345") == 5);
    assert(strlen_("asdf") == 4);
    assert(strlen_("SDDfqwerqw") == 10);
    assert(strlen_("") == 0);
}

void test_findNonSpace(){
    assert(*findNonSpace("        \t\t\nnm") == 'n');
    assert(*findNonSpace("") == 0);
    assert(*findNonSpace("asdf") =='a');
    assert(*findNonSpace("sd      fr") =='s');
    assert(*findNonSpace("             ") == 0);
}

void test_findSpace(){
    assert(*findSpace("        \t\t\nnm") == ' ');
    assert(*findSpace("") == 0);
    assert(*findSpace("asdf\n") == '\n');
    assert(*findSpace("sd\t      fr") =='\t');
    assert(*findSpace("             ") == ' ');
}

void test_findNonSpaceReverse(){
    char s1[] = "        \t\t\nnm  ";
    assert(findNonSpaceReverse(s1 + 14, s1 - 1) == s1 + 12);
    char s2[] = "";
    assert(findNonSpaceReverse(s2 - 1, s2 - 1) == s2 - 1);
    char s3[] = "asdf";
    assert(findNonSpaceReverse(s3 + 3, s3 - 1) == s3 + 3);
    char s4[] = "sd      fr  ";
    assert(findNonSpaceReverse(s4 + 11, s4 - 1) == s4 + 9);
    char s5[] = "             ";
    assert(findNonSpaceReverse(s5 + 12, s5 - 1) == s5 - 1);
}

void test_findSpaceReverse(){
    char s1[] = "        \t\tnm";
    assert(findSpaceReverse(s1 + 11, s1 - 1) == s1 + 9);
    char s2[] = "";
    assert(findSpaceReverse(s2 - 1, s2 - 1) == s2 - 1);
    char s3[] = "asdf\n";
    assert(findSpaceReverse(s3 + 4, s3 - 1) == s3 + 4);
    char s4[] = "sdfr";
    assert(findSpaceReverse(s4 + 4, s4 - 1) == s4 - 1);
    char s5[] = "             ";
    assert(findSpaceReverse(s5 + 12, s5 - 1) == s5 + 12);
}

void test_strcmp(){
    assert(strcmp_("Вася", "Петя") == -13);
    assert(strcmp_("nordstream", "nord") == 115);
    assert(strcmp_("asa\nasa", "asa\nasa") == 0);
    assert(strcmp_("lhs\t1", "rhs2") == -6);
    assert(strcmp_("             ", "             ") == 0);
}

void test_copy_(){
    char *src = "init local machine";
    char dest[20];
    copy_(src, src + 3, dest);
    assert(!memcmp(src, dest, 3));
    copy_(src + 5, src + 10, dest);
    assert(!memcmp(src + 5, dest, 5));
    copy_(src + 1, src + 10, dest);
    assert(!memcmp(src + 1, dest, 9));
    copy_(src, src, dest);
    assert(!memcmp(src, dest, 0));
}

int isNotSpace(int c){
    return !isspace(c);
}

void test_copyIf(){
    char src[] = "Init0 1Local2 3Machine4";
    char dest[20];

    char s1[] = "Init01Local";
    copyIf(src, src + 14, dest, isNotSpace);
    assert(!memcmp(dest, s1, 11));

    char s2[] = "  ";
    copyIf(src, src + 19, dest, isspace);
    assert(!memcmp(dest, s2, 2));

    char s3[] = "nitocal";
    copyIf(src, src + 14, dest, islower);
    assert(!memcmp(dest, s3, 7));
}

void test_copyIfReverse(){
    char src[] = "Init0 1Local2 3Machine4";
    char dest[20];

    char s1[] = "4enihcaM32lacoL10tinI";
    copyIfReverse(src + 22, src - 1, dest, isNotSpace);
    assert(!memcmp(dest, s1, 21));

    char s2[] = "  ";
    copyIf(src + 22, src - 1, dest, isspace);
    assert(!memcmp(dest, s2, 2));

    char s3[] = "enihcalacotin";
    copyIf(src + 22, src -1, dest, islower);
    assert(!memcmp(dest, s3, 13));
}

void test_strings1(){
    test_strlen_();
    test_findNonSpace();
    test_findSpace();
    test_findNonSpaceReverse();
    test_findSpaceReverse();
    test_strcmp();
    test_copy_();
    test_copyIf();
    test_copyIfReverse();
}

void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line) {
    if (strcmp_(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}

void test_removeAdjacentEqualLetters(){
    char s[] = "11112223";
    removeAdjacentEqualLetters(s);
    assertString("123",
                 s,
                 "string.h",
                 "removeAdjacentEqualLetters",
                 144);
}

void test_getWordReverse(){
    char s[] = "asdf qwery                         zxcv";
    WordDescriptor wd;
    assert(getWordReverse(s + 15, s - 1, &wd));
    assert(wd.begin == s + 5);
    assert(wd.end == s + 10);
}

void test_reverseWordsInStr(){
    char s[] = "Sword of fortune";
    reverseWordsInStr(s);
    assertString("drowS fo enutrof",
                 s,
                 "string.h",
                 "reverseWordsInStr",
                 144);
}

void test_replaceDigitSpaces(){
    char s[MAX_STRING_SIZE] = "A122tt000x5";
    replaceDigitSpaces(s);
    assertString("A     ttx     ",
                 s,
                 "string.h",
                 "replaceDigitSpaces",
                 122);
}

void test_strings2(){
    test_removeAdjacentEqualLetters();
    test_getWordReverse();
    test_reverseWordsInStr();
    test_replaceDigitSpaces();
}
