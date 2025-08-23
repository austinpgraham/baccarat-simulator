#include <stdio.h>
#include "cmd.h"
#include "rules.h"

int main(int argc, char *argv[])
{
    menuoptions_t options = {0, DEFAULT_NUM_SHOES, DEFAULT_NUM_DECKS, DEFAULT_STRATEGY};
    int success = parse_command_line(argc, argv, &options);
    if (!success || options.show_help)
    {
        display_help_menu();
        return success ? 0 : 1;
    }

    printf("num_shoes: %d, strategy: %s\n", options.num_shoes, options.strategy);

    return 0;
}
