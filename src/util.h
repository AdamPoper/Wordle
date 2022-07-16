#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_LENGTH 5
#define FILE_LENGTH 5757
#define MAX_GUESSES 6

#define FILE_PATH "words.txt"

void readWordFromFile(int index, char word[WORD_LENGTH]);
int checkValidWord(char guessedWord[WORD_LENGTH]);
int wordCompare(const char* word1, const char* word2);
void tolowercase(char word[WORD_LENGTH]);

#endif