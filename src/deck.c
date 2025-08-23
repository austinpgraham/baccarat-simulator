#include <stdlib.h>
#include "deck.h"

const char SUITS[] = {'S', 'C', 'H', 'D'};
const char CARD_SYMBOLS[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
const int SYMBOL_VALUES[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0};

const int TOTAL_SUITS = 4;
const int TOTAL_SYMBOLS = 13;
const int DECK_SIZE = TOTAL_SUITS * TOTAL_SYMBOLS;

shoe_t *create_shoe(int total_decks)
{
    card_t **all_decks = malloc(total_decks * DECK_SIZE * sizeof(card_t *));
    for (int k = 0; k < total_decks; k++)
    {
        for (int i = 0; i < TOTAL_SUITS; i++)
        {
            for (int j = 0; j < TOTAL_SYMBOLS; j++)
            {
                card_t *new_card = malloc(sizeof(card_t));
                new_card->suit = SUITS[i];
                new_card->symbol = CARD_SYMBOLS[j];
                new_card->value = SYMBOL_VALUES[j];
                int deck_pos = i * TOTAL_SYMBOLS + j;
                int final_pos = k * total_decks + deck_pos;
                all_decks[final_pos] = new_card;
            }
        }
    }

    shoe_t *shoe = malloc(sizeof(shoe_t));
    shoe->cards = all_decks;
    shoe->current_card = 0;
    shoe->total_decks = total_decks;
    return shoe;
}

void shuffle(int total_shuffles, shoe_t *shoe)
{
    int max_card_index = shoe->total_decks * DECK_SIZE - 1;
    for (int j = 0; j < total_shuffles; j++)
    {
        for (int i = 0; i <= max_card_index; i++)
        {
            int swap_with_index = rand() % max_card_index;
            card_t *swap_card = shoe->cards[i];
            card_t *with_card = shoe->cards[swap_with_index];
            shoe->cards[i] = with_card;
            shoe->cards[swap_with_index] = swap_card;
        }
    }
}

void destroy_shoe(shoe_t *shoe)
{
    for (int i = 0; i < TOTAL_SUITS * TOTAL_SYMBOLS; i++)
    {
        free(shoe->cards[i]);
    }
    free(shoe->cards);
    free(shoe);
}
