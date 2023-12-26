
#include <stdio.h>

int part1(char *input, int len);
int part2(char *input, int len);

int main() {
  FILE *fp;
  char buff[7000];
  fp = fopen("day01.in", "r");
  fscanf(fp, "%s", buff);

  printf("Part 1:%d\n", part1(buff, 7000));
  printf("Part 2:%d\n", part2(buff, 7000));

  fclose(fp);
}

int part1(char input[], int len) {
  int left = 0;
  int right = 0;

  for (int i = 0; i < len; i++) {
    if (input[i] == '(') {
      left++;
    } else if (input[i] == ')') {
      right++;
    }
  }
  return left - right;
}

int part2(char input[], int len) {
  int i = 0;
  int curr = 0;

  for (; curr >= 0 && i < len; i++) {
    if (input[i] == '(') {
      curr++;
    } else if (input[i] == ')') {
      curr--;
    }
  }
  return i;
}
