#include "random.h"

int main()
{
  int N = 20;
  int includeNumbers = 1;
  int includeLowercase = 1;
  int includeUppercase = 1;
  int includeSymbols = 1;

  randomPasswordGeneration(N, includeNumbers, includeLowercase, includeUppercase, includeSymbols);

  return 0;
}