#include <stdio.h>
#include "cmd.h"
#include "rules.h"

int main(int argc, char *argv[])
{
    menuoptions_t options = {0, 1, RANDOM_STRATEGY};
    int success = parse_command_line(argc, argv, &options);
    printf("Successful: %d\n", success);
    if (!success || options.show_help)
    {
        display_help_menu();
        return success ? 0 : 1;
    }

    printf("num_shoes: %d, strategy: %s\n", options.num_shoes, options.strategy);

    return 0;
}
