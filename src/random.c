#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randomPasswordGeneration(int N, int includeNumbers, int includeLowercase, int includeUppercase,
                              int includeSymbols)
{
  if(N <= 0)
  {
    printf("Error: Password length must be greater than 0.\n");
    return;
  }

  srand((unsigned int)(time(NULL)));

  char numbers[] = "0123456789";
  char letter[] = "abcdefghijklmnopqrstuvwxyz";
  char LETTER[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char symbols[] = "!@#$%^&*?";

  char password[N];

  for(int i = 0; i < N; i++)
  {
    int randomizer =
        rand() % (includeNumbers + includeLowercase + includeUppercase + includeSymbols);

    if(randomizer < includeNumbers)
    {
      password[i] = numbers[rand() % 10];
    }
    else if(randomizer < includeNumbers + includeSymbols)
    {
      password[i] = symbols[rand() % 8];
    }
    else if(randomizer < includeNumbers + includeSymbols + includeUppercase)
    {
      password[i] = LETTER[rand() % 26];
    }
    else
    {
      password[i] = letter[rand() % 26];
    }
  }

  printf("%s\n", password);
}