#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <number_of_simulations>\n", argv[0]);
        return 1;
    }
    printf("Running simulation...\n");
    return 0;
}
