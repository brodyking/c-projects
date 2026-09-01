#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void roll(int *dice1, int *dice2, int *total) {
  printf("Press enter to roll.");
  char temp = 0;
  scanf("%c", &temp);
  srand(time(NULL));
  *dice1 = rand() % 6 + 1;
  *dice2 = rand() % 6 + 1;
  *total = *dice1 + *dice2;
  printf("You rolled a %d and a %d.\n", *dice1, *dice2);
}

void loop(int point) {
  int dice1, dice2, total;
  roll(&dice1, &dice2, &total);

  // First round
  if (!point) {
    if (total == 7 || total == 11) {
      printf("You won immediately!");
    } else if (total == 2 || total == 3 || total == 12) {
      printf("You lost immediately!");
    } else {
      printf("Point: %d\n", total);
      loop(total);
    }
  } else {
    if (total == 7) {
      printf("You lost!");
    } else if (total == point) {
      printf("You won!");
    } else {
      loop(point);
    }
  }
}

int main() { loop(0); }
