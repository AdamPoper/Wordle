#include "util.h"

void readWordFromFile(int index, char word[WORD_LENGTH])
{
    FILE* file = fopen(FILE_PATH, "r");
    if(!file)
    {
        printf("%s\n", "file not opened");
        return;
    }
    
    int line = 0;
    while(!feof(file) && line <= index)
    {
        if(fgets(word, WORD_LENGTH + 2, file) != NULL)
        {
            line++;
        }
    }
    fclose(file);
}

int checkValidWord(char guessedWord[WORD_LENGTH])
{
    FILE* file = fopen(FILE_PATH, "r");
    if(!file)
    {
        printf("%s\n", "file not opened");
        return 0;
    }
    char currentWord[WORD_LENGTH + 2];
    while(!feof(file))
    {
        if(fgets(currentWord, WORD_LENGTH + 2, file) != NULL)
        {
            int isValid = wordCompare(currentWord, guessedWord);
            if(isValid)
            {
                fclose(file);
                return isValid;
            }
        }
    }
    fclose(file);
    return 0;
}

int wordCompare(const char* word1, const char* word2)
{
    int isSame = 1;
    for(int i = 0; i < WORD_LENGTH; i++)
    {
        if(word1[i] != word2[i])
        {
            return !isSame;
        }
    }
    return isSame;
}

void tolowercase(char word[WORD_LENGTH])
{
    for(int i = 0; i < WORD_LENGTH; i++)
    {
        word[i] = tolower((unsigned char)word[i]);
    }
}