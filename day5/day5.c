
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "day5.in"
#define LINE_LEN 16
#define LINES 1000

void example();
void answer(void *in, int len);

int solve_with(char *input, int (*pred)(char *input, int len));
int isGood1(char *input, int len);
int isGood2(char *input, int len);

int main() {
  FILE *fp;
  char *input = malloc(LINE_LEN * LINES);

  fp = fopen(FILENAME, "r");
  for (int i = 0; i < LINES; i++) {
    fscanf(fp, "%s[\n]", &input[i * LINE_LEN]);
  }

  fclose(fp);

  example();
  answer(input, 0);

  printf("Part 1: %d\n", solve_with(input, isGood1));
  printf("Part 2: %d\n", solve_with(input, isGood2));
}

int solve_with(char *input, int (*pred)(char *input, int len)) {
  char *curr = input;
  int count = 0;
  for (int i = 0; i < LINES * LINE_LEN; i += LINE_LEN) {
    curr = input + i;
    if (pred(curr, LINE_LEN) == 1) {
      count++;
    }
  }
  return count;
}

/* Returns 1 if input is good, 0 otherwise */
int isGood1(char *input, int len) {
  char prev = '\0';
  int vowels = 0;
  int twice = 0;

  for (int i = 0; i < len; i++) {
    char curr = input[i];
    if (curr == prev) {
      twice = 1;
    }
    if (curr == 'a' || curr == 'e' || curr == 'i' || curr == 'o' ||
        curr == 'u') {
      vowels++;
    }
    if ((prev == 'a' && curr == 'b') || (prev == 'c' && curr == 'd') ||
        (prev == 'p' && curr == 'q') || (prev == 'x' && curr == 'y')) {
      return 0;
    }
    prev = curr;
  }

  if (vowels >= 3 && twice == 1) {
    return 1;
  } else {
    return 0;
  }
}

/* Returns 1 if input is good, 0 otherwise */
int isGood2(char *input, int len) {
  if (len < 4) {
    return 0;
  }

  int counts[26] = {0};
  for (int i = 0; i < len; i++) {
    counts[input[i] - 'a']++;
  }

  int hasPair = 0;
  for (int i = 0; i < len - 2; i++) {
    if (counts[input[i] - 'a'] <= 1) {
      continue;
    }

    char curr = input[i];
    char next = input[i + 1];
    for (int j = i + 2; j < len - 1; j++) {
      if (curr == input[j] && next == input[j + 1]) {
        hasPair = 1;
        break;
      }
    }
    if (hasPair == 1) {
      break;
    }
  }

  int hasAba = 0;
  for (int i = 0; i < len - 2; i++) {
    if (input[i] == input[i + 2]) {
      hasAba = 1;
      break;
    }
  }

  if (hasPair == 1 && hasAba == 1) {
    return 1;
  } else {
    return 0;
  }
}

void example() {

  struct Case {
    int expect;
    char *input;
  };

  struct Case cases[5] = {
      {1, "ugknbfddgicrmopn"}, {1, "aaa"},
      {0, "jchzalrnumimnmhp"}, {0, "haegwjzuvuyypxyu"},
      {0, "dvszwmarrgswjxmb"},
  };

  for (int i = 0; i < 5; i++) {
    struct Case c;
    c = cases[i];
    assert(c.expect == isGood1(c.input, strlen(c.input)));
  }

  struct Case cases2[6] = {
      {1, "qjhvhtzxzqqjkmpb"}, {1, "xxyxx"}, {0, "uurcxstgmygtbstg"},
      {0, "ieodomkazucvgmuy"}, {0, "aaa"},   {1, "aaaa"},
  };

  for (int i = 0; i < 6; i++) {
    struct Case c;
    c = cases2[i];
    assert(c.expect == isGood2(c.input, strlen(c.input)));
  }
  printf("All example tests passed.\n");
}

void answer(void *in, int len) {
  char *input = (char *)in;
  (void)len;
  assert(238 == solve_with(input, isGood1));
  assert(69 == solve_with(input, isGood2));
  printf("All answers checked.\n");
}
