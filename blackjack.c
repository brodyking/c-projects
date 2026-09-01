#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

typedef struct {
  int total;
  int standon;
  Deck deck;
  bool stand;
  bool bust;
  bool turn;
} Player;

void generate_title_from_value(Card *card) {
  snprintf(card->title, sizeof(card->title), "%d of %s", card->value,
           card->suit);
}

void generate_title_from_fc(Card *card, char face[]) {
  snprintf(card->title, sizeof(card->title), "%s of %s", face, card->suit);
}

void debug_print_deck(Deck *deck) {
  for (int c = 0; c < deck->length; c++) {
    printf("%s\n", deck->cards[c].title);
  }
}

void print_card(Card *card) { printf("%s, ", card->title); }

void print_hand(Player *player) {
  printf("(%d) ", player->total);
  for (int c = 0; c < player->deck.length; c++) {
    print_card(&player->deck.cards[c]);
  }
  printf("\n");
}

void print_hidden_hand(Player *player) {
  printf("(? + %d) ", player->deck.cards[0].value);
  print_card(&player->deck.cards[0]);
  printf("Unknown");
  printf("\n");
}

void print_everyones_hands(Player *player, Player *dealer) {

  printf("\nYour hand: ");
  print_hand(player);
  printf("Dealer hand: ");
  if (player->turn) {
    print_hidden_hand(dealer);
  } else {
    print_hand(dealer);
  }
}

void generate_deck(Deck *deck) {

  const char suits[4][32] = {"Diamonds", "Hearts", "Clubs", "Spades"};

  int pos = 0;

  for (int s = 0; s < 4; s++) {

    // cards 210
    for (int value = 2; value < 11; value++) {
      Card card = {.value = value, .ace = false};
      strcpy(card.suit, suits[s]);
      generate_title_from_value(&card);
      deck->cards[pos++] = card;
    }

    char face_cards[3][32] = {"Jack", "Queen", "King"};

    // cards jack-king
    for (int f = 0; f < 3; f++) {
      Card card = {.value = 10, .ace = false};
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

void shuffle_deck(Deck *deck) {
  for (int i = 0; i < deck->length - 1; i++) {
    int tomovex = i + rand() % (deck->length - i);
    Card tomovecard = deck->cards[tomovex];
    deck->cards[tomovex] = deck->cards[i];
    deck->cards[i] = tomovecard;
  }
}

void deal_player(Player *player, Deck *deck) {
  int rand_i = rand() % deck->length;
  Card card = deck->cards[rand_i];
  player->deck.cards[player->deck.length++] = card;
  player->total += card.value;
  for (int i = rand_i + 1; i < deck->length; i++) {
    deck->cards[i - 1] = deck->cards[i];
  }
  deck->length--;
}

void check_bust_and_aces(Player *player) {

  for (int c = 0; c < player->deck.length && player->total > 21; c++) {
    if (player->deck.cards[c].ace) {
      player->deck.cards[c].ace = false;
      player->total = player->total - 10;
      break;
    }
  }

  if (player->total > 21) {
    player->bust = true;
  }
}

void deal_initial_hands(Player *player, Player *dealer, Deck *deck) {
  for (int i = 0; i < 2; i++) {
    deal_player(player, deck);
    deal_player(dealer, deck);
  }
  check_bust_and_aces(player);
  check_bust_and_aces(dealer);
}

int main() {

  srand(time(NULL));

  Player dealer = {.standon = 17, .stand = false, .turn = false};
  Player player = {.standon = 21, .stand = false, .turn = true};

  Deck deck = {.length = 52};

  generate_deck(&deck);

  shuffle_deck(&deck);

  deal_initial_hands(&player, &dealer, &deck);

  print_everyones_hands(&player, &dealer);

  while ((player.standon > player.total) && (!player.stand) && (!player.bust)) {
    char action;
    printf("\nMake your move (h/s): ");
    if (scanf(" %c", &action) != 1)
      break;
    switch (action) {
    case 'h':
      deal_player(&player, &deck);
      check_bust_and_aces(&player);
      print_everyones_hands(&player, &dealer);
      break;
    case 's':
      player.stand = true;
      break;
    }
  }

  player.turn = false;

  if (player.bust && !player.stand) {
    printf("\nYou bust!\n");
    return 0;
  }

  dealer.turn = true;

  while ((dealer.standon > dealer.total) && (!dealer.stand) && (!dealer.bust) &&
         (!player.bust)) {
    deal_player(&dealer, &deck);
    check_bust_and_aces(&dealer);
    print_everyones_hands(&player, &dealer);
  }

  print_everyones_hands(&player, &dealer);

  if ((player.total > dealer.total) || dealer.bust) {
    printf("\nYou won!\n");
  } else if (player.total == dealer.total) {
    printf("\nYou pushed!\n");
  } else {
    printf("\nYou lost!\n");
  }

  return 0;
}
