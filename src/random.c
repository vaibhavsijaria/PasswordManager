#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define NUM_SETS 4

void randomPasswordGeneration(int N, int includeNumbers, int includeLowercase, int includeUppercase,
                              int includeSymbols)
{
  if(N <= 0)
  {
    printf("Error: Password length must be greater than 0.\n");
    return;
  }

  if(!(includeNumbers || includeLowercase || includeUppercase || includeSymbols))
  {
    printf("Error: At least one character set must be included.\n");
    return;
  }

  srand((unsigned int)(time(NULL)) ^ (unsigned int)getpid());

  char numbers[] = "0123456789";
  char letter[] = "abcdefghijklmnopqrstuvwxyz";
  char LETTER[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char symbols[] = "!@#$%^&*?";

  char* sets[] = {numbers, letter, LETTER, symbols};
  int setSizes[NUM_SETS] = {strlen(numbers), strlen(letter), strlen(LETTER), strlen(symbols)};
  int includes[] = {includeNumbers, includeLowercase, includeUppercase, includeSymbols};

  char password[N + 1];
  password[N] = '\0';

  for(int i = 0; i < N; i++)
  {
    int setIndex;
    do
    {
      setIndex = rand() % NUM_SETS;
    } while(!includes[setIndex]);

    password[i] = sets[setIndex][rand() % setSizes[setIndex]];
  }

  printf("%s\n", password);
}