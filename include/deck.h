#ifndef DECK_H
#define DECK_H

extern const char SUITS[];
extern const char CARD_SYMBOLS[];
extern const int SYMBOL_VALUES[];

typedef struct
{
    char symbol;
    char suit;
    int value;
} card_t;

typedef struct
{
    int current_card;
    int total_decks;
    card_t **cards;
} shoe_t;

shoe_t *create_shoe(int total_decks);
void shuffle(int total_shuffles, shoe_t *shoe);
card_t *discard(shoe_t *shoe);
void destroy_shoe(shoe_t *shoe);
int is_shoe_finished(shoe_t *shoe);
void print_card_value(card_t *card);
void print_shoe(shoe_t *shoe);

#endif // DECK_H
