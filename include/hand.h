#ifndef HAND_H
#define HAND_H

#include <stdlib.h>
#include "deck.h"

extern const int MAX_CARDS_IN_HAND;

typedef struct
{
    card_t **cards;
    int current_card;
} hand_t;

hand_t *init_hand();
void draw_card(hand_t *hand, shoe_t *shoe);
void free_hand(hand_t *hand);

#endif // HAND_H
