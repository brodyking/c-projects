#include "prelab8.h"

int fill_multiples(int values[], int n, int factor) {
  if (n < 1 || n > 20 || factor < 1 || factor > 1000) {
    return -1;
  }
  for (int i = 0; i < n; i++) {
    values[i] = (i + 1) * factor;
  }
  return n;
}

int sum_values(const int values[], int n) {
  if (n < 1 || n > 20) {
    return -1;
  }
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += values[i];
  }
  return sum;
}

double average_values(const int values[], int n) {
  if (n < 1 || n > 20) {
    return -1.0;
  }
  int sum = sum_values(values, n);
  return ((double)sum) / n;
}
