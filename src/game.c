#include <stdlib.h>
#include "game.h"
#include "deck.h"
#include "hand.h"

const int MAX_CARDS_PER_HAND;
const int INITIAL_CARD_COUNT = 2;
const int MAX_SCORE_MODULO = 10;

int is_natural(int score)
{
    return score == 8 || score == 9;
}

winner_t determine_winner(int player_score, int banker_score)
{
    if (player_score == banker_score)
        return TIE;

    int player_diff = 9 - player_score;
    int banker_diff = 9 - banker_score;

    if (player_diff < banker_diff)
        return PLAYER;

    return BANKER;
}

winner_t play_shoe(shoe_t *shoe)
{
    hand_t *player_hand = init_hand();
    hand_t *banker_hand = init_hand();

    int player_score = 0;
    int banker_score = 0;

    // Deal out two cards for both the player and banker, alternating
    // between the player and banker;
    for (int current_card = 0; current_card < MAX_CARDS_PER_HAND; current_card++)
    {
        draw_card(player_hand, shoe);
        player_score = player_hand->cards[current_card]->value;
        draw_card(banker_hand, shoe);
        banker_score = banker_hand->cards[current_card]->value;
    }

    // Neither score can go above 9. If two digits, take the one's place.
    player_score %= MAX_SCORE_MODULO;
    banker_score %= MAX_SCORE_MODULO;

    // If both hands are not natural, we need to draw a third card. If one of
    // them is, we calculate the score right away.
    if (!is_natural(player_score) && !is_natural(banker_score))
    {
    }

    // Determine who won!
    winner_t winner = determine_winner(player_score, banker_score);

    free_hand(player_hand);
    free_hand(banker_hand);

    return winner;
}
