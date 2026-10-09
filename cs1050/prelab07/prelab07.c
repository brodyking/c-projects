#include "prelab07.h"
#include <stdio.h>

static int points_store(int op, int value) {
  static int total_points = 0;
  switch (op) {
  case 0: {
    return total_points;
  }
  case 1: {
    if (value < 0) {
      return -1;
    }
    total_points += value;
    return total_points;
  }
  case 2: {
    if (value <= 0) {
      return -1;
    }
    if (value > total_points) {
      return 0;
    }
    total_points -= value;
    return 1;
  }
  case 3: {
    total_points = 0;
    return 1;
  }
  case 4: {
    if (value > 3 || value < 1) {
      return -1;
    }
    total_points *= value;
    return total_points;
  }
  default: {
    return -1;
  }
  }
}

int reset_day(void) { return points_store(3, 0); }

int compute_points(int cents) {
  if (cents < 0) {
    return -1;
  }
  return cents / 100 + ((cents >= 1000) ? 2 : 0);
}

int record_purchase(int cents) {
  int earned = compute_points(cents);
  if (earned == -1) {
    return -1;
  }
  return points_store(1, earned);
}

int redeem_reward(int points_needed) { return points_store(2, points_needed); }

int bonus_points_day(int multiplier) { return points_store(4, multiplier); }

int get_total_points(void) { return points_store(0, 0); }
