#include "array_operations.h"
#include <stdio.h>

void printarr(const int array[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d", array[i]);
  }
  printf("\n");
}

void bublesort(int array[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int k = 0; k < size - 1 - i; k++) {
      if (array[k] > array[k + 1]) {
        int val = array[k];
        array[k] = array[k + 1];
        array[k + 1] = val;
      }
    }
  }
}

int linearsearch(int element, int array[], int size) {
  for (int i = 0; i < size; i++) {
    if (array[i] == element)
      return i;
  }
  return -1;
}

int binarysearch(int element, int array[], int size) {
  int start = 0;
  int end = size - 1;
  int mid = (start + end) / 2;
  do {
    if (array[mid] == element) {
      return mid;
    }
    if (array[mid] < element) {
      start = mid + 1;
    } else {
      end = mid - 1;
    }
    mid = (start + end) / 2;
  } while (start <= end);
  return -1;
}

int main() {
  int nums[] = {1, 8, 3, 5, 1, 4};
  int size = sizeof(nums) / sizeof(nums[0]);
  puts("before sort:");
  printarr(nums, size);
  puts("after sort:");
  bublesort(nums, size);
  printarr(nums, size);
  printf("(linear) index of 9: %d\n", linearsearch(9, nums, size));
  printf("(binary) index of 8: %d\n", binarysearch(8, nums, size));
}
