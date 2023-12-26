#include <assert.h>
#include <stdio.h>

struct box {
  int l, w, h;
};

void example();
void answer(void *in, int len);

int part1(struct box *input, int len);
int part2(struct box *input, int len);

int main() {
  FILE *fp;
  struct box input[1000];

  fp = fopen("day02.in", "r");
  for (int i = 0; i < 1000; i++) {
    int x, y, z;
    fscanf(fp, "%d%*c%d%*c%d\n", &x, &y, &z);
    input[i] = (struct box){x, y, z};
  }

  example();
  answer(input, 1000);

  printf("Part 1:%d\n", part1(input, 1000));
  printf("Part 2:%d\n", part2(input, 1000));

  fclose(fp);
}

int part1(struct box *input, int len) {
  int sum = 0;
  for (int i = 0; i < len; i++) {
    struct box b = input[i];
    int x = b.l * b.w;
    int y = b.w * b.h;
    int z = b.h * b.l;
    int min = x < y ? (x < z ? x : z) : (y < z ? y : z);
    sum += 2 * x + 2 * y + 2 * z + min;
  }
  return sum;
}

int part2(struct box *input, int len) {
  int sum = 0;
  for (int i = 0; i < len; i++) {
    struct box b = input[i];
    int x = b.l + b.w;
    int y = b.w + b.h;
    int z = b.h + b.l;
    int min = x < y ? (x < z ? x : z) : (y < z ? y : z);
    sum += b.l * b.w * b.h + 2 * min;
  }
  return sum;
}

void example() {
  struct box input[2] = {{2, 3, 4}, {1, 1, 10}};
  assert(part1(input, 2) == 58 + 43);
  assert(part2(input, 2) == 34 + 14);
}

void answer(void *in, int len) {
  struct box *input = (struct box *)in;
  assert(part1(input, len) == 1586300);
  assert(part2(input, len) == 3737498);
}
