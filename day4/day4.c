
#include <assert.h>
#include <openssl/md5.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma GCC diagnostic ignored "-Wdeprecated-declarations" // for MD5

#define FILENAME "day4.in"

int compute(char *input, int start, int numMatch);

void example();
void answer(void *in, int len);

int main() {
  FILE *fp;
  char input[8];

  fp = fopen(FILENAME, "r");
  fscanf(fp, "%s", input);
  fclose(fp);

  example();
  answer(input, 8);

  int part1 = compute(input, 1, 5);
  int part2 = compute(input, part1, 6);

  printf("Part 1: %d\n", part1);
  printf("Part 2: %d\n", part2);
}

char *md5DigtestToHex(unsigned char *digest) {
  char *result = (char *)malloc(33);

  for (int i = 0; i < 16; i++) {
    sprintf(&result[i * 2], "%02x", (unsigned int)digest[i]);
  }

  return result;
}

char *strToMd5(char input[], int len) {
  unsigned char result[MD5_DIGEST_LENGTH];
  unsigned char *digest = MD5((unsigned char *)input, len, result);
  char *hex = md5DigtestToHex(digest);
  return hex;
}

int compute(char input[], int start, int numMatch) {
  int num = start;
  size_t i = 0;
  char *s = calloc(strlen(input) + 20, sizeof(char));
  for (; i < strlen(input); i++) {
    s[i] = input[i];
  }

  char *numStr = calloc(20, sizeof(char));

  while (1) {
    memset(numStr, 0, 20);
    sprintf(numStr, "%d", num);
    for (size_t j = 0; j < strlen(numStr); j++) {
      s[i + j] = numStr[j];
    }

    char *hex = strToMd5(s, i + strlen(numStr));

    for (int j = 0; j < numMatch; j++) {
      if (hex[j] != '0') {
        break;
      }
      if (j == numMatch - 1) {
        return num;
      }
    }

    num++;
  }
}

void example() {

  struct Case {
    int expect;
    char *input;
  };

  struct Case cases[2] = {
      {609043, "abcdef"},
      {1048970, "pqrstuv"},
  };

  for (int i = 0; i < 2; i++) {
    struct Case c;
    c = cases[i];
    assert(c.expect == compute(c.input, c.expect - 100, 5));
  }

  printf("All example tests passed!\n");
}

void answer(void *in, int len) {
  char *input = (char *)in;
  (void)len;

  int part1 = compute(input, 1, 5);
  int part2 = compute(input, part1, 6);
  assert(346386 == part1);
  assert(9958218 == part2);
  printf("All answers checked!\n");
}
