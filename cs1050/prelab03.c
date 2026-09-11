#include <stdio.h>
#include <string.h>

int main() {

  int altitude = 0;

  for (int m = 0; m < 15; ++m) {

    if (m % 2 == 0) {
      altitude += 3;
    } else {
      altitude += 5;
    }

    char z[7];

    if (altitude < 25) {
      strcpy(z, "Base");
    } else if (altitude > 50) {
      strcpy(z, "Summit");
    } else {
      strcpy(z, "Ridge");
    }

    printf("Marker: %d: altitude = %d meteres, %s zone\n", (m + 1), altitude,
           z);
  }

  return 0;
}
