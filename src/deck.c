#include <stdlib.h>
#include <stdio.h>
#include "deck.h"
#include "panic.h"

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
                int final_pos = k * TOTAL_SUITS * TOTAL_SYMBOLS + deck_pos;
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

card_t *discard(shoe_t *shoe)
{
    if (shoe->current_card == DECK_SIZE * shoe->total_decks)
        panic("Attempted to draw a card from an empty deck.");
    return shoe->cards[shoe->current_card++];
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

int is_shoe_finished(shoe_t *shoe)
{
    int total_size = DECK_SIZE * shoe->total_decks;
    // This is generally decided by a casino, making the cut card
    // appear 7 from the end for the sake of the simulation. Shouldn't
    // affect results.
    return total_size - shoe->current_card <= 7;
}

void print_card_value(card_t *card)
{
    if (card == NULL)
        printf("NONE");
    else
    {
        printf("%c%c", card->suit, card->symbol);
    }
}

void print_shoe(shoe_t *shoe)
{
    int last_index = DECK_SIZE * shoe->total_decks - 1;
    for (int i = 0; i < last_index; i++)
    {
        print_card_value(shoe->cards[i]);
        printf(", ");
    }
    print_card_value(shoe->cards[last_index]);
    printf("\n");
}
