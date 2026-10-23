#define NUM_SEQUENCES 5
#define SEQUENCE_LENGTH 10
#define RELATIONSHIP_THRESHOLD 70.0

void initialize_sequences(char sequences[NUM_SEQUENCES][SEQUENCE_LENGTH]);
int replace_base(char sequences[NUM_SEQUENCES][SEQUENCE_LENGTH],
                 int sequence_index, int position, char new_base);
int matching_positions(const char sequences[NUM_SEQUENCES][SEQUENCE_LENGTH],
                       int first_index, int second_index);
double similarity_percent(const char sequences[NUM_SEQUENCES][SEQUENCE_LENGTH],
                          int first_index, int second_index);
int are_related(double similarity);
