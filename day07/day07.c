#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "day07.in"
#define LINES 339
#define LINE_BUF_SIZE 20
#define ASSOC_ARR_SIZE 26 * 26

enum Operation { AND, OR, LSHIFT, RSHIFT, NOT, ASSIGN };

struct Node {
  char *name;
  int *first; // idx of associative array
  enum Operation action;
  int *second; // idx of associative array
  int value;
};

void example();
void answer(void *in, int len);

struct Node *parse() {
  FILE *fp;
  struct Node *input = calloc(ASSOC_ARR_SIZE, sizeof(struct Node));

  fp = fopen(FILENAME, "r");
  for (size_t i = 0; i < LINES; i++) {
    char lineBuf[LINE_BUF_SIZE];

    char nameBuf[3];
    char actionBuf[7]; // holds up to `LSHIFT`

    int idx;

    char *first = NULL;
    bool hasFirst = false;

    char *second = NULL;
    bool hasSecond = false;

    char *valueStr = NULL;
    int value;
    bool hasValue = false;

    char *actionStr = NULL;
    bool hasAction = false;

    assert(NULL != fgets(lineBuf, LINE_BUF_SIZE, fp));
    // printf("%s\n", buf);

    char *ptr = strchr(lineBuf, '-'); // first char of `->`
    assert(NULL != ptr);
    sscanf(ptr + 3, "%s", nameBuf);
    printf("Name: %s\n", nameBuf);
    *(ptr - 1) = '\0'; // terminate the string before `->`

    assert(strlen(nameBuf) <= 2);
    if (strlen(nameBuf) == 1) {
      idx = nameBuf[0] - 'a';
    } else {
      idx = (nameBuf[0] - 'a') * 26 + (nameBuf[1] - 'a');
    }
    printf("idx: %d\n", idx);

    int tokensLeft = 3;

    int j = 0;
    while (lineBuf[j] != '\0') {
      bool isName = false;
      bool isAction = false;
      bool isValue = false;
      if (j == 0 && islower(lineBuf[j]) != 0) {
        // printf("checking first\n");
        first = calloc(3, sizeof(char));
        sscanf(lineBuf + j, "%s", first);
        j += strlen(first);
        assert(strlen(first) <= 2);
        // printf("first:%s\n", first);
        continue;
      }
      if (islower(lineBuf[j]) != 0 && !hasSecond) {
        // printf("checking second\n");
        second = calloc(3, sizeof(char));
        sscanf(lineBuf + j, "%s", second);
        j += strlen(second);
        assert(strlen(second) <= 2);
        // printf("second:%s\n", second);
        continue;
      }
      if (isupper(lineBuf[j]) != 0) {
        if (tokensLeft == 3) {
          // a `NOT` action
          tokensLeft -= 2;
        } else {
          tokensLeft--;
        }
        // printf("checking action\n");
        actionStr = calloc(8, sizeof(char));
        sscanf(lineBuf + j, "%s", actionStr);
        j += strlen(actionStr);
        // printf("action:%s\n", actionStr);
        continue;
      }
      if (isdigit(lineBuf[j]) != 0 && !hasValue) {
        // printf("checking value\n");
        valueStr = calloc(6, sizeof(char));
        sscanf(lineBuf + j, "%s", valueStr);
        j += strlen(valueStr);
        value = atoi(valueStr);
        // printf("value:%d\n", value);
        continue;
      }

      // printf("whitespace j:%d\n", j);
      j++;
    }

    // printf("%s %s \n", name, actionStr);

    input[idx].name = nameBuf;
    enum Operation action;
    switch (actionStr[0]) {
    case 'A':
      action = AND;
      break;
    case 'O':
      action = OR;
      break;
    case 'L':
      action = LSHIFT;
      break;
    case 'R':
      action = RSHIFT;
      break;
    case 'N':
      action = NOT;
      break;
    case '-':
      action = ASSIGN;
      break;
    default:
      printf("unrecognized action: %s\n", actionStr);
      exit(1);
    }
    input[idx].action = action;

    printf("%s %s %d %d\n", first, second, value, action);

    if (i == 9) {
      break;
    }
  }

  fclose(fp);

  return input;
}

int main() {
  struct Node *input = parse();

  // example();
  // answer(input, 0);

  // printf("Part 1: %d\n", solve_with(input, LINES, part1_solver));
  // printf("Part 2: %d\n", solve_with(input, LINES, part2_solver));

  free(input);
}

// void example() {
//   struct Instruction example[3] = {
//       (struct Instruction){
//           .action = 1, .topL = {.x = 0, .y = 0}, .botR = {.x = 999, .y =
//           999}},
//
//       (struct Instruction){
//           .action = 2, .topL = {.x = 0, .y = 0}, .botR = {.x = 999, .y = 0}},
//
//       (struct Instruction){.action = 0,
//                            .topL = {.x = 499, .y = 499},
//                            .botR = {.x = 500, .y = 500}}};
//
//   assert(999 * 1000 - 4 == solve_with(example, 3, part1_solver));
//
//   printf("All example tests passed.\n");
// }
//
// void answer(void *in, int len) {
//   struct Instruction *input = (struct Instruction *)in;
//   (void)len;
//   assert(569999 == solve_with(input, LINES, part1_solver));
//   assert(17836115 == solve_with(input, LINES, part2_solver));
//   printf("All answers checked.\n");
// }
