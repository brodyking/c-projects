#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int total;
  int standon;
} Player;

typedef struct {
  int value;
  char suit[32];
  char title[32];
  bool ace;
} Card;

typedef struct {
  Card cards[52];
  int length;
} Deck;

void generate_title_from_value(Card *card) {
  snprintf(card->title, sizeof(card->title), "%d of %s", card->value,
           card->suit);
}

void generate_title_from_fc(Card *card, char face[]) {
  snprintf(card->title, sizeof(card->title), "%s of %s", face, card->suit);
}

void print_deck(Deck *deck) {
  for (int c = 0; c < deck->length; c++) {
    printf("%s\n", deck->cards[c].title);
  }
}

void deal_deck(Deck *deck) {

  const char suits[4][32] = {"Diamonds", "Hearts", "Clubs", "Spades"};

  int pos = 0;

  for (int s = 0; s < 4; s++) {

    // cards 210
    for (int value = 2; value < 11; value++) {
      Card card;
      card.value = value;
      strcpy(card.suit, suits[s]);
      generate_title_from_value(&card);
      deck->cards[pos++] = card;
    }

    char face_cards[4][32] = {"Jack", "Queen", "King"};

    // cards jack-king
    for (int f = 0; f < 3; f++) {
      Card card = {.value = 10};
      strcpy(card.suit, suits[s]);
      generate_title_from_fc(&card, face_cards[f]);
      deck->cards[pos++] = card;
    }

    // ace
    Card ace = {.value = 11, .ace = true};
    strcpy(ace.suit, suits[s]);
    generate_title_from_fc(&ace, "Ace");
    deck->cards[pos++] = ace;
  }
}

int main() {

  Player dealer = {.standon = 17};
  Player player = {.standon = 21};

  Deck deck = {.length = 52};

  deal_deck(&deck);

  print_deck(&deck);
}
