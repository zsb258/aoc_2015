
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "day3.in"
#define MAX 8192

void example();
void answer(void *in, int len);

int part1(char *input, int len);
int part2(char *input, int len);

int main() {
  FILE *fp;
  char input[MAX];

  fp = fopen(FILENAME, "r");
  fscanf(fp, "%s", input);
  fclose(fp);

  example();
  answer(input, MAX);

  printf("Part 1: %d\n", part1(input, MAX));
  printf("Part 2: %d\n", part2(input, MAX));
}

int step(int *seen, char c, int *x, int *y, int wd) {
  switch (c) {
  case '^':
    ++*y;
    break;
  case 'v':
    --*y;
    break;
  case '>':
    ++*x;
    break;
  case '<':
    --*x;
    break;
  }

  assert(*x >= 0 && *x < wd);
  assert(*y >= 0 && *y < wd);
  int curr = (*x) * wd + (*y);

  if (seen[curr] == 1) {
    return 0;
  } else {
    seen[curr] = 1;
    return 1;
  }
}

int part1(char input[], int len) {
  int size = (len * 2) * (len * 2);
  int *seen = calloc(size, sizeof(int));
  int x = len, y = len;

  seen[x * (len * 2) + y] = 1;

  int count = 1;

  for (int i = 0; i < len; i++) {
    count += step(seen, input[i], &x, &y, len * 2);
  }

  return count;
}

int part2(char input[], int len) {
  int size = (len * 2) * (len * 2);
  int *seen = calloc(size, sizeof(int));
  int x1 = len, y1 = len;
  int x2 = len, y2 = len;

  seen[x1 * (len * 2) + y1] += 1;

  int count = 1;

  for (int i = 0; i < len; i++) {
    if (i % 2 == 0) {
      count += step(seen, input[i], &x1, &y1, len * 2);
    } else {
      count += step(seen, input[i], &x2, &y2, len * 2);
    }
  }
  return count;
}

void example() {

  struct Case {
    int expect;
    char *input;
  };

  struct Case cases[3] = {
      {2, "^v"},
      {4, "^>v<"},
      {2, "^v^v^v^v^v"},
  };
  struct Case cases2[3] = {
      {3, "^v"},
      {3, "^>v<"},
      {11, "^v^v^v^v^v"},
  };

  for (int i = 0; i < 3; i++) {
    struct Case c;
    c = cases[i];
    assert(c.expect == part1(c.input, strlen(c.input)));

    c = cases2[i];
    assert(c.expect == part2(c.input, strlen(c.input)));
  }
}

void answer(void *in, int len) {
  char *input = (char *)in;
  assert(part1(input, len) == 2592);
  assert(part2(input, len) == 2360);
}
