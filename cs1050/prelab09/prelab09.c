#include "prelab09.h"

void initialize_sequences(char sequences[NUM_SEQUENCES][SEQUENCE_LENGTH]) {

  const char bases[4] = {'A', 'T', 'C', 'G'};

  for (int r = 0; r < NUM_SEQUENCES; r++) {
    for (int c = 0; c < SEQUENCE_LENGTH; c++) {
      sequences[r][c] = bases[c % 4];
    }
  }
}

int replace_base(char sequences[NUM_SEQUENCES][SEQUENCE_LENGTH],
                 int sequence_index, int position, char new_base) {

  if (sequence_index < 0 || sequence_index > 4 || position < 0 || position > 9)
    return 0;

  if (new_base != 'A' && new_base != 'T' && new_base != 'C' && new_base != 'G')
    return 0;

  sequences[sequence_index][position] = new_base;
  return 1;
}

int matching_positions(const char sequences[NUM_SEQUENCES][SEQUENCE_LENGTH],
                       int first_index, int second_index) {

  if (first_index < 0 || first_index > 4 || second_index < 0 ||
      second_index > 4)
    return -1;

  int total_matches = 0;
  for (int c = 0; c < SEQUENCE_LENGTH; c++) {
    if (sequences[first_index][c] == sequences[second_index][c])
      total_matches++;
  }
  return total_matches;
}

double similarity_percent(const char sequences[NUM_SEQUENCES][SEQUENCE_LENGTH],
                          int first_index, int second_index) {

  int matching = matching_positions(sequences, first_index, second_index);
  if (matching == -1)
    return -1.0;
  return 100.0 * ((double)matching / SEQUENCE_LENGTH);
}

int are_related(double similarity) {
  if (similarity < 0.0 || similarity > 100.0)
    return -1;
  if (similarity >= RELATIONSHIP_THRESHOLD)
    return 1;
  return 0;
}
