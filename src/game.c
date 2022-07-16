#include "game.h"

void generateRandomWord(char word[WORD_LENGTH])
{
    int randomIndex;
    time_t t;
    srand((unsigned)time(&t));
    randomIndex = rand() % FILE_LENGTH;
    readWordFromFile(randomIndex, word);
}

void gameStart()
{
    char randomWord[WORD_LENGTH];
    generateRandomWord(randomWord);
    gameLoop(randomWord);
}

void gameLoop(char randomWord[WORD_LENGTH])
{
    int gameOver = 0;
    int countGuesses = 0;
    int wordGuessedCorrectly = 0;
    char guessedWord[WORD_LENGTH + 2];
    GuessEntry history[MAX_GUESSES];
    while(!gameOver)
    {
        printf("%s: ", "Enter a Valid Word");
        scanf(" %s", guessedWord);
        tolowercase(guessedWord);        
        if(strlen(guessedWord) != WORD_LENGTH || !checkValidWord(guessedWord))
        {
            printf("Please Enter Valid Word\n");
            outputHistory(history, countGuesses);
        }
        else
        {
            enum letterStatus results[WORD_LENGTH];
            checkGuess(randomWord, guessedWord, results);
            memcpy(history[countGuesses].word, guessedWord, sizeof(char) * WORD_LENGTH);
            memcpy(history[countGuesses].result, results, sizeof(int) * WORD_LENGTH);
            countGuesses++;
            outputHistory(history, countGuesses);
        }
        wordGuessedCorrectly = sumResults(history[countGuesses - 1].result) == EXACT * WORD_LENGTH;
        gameOver = countGuesses == MAX_GUESSES || wordGuessedCorrectly;
    }
    if(!wordGuessedCorrectly)
    {
        printf("The Word Was: %s", randomWord);
    }
}

void checkGuess(char targetWord[WORD_LENGTH], char guessedWord[WORD_LENGTH], enum letterStatus results[WORD_LENGTH])
{
    if(wordCompare(targetWord, guessedWord))
    {
        for(int i = 0; i < WORD_LENGTH; i++)
            results[i] = EXACT;
        return;
    }
    else
    {
        for(int i = 0; i < WORD_LENGTH; i++)
        {
            if(targetWord[i] == guessedWord[i])
            {
                results[i] = EXACT;
            }
            else if(strchr(targetWord, guessedWord[i]) != NULL)
            {
                results[i] = CONTAINS;
            }
            else
            {
                results[i] = NONE;
            }
        }
    }
}

int getColorCode(enum letterStatus status)
{
    switch(status)
    {
        case EXACT: return 32;
        case CONTAINS: return 33;
        case NONE: return 0;
    }
}

void outputResults(char word[WORD_LENGTH], enum letterStatus results[WORD_LENGTH])
{
    for(int i = 0; i < WORD_LENGTH; i++)
    {
        int cc = getColorCode(results[i]);
        printf("\033[%dm%c ", cc, word[i]);
    }
    int defaultCode = getColorCode(NONE);
    printf("\033[%dm\n", defaultCode);
}

void outputHistory(GuessEntry history[MAX_GUESSES], int guessCount)
{
    for(int i = 0; i < guessCount; i++)
    {
        outputResults(history[i].word, history[i].result);
    }
}

int sumResults(enum letterStatus results[WORD_LENGTH])
{
    int sum = 0;
    for(int i = 0; i < WORD_LENGTH; i++)
    {
        sum += results[i];
    }
    return sum;
}