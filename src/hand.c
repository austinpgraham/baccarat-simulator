#include <stdlib.h>
#include <stdio.h>
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

void clear_hand(hand_t *hand)
{
    for (int i = 0; i < MAX_CARDS_IN_HAND; i++)
    {
        hand->cards[i] = NULL;
    }
    hand->current_card = 0;
}

card_t *draw_card(hand_t *hand, shoe_t *shoe)
{
    if (hand->current_card >= MAX_CARDS_IN_HAND)
        panic("Tried to draw a card when hand is full.");
    card_t *new_card = discard(shoe);
    hand->cards[hand->current_card++] = new_card;
    return new_card;
}

void free_hand(hand_t *hand)
{
    free(hand->cards);
    free(hand);
}

void print_hand(hand_t *hand)
{
    int last_index = MAX_CARDS_IN_HAND - 1;
    for (int i = 0; i < last_index; i++)
    {
        print_card_value(hand->cards[i]);
        printf(", ");
    }

    print_card_value(hand->cards[last_index]);
    printf("\n");
}
