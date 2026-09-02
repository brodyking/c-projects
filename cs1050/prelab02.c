#include <stdio.h>

int main() {
  int itemsPerCarton, cartonCount, reservedItems, workerCount;
  scanf("%d %d %d %d", &itemsPerCarton, &cartonCount, &reservedItems,
        &workerCount);

  int totalInventory = itemsPerCarton * cartonCount;
  int availableInventory = totalInventory - reservedItems;

  printf("%d %d %d %d\n", itemsPerCarton, cartonCount, reservedItems,
         workerCount);

  printf("Total inventory: %d\n", totalInventory);

  printf("Total number of items available after reserved: %d\n",
         availableInventory);

  int itemsPerWorker = availableInventory / workerCount;
  int itemsLeftover = availableInventory % workerCount;

  printf("Amount each worker recieves: %d\n", itemsPerWorker);
  printf("Amount left over: %d\n", itemsLeftover);

  int checkamount = (itemsPerWorker * workerCount) + itemsLeftover;

  printf("Check count: %d\n", checkamount);

  if (itemsLeftover == 0) {
    printf("The items divide evenly amount the workers.\n");
  } else if (itemsLeftover > 0) {
    printf("Some items remain after the workers recieve equal shares.\n");
  }
  return 0;
}
