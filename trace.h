#ifndef TRACE_H
#define TRACE_H

typedef struct _Trace{
    int x;
    int y;
    struct _Trace * next;
} Trace;


void freeTrace(Trace * trace, int x, int y); 

#endif