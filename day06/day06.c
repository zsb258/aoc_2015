#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define FILENAME "day06.in"
#define LINES 300
#define GRID_SIZE 1000

struct Instruction {
  int action;
  struct Point {
    int x;
    int y;
  } topL, botR;
};

void example();
void answer(void *in, int len);

int solve_with(struct Instruction *input, int len,
               void (*solver)(int *grid, int index, int action));
void part1_solver(int *grid, int index, int action);
void part2_solver(int *grid, int index, int action);

struct Instruction *parse() {
  FILE *fp;
  struct Instruction *input = malloc(sizeof(struct Instruction) * LINES);

  fp = fopen(FILENAME, "r");
  for (int i = 0; i < LINES; i++) {
    char c;
    for (int i = 0; i < 7; i++) {
      // 7th char:
      // 'n' -> turn on
      // 'f' -> turn off
      // ' ' -> toggle
      fscanf(fp, "%c", &c);
    }

    int action;
    int step;
    switch (c) {
    case 'n':
      action = 1;
      step = 1;
      break;

    case 'f':
      action = 0;
      step = 2;
      break;

    case ' ':
      action = 2;
      step = 0;
      break;

    default:
      assert(0 && "Invalid action");
    }

    for (int i = 0; i < step; i++) {
      // shift pointer to start of coordinates
      fscanf(fp, "%c", &c);
    }

    int x1, y1, x2, y2;
    fscanf(fp, "%d%*c%d%*s%d%*c%d\n", &x1, &y1, &x2, &y2);

    input[i] = (struct Instruction){.action = action,
                                    .topL = {.x = x1, .y = y1},
                                    .botR = {.x = x2, .y = y2}};
  }

  fclose(fp);

  return input;
}

int main() {
  struct Instruction *input = parse();

  example();
  answer(input, 0);

  printf("Part 1: %d\n", solve_with(input, LINES, part1_solver));
  printf("Part 2: %d\n", solve_with(input, LINES, part2_solver));

  free(input);
}

int solve_with(struct Instruction *input, int len,
               void (*solver)(int *grid, int index, int action)) {
  int *grid = calloc(GRID_SIZE * GRID_SIZE, sizeof(int));
  for (int i = 0; i < len; i++) {
    struct Instruction curr = input[i];

    for (int x = curr.topL.x; x <= curr.botR.x; x++) {
      for (int y = curr.topL.y; y <= curr.botR.y; y++) {
        int index = x * GRID_SIZE + y;
        solver(grid, index, curr.action);
      }
    }
  }

  int count = 0;
  for (int i = 0; i < GRID_SIZE * GRID_SIZE; i++) {
    count += grid[i];
  }

  free(grid);

  return count;
}

void part1_solver(int *grid, int index, int action) {
  switch (action) {
  case 0:
    grid[index] = 0;
    break;
  case 1:
    grid[index] = 1;
    break;
  case 2:
    grid[index] = !grid[index];
    break;
  default:
    assert(0 && "Invalid action");
  }
}

void part2_solver(int *grid, int index, int action) {
  switch (action) {
  case 0:
    grid[index] -= (grid[index] > 0 ? 1 : 0);
    break;
  case 1:
    grid[index] += 1;
    break;
  case 2:
    grid[index] += 2;
    break;
  default:
    assert(0 && "Invalid action");
  }
}

void example() {
  struct Instruction example[3] = {
      (struct Instruction){
          .action = 1, .topL = {.x = 0, .y = 0}, .botR = {.x = 999, .y = 999}},

      (struct Instruction){
          .action = 2, .topL = {.x = 0, .y = 0}, .botR = {.x = 999, .y = 0}},

      (struct Instruction){.action = 0,
                           .topL = {.x = 499, .y = 499},
                           .botR = {.x = 500, .y = 500}}};

  assert(999 * 1000 - 4 == solve_with(example, 3, part1_solver));

  printf("All example tests passed.\n");
}

void answer(void *in, int len) {
  struct Instruction *input = (struct Instruction *)in;
  (void)len;
  assert(569999 == solve_with(input, LINES, part1_solver));
  assert(17836115 == solve_with(input, LINES, part2_solver));
  printf("All answers checked.\n");
}
