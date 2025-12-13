#ifndef GAME_H
#define GAME_H
#include "deck.h"
#include "hand.h"

extern const char *RANDOM_STRATEGY;
extern const char *DOUBLING;

extern const int CARDS_TO_BURN;
extern const int INITIAL_CARD_COUNT;
extern const int MAX_SCORE_MODULO;

typedef enum winner
{
    PLAYER,
    BANKER,
    TIE
} winner_t;

typedef struct
{
    int value;
    winner_t winner;
} bet_t;

void play_shoe(shoe_t *shoe, const char *strategy, int start_pot);
bet_t make_bet(const char *strategy, winner_t last_winner, bet_t *last_bet);
void print_hand_result(bet_t *bet, winner_t winner, hand_t *player_hand, hand_t *banker_hand, int result_pot);

#endif // GAME_H
