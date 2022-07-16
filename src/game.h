#ifndef GAME_H
#define GAME_H

#include "util.h"
#include <time.h>

enum letterStatus {
    NONE, CONTAINS, EXACT
};

typedef struct {
    enum letterStatus result[WORD_LENGTH];
    char word[WORD_LENGTH];
} GuessEntry;

void gameStart();
void generateRandomWord(char word[WORD_LENGTH]);
void gameLoop(char word[WORD_LENGTH]);
void checkGuess(char targetWord[WORD_LENGTH], char guessedWord[WORD_LENGTH], enum letterStatus results[WORD_LENGTH]);
int getColorCode(enum letterStatus);
void outputResults(char word[WORD_LENGTH], enum letterStatus[WORD_LENGTH]);
void outputHistory(GuessEntry history[MAX_GUESSES], int guessCount);
int sumResults(enum letterStatus results[WORD_LENGTH]);

#endif