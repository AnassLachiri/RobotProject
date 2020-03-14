#include <stdlib.h>
#include "trace.h"

void freeTrace(Trace * trace, int x, int y){    // Reinitialiser la liste chainée du chemin
    trace->x = x;
    trace->y = y;
    trace->next = NULL;
}