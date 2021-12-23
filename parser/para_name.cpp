#include "para_name.h"
#include "lex.h"

#include <stdio.h>
#include <stdlib.h>

// 名字的栈，和控制栈的pointer
static char *Names[] = {"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7"};
static char **Namep = Names;

char *newname()
{
    // 当pop的时候要防止超限
    if (Namep >= &Names[ sizeof(Names)/sizeof(*Names) ])
    {
        fprintf(stdout, "%d: Expression too complex\n", yylineno);
        exit(1);
    }
    return (*Namep++);
}

void freename(char *s)
{
    // 同时push back时要当心underflow
    if (Namep > Names)
    {
        *--Namep = s;
    }
    else
    {
        fprintf(stdout, "%d: (Internal error) Name stack overflow\n", yylineno);
    }
}