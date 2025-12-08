#ifndef GAME_H
#define GAME_H
#include "deck.h"

typedef enum winner
{
    PLAYER,
    BANKER,
    TIE
} winner_t;

winner_t play_shoe(shoe_t *shoe);

#endif // GAME_H
