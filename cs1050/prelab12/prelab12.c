#include <stdio.h>
#include <string.h>

#define MAX 10

struct Animal {
  char name[30];
  int age;
  char origin[30];
};

void insert_animal(struct Animal *animals, int *count, struct Animal animal);
void sort_animals(struct Animal *animals, int count);
int oldest_matching_origin(struct Animal *animals, int count, char origin[]);

int main() {

  struct Animal tiger = {"tiger", 10, "africa"};
  struct Animal *t = &tiger;

  tiger.age = 4;
  t->age = 5;
  strcpy(t->origin, "Brazil");

  struct Animal animals[5] = {{"Leo", 5, "Africa"},
                              {"Polly", 2, "Australia"},
                              {"Splash", 3, "Japan"},
                              {"Slither", 4, "Brazil"},
                              {"Nibbles", 1, "Canada"}};

  int count = 5;

  puts("All animals");
  for (const struct Animal *p = animals; p < animals + count; p++) {
    printf("%s %d\n", p->name, p->age);
  }

  puts("Only Japan");
  for (const struct Animal *p = animals; p < animals + count; p++) {
    if (strcmp(p->origin, "Japan") == 0)
      printf("%s %d\n", p->name, p->age);
  }

  struct Animal animals2[MAX];
  int count2 = 0;

  struct Animal a1 = {"Leo", 5, "Africa"};
  struct Animal a2 = {"Polly", 2, "Australia"};
  struct Animal a3 = {"Meow", 3, "Australia"};
  insert_animal(animals2, &count2, a1);
  insert_animal(animals2, &count2, a2);
  insert_animal(animals2, &count2, a3);

  puts("new list");
  for (const struct Animal *p = animals2; p < animals2 + count2; p++) {
    printf("%s %d\n", p->name, p->age);
  }

  sort_animals(animals2, count2);

  puts("new list sorted");
  for (const struct Animal *p = animals2; p < animals2 + count2; p++) {
    printf("%s %d\n", p->name, p->age);
  }

  int oldest_index = oldest_matching_origin(animals2, count2, "Australia");
  printf("oldest animal from australia: %s\n", animals2[oldest_index].name);

  return 0;
}

void insert_animal(struct Animal *animals, int *count, struct Animal animal) {
  if (*count >= MAX)
    return;
  *(animals + *count) = animal;
  *count = *count + 1;
}

void sort_animals(struct Animal *animals, int count) {
  // bubble sort by age in ascending order
  for (size_t i = 0; i < count - 1; i++) {
    for (size_t x = 0; x < count - 1; x++) {
      if (animals[x].age > animals[x + 1].age) {
        struct Animal temp1 = animals[x];
        animals[x] = animals[x + 1];
        animals[x + 1] = temp1;
      }
    }
  }
}

int oldest_matching_origin(struct Animal *animals, int count, char origin[]) {
  int oldest_index = -1;
  int oldest_age = -1;
  for (size_t i = 0; i < (size_t)count; i++) {
    if (strcmp(animals[i].origin, origin) == 0 && animals[i].age > oldest_age) {
      oldest_age = animals[i].age;
      oldest_index = i;
    }
  }
  return oldest_index;
}
