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
    char s1[] = "11112223";
    char s2[] = "";
    char s3[] = "11112223";
    removeAdjacentEqualLetters(s1);
    removeAdjacentEqualLetters(s2);
    removeAdjacentEqualLetters(s3);
    ASSERT_STRING("123", s1);
    ASSERT_STRING("", s2);
    ASSERT_STRING("123", s3);
}

void test_getWordReverse(){
    char s[] = "asdf qwery                         zxcv";
    WordDescriptor wd;
    assert(getWordReverse(s + 15, s - 1, &wd));
    assert(wd.begin == s + 5);
    assert(wd.end == s + 10);

    char s2[] = "adf \ttgddv cadf\t yhyt";
    char got[MAX_WORD_SIZE];
    assert(getWordReverse(getEndOfString(s2) - 1, s2 - 1, &wd));
    wordDescriptorToString(wd, got);
    ASSERT_STRING("yhyt", got);

    char s3[] = "";
    assert(!getWordReverse(s3 - 1, s3 - 1, &wd));
}

void test_reverseWordsInStr(){
    char s1[] = "";
    char s2[] = "Sword of fortune";
    char s3[] = "abcba sos";
    reverseWordsInStr(s1);
    reverseWordsInStr(s2);
    reverseWordsInStr(s3);
    ASSERT_STRING("drowS fo enutrof", s2);
    ASSERT_STRING(s3, s3);
}

void test_replaceDigitSpaces(){
    char s1[MAX_STRING_SIZE] = "A122tt000x5";
    char s2[MAX_STRING_SIZE] = "Attx";
    char s3[MAX_STRING_SIZE] = "";
    replaceDigitSpaces(s1);
    replaceDigitSpaces(s2);
    replaceDigitSpaces(s3);
    ASSERT_STRING("A     ttx     ", s1);
    ASSERT_STRING(s2, s2);
    ASSERT_STRING(s3, s3);
}

void test_replace(){
    char s1[MAX_STRING_SIZE] = "dde abc abcd ffk";
    char s2[MAX_STRING_SIZE] = "dde abc abcd ffk";
    char s3[MAX_STRING_SIZE] = "dde abc abcd ffk";
    char s4[MAX_STRING_SIZE] = "";
    char out1[] = "dde dda abcd ffk";
    char out2[] = "dde abc dda ffk";
    char out3[] = "dde abc abcd abcdefg";
    char out4[] = "";
    replace(s1, "abc", "dda");
    replace(s2, "abcd", "dda");
    replace(s3, "ffk", "abcdefg");
    replace(s4, "ffk", "abcdefg");
    ASSERT_STRING(out1, s1);
    ASSERT_STRING(out2, s2);
    ASSERT_STRING(out3, s3);
    ASSERT_STRING(out4, s4);
}

void test_areWordsOrdered(){
    char s1[] = "abc abc cde efj";
    char s2[] = "abc cde efj abc";
    char s3[] = "efj cde abc abc";
    char s4[] = "";
    assert(areWordsOrdered(s1));
    assert(!areWordsOrdered(s2));
    assert(areWordsOrdered(s3));
    assert(areWordsOrdered(s4));
}

void test_getBagOfWords(){
    char s[] = "asdf ewt    lokpf \n \t 23";
    getBagOfWords(&_bag, s);
    char got[MAX_WORD_SIZE];

    wordDescriptorToString(_bag.words[0], got);
    ASSERT_STRING("asdf", got);
    wordDescriptorToString(_bag.words[1], got);
    ASSERT_STRING("ewt", got);
    wordDescriptorToString(_bag.words[2], got);
    ASSERT_STRING("lokpf", got);
    wordDescriptorToString(_bag.words[3], got);
    ASSERT_STRING("23", got);

    getBagOfWords(&_bag, "");
    assert(_bag.size == 0);
}

void test_countPalindromes(){
    char s[] = "asdf,ogo,assa,forest,minim";
    char s2[] = "asdf,ogo,assa,forest,minim,got,leel,of";
    char s3[] = "";
    assert(countPalindromes(s) == 3);
    assert(countPalindromes(s2) == 4);
    assert(countPalindromes(s3) == 0);
}

void test_mergeStr(){
    char s[] = "word1   word3 \nword5\tword6  word7";
    char s2[] = "word2  word4";
    char out[MAX_STRING_SIZE];
    mergeStr(s, s2, out);
    ASSERT_STRING("word1 word2 word3 word4 word5 word6 word7", out);
    char s3[] = "";
    mergeStr(s3, s3, out);
    ASSERT_STRING("", out);
    mergeStr(s2, s2, out);
    ASSERT_STRING("word2 word2 word4 word4", out);
}

void test_getWordsInReverseOrder(){
    char s1[] = "word1 word2 word3\n word4 word5\tword6\tword7";
    char s2[] = "asdf\n effv dvvg\tdf";
    char s3[] = "";
    getWordsInReverseOrder(s1);
    getWordsInReverseOrder(s2);
    getWordsInReverseOrder(s3);
    ASSERT_STRING("word7 word6 word5 word4 word3 word2 word1", s1);
    ASSERT_STRING("df dvvg effv asdf", s2);
    ASSERT_STRING("", s3);
}

void testAll_getWordBeforeFirstWordWithA() {
    WordDescriptor word;
    char s1[] = "";
    assert(
            getWordBeforeFirstWordWithA(s1, &word)
            == EMPTY_STRING
    );
    char s2[] = "ABC";
    assert(
            getWordBeforeFirstWordWithA(s2, &word)
            == FIRST_WORD_WITH_A
    );
    char s3[] = "BC A";
    assert(
            getWordBeforeFirstWordWithA(s3, &word)
            == WORD_FOUND
    );
    char got[MAX_WORD_SIZE];
    wordCpy(got, word);
    got[word.end - word.begin] = '\0';
    ASSERT_STRING("BC", got);

    char s4[] = "B Q WE YR OW IUWR";
    assert(getWordBeforeFirstWordWithA(s4, &word) ==
           NOT_FOUND_A_WORD_WITH_A);
}

