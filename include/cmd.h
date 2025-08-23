#ifndef MENU_H
#define MENU_H

extern const int DEFAULT_NUM_SHOES;
extern const int DEFAULT_NUM_DECKS;
extern const char *DEFAULT_STRATEGY;

typedef struct
{
    int show_help;
    int num_shoes;
    int num_decks;
    const char *strategy;
} menuoptions_t;

void display_help_menu();
int parse_command_line(int argc, char *argv[], menuoptions_t *options);

#endif // MENU_H
