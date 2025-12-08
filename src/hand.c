#include <stdlib.h>
#include "hand.h"
#include "panic.h"

const int MAX_CARDS_IN_HAND = 3;

hand_t *init_hand()
{
    hand_t *new_hand = (hand_t *)malloc(sizeof(hand_t));
    new_hand->current_card = 0;
    new_hand->cards = (card_t **)malloc(sizeof(card_t *) * MAX_CARDS_IN_HAND);
    return new_hand;
}

void draw_card(hand_t *hand, shoe_t *shoe)
{
    if (hand->current_card >= MAX_CARDS_IN_HAND)
        panic("Tried to draw a card when hand is full.");
    hand->cards[hand->current_card++] = discard(shoe);
}

void free_hand(hand_t *hand)
{
    free(hand->cards);
    free(hand);
}
