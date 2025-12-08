#include <stdio.h>
#include <stdlib.h>
#include "panic.h"

void panic(const char *message)
{
    fprintf(stderr, "panic: %s", message);
    exit(1);
}