void testAll_lastWordInFirstStringInSecondString() {
    WordDescriptor word;
    char s1[] = "word1 word2 word3";
    char s2[] = "word4 word5 word6";
    assert(
            lastWordInFirstStringInSecondString(s1, s2).begin == NULL
    );
    char s3[] = "";
    assert(
            lastWordInFirstStringInSecondString(s3, s3).begin == NULL
    );
    char s4[] = "word4 word2 word5";
    word = lastWordInFirstStringInSecondString(s1, s4);
    char got[MAX_STRING_SIZE];
    wordDescriptorToString(word, got);
    ASSERT_STRING("word2", got);
}

void test_haveEqualWords() {
    char s1[] = "word1 word2 word3";
    char s2[] = "word4 word5 word5";
    char s3[] = "asd dfg kl sdf trty gfgd gree sdf errf";

    assert(!haveEqualWords(s1));
    assert(haveEqualWords(s2));
    assert(haveEqualWords(s3));
}

void test_haveWordWithEqualSymbolSet() {
    char s1[] = "word1 w2dor word3";
    char s2[] = "word4 w5odr word5";
    char s3[] = "asd dfg kl dsf trty gfgd gree sdf errf";

    assert(!haveWordWithEqualSymbolSet(s1));
    assert(haveWordWithEqualSymbolSet(s2));
    assert(haveWordWithEqualSymbolSet(s3));
}

void test_deleteEqualLastWord() {
    char s1[] = "word1 word2 word3 word2";
    char s2[] = "word4 w5odr word5";
    char s3[] = "";
    char s4[] = "word5";

    deleteEqualLastWord(s1);
    deleteEqualLastWord(s2);
    deleteEqualLastWord(s3);
    deleteEqualLastWord(s4);

    ASSERT_STRING("word1 word3", s1);
    ASSERT_STRING("word4 w5odr", s2);
    ASSERT_STRING("", s3);
    ASSERT_STRING("", s4);
}

void test_getFirstWordS1InS2() {
    char s1[] = "word1 word2 word3 word2";
    char s2[] = "word4 word3 word5";
    char s3[] = "";
    char s4[] = "word5";
    char s5[] = "word5";
    char got[MAX_STRING_SIZE];
    WordDescriptor word;

    word = getFirstWordS1InS2(s1, s2);
    wordDescriptorToString(word, got);
    ASSERT_STRING("word2", got);

    word = getFirstWordS1InS2(s3, s4);
    assert(word.begin == NULL);

    word = getFirstWordS1InS2(s5, s5);
    assert(word.begin == NULL);
}

void test_deletePalindromes() {
    char s1[] = "word1 wordrow word3 asa";
    char s2[] = "word4 w5odr word5";
    char s3[] = "";
    char s4[] = "asa";

    deletePalindromes(s1);
    deletePalindromes(s2);
    deletePalindromes(s3);
    deletePalindromes(s4);

    ASSERT_STRING("word1 word3", s1);
    ASSERT_STRING("word4 w5odr word5", s2);
    ASSERT_STRING("", s3);
    ASSERT_STRING("", s4);
}

void test_fillShorterStr() {
    char s1[MAX_STRING_SIZE] = "word1 wordrow word3 asa";
    char s2[MAX_STRING_SIZE] = "word4 w5odr word5";
    char s3[MAX_STRING_SIZE] = "";
    char s4[MAX_STRING_SIZE] = "";

    fillShorterStr(s1, s2);
    fillShorterStr(s3, s1);
    fillShorterStr(s4, s4);

    ASSERT_STRING("word4 w5odr word5 asa", s2);
    ASSERT_STRING("word1 wordrow word3 asa", s3);
    ASSERT_STRING("", s4);
}

void test_isAllWordLettersInStr() {
    char s1[] = "word wordrow word asa";
    char s2[] = "word wodr word";
    char s3[] = "asd";
    char s4[] = "";

    char ws1[] = "wdosaaaarwwworrrrr";
    char ws2[] = "wordwodrqword";
    char ws3[] = "";
    char ws4[] = "sad";

    WordDescriptor word1;
    WordDescriptor word2;
    WordDescriptor word3;
    WordDescriptor word4;

    getWord(ws1, &word1);
    getWord(ws2, &word2);
    word3 = (WordDescriptor) {ws3, ws3};
    getWord(ws4, &word4);

    assert(isAllWordLettersInStr(s1, word1));
    assert(!isAllWordLettersInStr(s2, word2));
    assert(isAllWordLettersInStr(s3, word3));
    assert(!isAllWordLettersInStr(s4, word4));
}

void test_strings2(){
    test_removeAdjacentEqualLetters();
    test_getWordReverse();
    test_reverseWordsInStr();
    test_replaceDigitSpaces();
    test_replace();
    test_areWordsOrdered();
    test_getBagOfWords();
    test_countPalindromes();
    test_mergeStr();
    test_getWordsInReverseOrder();
    testAll_getWordBeforeFirstWordWithA();
    testAll_lastWordInFirstStringInSecondString();
    test_haveEqualWords();
    test_haveWordWithEqualSymbolSet();
    test_deleteEqualLastWord();
    test_getFirstWordS1InS2();
    test_deletePalindromes();
    test_fillShorterStr();
    test_isAllWordLettersInStr();
}
