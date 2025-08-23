#ifndef MENU_H
#define MENU_H

typedef struct
{
    int show_help;
    int num_shoes;
    const char *strategy;
} menuoptions_t;

void display_help_menu();
int parse_command_line(int argc, char *argv[], menuoptions_t *options);

#endif // MENU_H
