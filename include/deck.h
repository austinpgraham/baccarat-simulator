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
    card_t **cards;
} shoe_t;

shoe_t *create_shoe(int total_decks);
void shuffle(shoe_t *shoe);
void destroy_shoe(shoe_t *shoe);

#endif // DECK_H
