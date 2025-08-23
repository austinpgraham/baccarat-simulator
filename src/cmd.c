#include <stdio.h>
#include "cmd.h"
#include "rules.h"
#include "ds/hashset.h"
#include "ds/string.h"

const int DEFAULT_NUM_SHOES = 1;
const int DEFAULT_NUM_DECKS = 8;
const char *DEFAULT_STRATEGY = "random";

const char *HELP_SHORT = "-h";
const char *HELP_LONG = "--help";
const char *NUM_SHOES_SHORT = "-n";
const char *NUM_SHOES_LONG = "--num-shoes";
const char *NUM_DECKS_SHORT = "-d";
const char *NUM_DECKS_LONG = "--num-decks";
const char *STRATEGY_SHORT = "-s";
const char *STRATEGY_LONG = "--strategy";

void display_help_menu()
{
    printf("Usage: baccarat <options>\n");
    printf("Options:\n");
    printf("  %s, %s                  Display this help menu\n", HELP_SHORT, HELP_LONG);
    printf("  %s, %s <num>       Number of shoes to simulate (default: %d)\n", NUM_SHOES_SHORT, NUM_SHOES_LONG, DEFAULT_NUM_SHOES);
    printf("  %s, %s <num>       Number of decks to simulate (default: %d)\n", NUM_DECKS_SHORT, NUM_DECKS_LONG, DEFAULT_NUM_DECKS);
    printf("  %s, %s <strategy>   Betting strategy to use (default: '%s')\n", STRATEGY_SHORT, STRATEGY_LONG, DEFAULT_STRATEGY);
}

hashset_t *create_options_set()
{
    hashset_t *options_set = create_hashset();
    add_key(HELP_SHORT, options_set);
    add_key(HELP_LONG, options_set);
    add_key(NUM_SHOES_SHORT, options_set);
    add_key(NUM_SHOES_LONG, options_set);
    add_key(STRATEGY_SHORT, options_set);
    add_key(STRATEGY_LONG, options_set);
    return options_set;
}

int is_command(const char *command_short, const char *command_long, const char *option)
{
    return str_equal(command_short, option) || str_equal(command_long, option);
}

int is_help(const char *option)
{
    return is_command(HELP_SHORT, HELP_LONG, option);
}

int is_num_shoes(const char *option)
{
    return is_command(NUM_SHOES_SHORT, NUM_SHOES_LONG, option);
}

int is_num_decks(const char *option)
{
    return is_command(NUM_DECKS_SHORT, NUM_DECKS_LONG, option);
}

int is_strategy(const char *option)
{
    return is_command(STRATEGY_SHORT, STRATEGY_LONG, option);
}

int parse_command_line(int argc, char *argv[], menuoptions_t *options)
{
    hashset_t *options_set = create_options_set();

    int i = 1;
    while (i < argc)
    {
        if (is_help(argv[i]))
        {
            options->show_help = 1;
            return 1;
        }

        if (!set_contains(argv[i], options_set))
        {
            printf("Unknown argument: %s\n\n", argv[i]);
            return 0;
        }

        // We now know we expect another arg. So if
        // we don't have one, raise an error.
        if (i == argc)
        {
            printf("Invalid argument for %s: %s\n\n", argv[i], "");
            return 0;
        }
        else if (is_num_shoes(argv[i]))
        {
            int num_shoes = str_to_int(argv[++i]);
            if (num_shoes == 0)
            {
                printf("Number of shoes should be greater than 0.\n\n");
                return 0;
            }
            options->num_shoes = num_shoes;
        }
        else if (is_num_decks(argv[i]))
        {
            int num_decks = str_to_int(argv[++i]);
            if (num_decks == 0)
            {
                printf("Number of decks should be greater than 0.\n\n");
                return 0;
            }
            options->num_decks = num_decks;
        }
        else if (is_strategy(argv[i]))
        {
            char *strategy = argv[++i];
            if (!str_equal(strategy, RANDOM_STRATEGY) && !str_equal(strategy, DOUBLING))
            {
                printf("Invalid strategy: %s\n\n", strategy);
                return 0;
            }
            options->strategy = strategy;
        }
        i++;
    }

    free_hashset(options_set);
    return 1;
}
