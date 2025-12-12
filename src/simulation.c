#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cmd.h"
#include "rules.h"
#include "deck.h"
#include "game.h"

const int TOTAL_SHUFFLES = 10;

int main(int argc, char *argv[])
{
    menuoptions_t options = {0, DEFAULT_NUM_SHOES, DEFAULT_NUM_DECKS, DEFAULT_STRATEGY};
    int success = parse_command_line(argc, argv, &options);
    if (!success || options.show_help)
    {
        display_help_menu();
        return success ? 0 : 1;
    }

    // Seed the simulation
    srand((unsigned int)time(NULL));

    for (int i = 0; i < options.num_shoes; i++)
    {
        printf("Playing shoe #%d...\n", i + 1);
        shoe_t *shoe = create_shoe(options.num_decks);
        shuffle(10, shoe);
        play_shoe(shoe);
        destroy_shoe(shoe);
    }

    return 0;
}
