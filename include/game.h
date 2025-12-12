#ifndef GAME_H
#define GAME_H
#include "deck.h"

extern const int CARDS_TO_BURN;
extern const int INITIAL_CARD_COUNT;
extern const int MAX_SCORE_MODULO;

typedef enum winner
{
    PLAYER,
    BANKER,
    TIE
} winner_t;

void play_shoe(shoe_t *shoe);

#endif // GAME_H
