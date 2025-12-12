#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "deck.h"
#include "hand.h"
#include "panic.h"

const int INITIAL_CARD_COUNT = 2;
const int MAX_SCORE_MODULO = 10;
const int CARDS_TO_BURN = 3;

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

card_t *draw_banker_third_card(int banker_score, hand_t *banker_hand, card_t *player_third_card, shoe_t *shoe)
{
    int player_stands = player_third_card == NULL;
    if ((player_stands && banker_score <= 5) || banker_score <= 2)
    {
        return draw_card(banker_hand, shoe);
    }
    for (int i = 0; i < 3; i++)
    {
        int banker_score_threshold = i + 3; // We start from three, and only draw up until 6.
        int minimum_draw_threshold = i * 2; // The minimum card value required on the player's third for the bank to draw.
        if (banker_score == banker_score_threshold && !player_stands && player_third_card->value >= minimum_draw_threshold && player_third_card->value <= 7)
        {
            return draw_card(banker_hand, shoe);
        }
    }
    return NULL;
}

winner_t play_hand(hand_t *player_hand, hand_t *banker_hand, shoe_t *shoe)
{
    int player_score = 0;
    int banker_score = 0;

    // Deal out two cards for both the player and banker, alternating
    // between the player and banker;
    for (int current_card = 0; current_card < 2; current_card++)
    {
        card_t *next_card = draw_card(player_hand, shoe);
        player_score = next_card->value;
        next_card = draw_card(banker_hand, shoe);
        banker_score = next_card->value;
    }

    // Neither score can go above 9. If two digits, take the one's place.
    player_score %= MAX_SCORE_MODULO;
    banker_score %= MAX_SCORE_MODULO;

    // If both hands are not natural, we need to draw a third card. If one of
    // them is, we calculate the score right away.
    if (!is_natural(player_score) && !is_natural(banker_score))
    {
        int player_stands = player_score <= 5;
        card_t *player_third_card = NULL;
        if (!player_stands)
        {
            player_third_card = draw_card(player_hand, shoe);
            player_score = (player_score + player_third_card->value) % MAX_SCORE_MODULO;
        }

        int banker_stands = banker_score == 7 || (player_stands && banker_score == 6);
        if (!banker_stands)
        {
            card_t *banker_third_card = draw_banker_third_card(banker_score, banker_hand, player_third_card, shoe);
            if (banker_third_card != NULL)
            {
                banker_score = (banker_score + banker_third_card->value) % MAX_SCORE_MODULO;
            }
        }
    }

    // Determine who won!
    winner_t winner = determine_winner(player_score, banker_score);

    return winner;
}

void print_game_result(winner_t winner, hand_t *player_hand, hand_t *banker_hand)
{
    printf("HAND RESULT\n");
    printf("---------\n");
    printf("WINNER: %s\n", winner == BANKER ? "BANKER" : "PLAYER");
    printf("PLAYER HAND: ");
    print_hand(player_hand);
    printf("BANKER_HAND: ");
    print_hand(banker_hand);
    printf("---------\n");
}

void play_shoe(shoe_t *shoe)
{
    hand_t *player_hand = init_hand();
    hand_t *banker_hand = init_hand();

    printf("Burning %d cards...\n", CARDS_TO_BURN);
    for (int i = 0; i < CARDS_TO_BURN; i++)
    {
        discard(shoe);
    }

    int should_stop = 0;
    while (!should_stop)
    {
        clear_hand(player_hand);
        clear_hand(banker_hand);
        winner_t hand_winner = play_hand(player_hand, banker_hand, shoe);
        print_game_result(hand_winner, player_hand, banker_hand);
        should_stop = is_shoe_finished(shoe);
    }

    free_hand(player_hand);
    free_hand(banker_hand);
}
