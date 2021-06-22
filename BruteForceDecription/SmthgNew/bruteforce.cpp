#include "bruteforce.h"
#include <math.h>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void getGuess()
{
    const char chars[CHAR_COUNT + 1] = "abcdefghijklmnopqrstuvwxyz0123456789";
    int i, j;
    int k = 0;
    int guessc[MAX_SIZE] = { 0 };
    char guess[MAX_SIZE + 1];

    for (i = 1; i < MAX_SIZE; guessc[i++] = -1);
    for (i = 1; i <= MAX_SIZE; guess[i++] = '\0');
    
    while (k++ < (pow(CHAR_COUNT + 1, MAX_PASSWORD_LENGTH) + 47988))
    {
        i = 0;
        while (guessc[i] == CHAR_COUNT)
        {
            guessc[i] = 0;
            guessc[++i] += 1;
        }
        for (j = 0; j <= i; ++j)
        {
            if (j < MAX_SIZE)
                guess[j] = chars[guessc[j]];
        }
        printf("%s\n", guess);
        std::ofstream os("C:/File1.txt", std::ios::app);
        os << guess << " ";
        ++guessc[0];
    }
}