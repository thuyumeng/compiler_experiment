#include <stdio.h>
#include "lex.h"
#include "parser.h"

void statements()
{
    /* statements -> expression SEMI
    *              | expression SEMI statements
    */
   while(!match(EOI))
   {
       expression();

       if (match(SEMI))
       {
           advance();
       }
       else
       {
           fprintf(stdout, "%d: Inserting missing semicolon\n", yylineno);
       }
   }
}

void expression()
{
    /* expression -> term expression' */
    if(!legal_lookahead(NUM_OR_ID, LP, 0))
    {
        return;
    }
    term();
    while(match(PLUS))
    {
        advance();
        term();
    }
}

void term()
{
    /* term -> factor term' */
    if (!legal_lookahead(NUM_OR_ID, LP, 0))
    {
        return;
    }
    factor();
    while(match(TIMES))
    {
        advance();
        factor();
    }
}

void factor()
{
    /* factor -> NUM_OR_ID
    *          | LP expression RP
    */
   if(!legal_lookahead(NUM_OR_ID, LP, 0))
   {
       return;
   }
   if(match(NUM_OR_ID))
   {
       advance();
   }
   else if (match(LP))
   {
       advance();
       expression();
       if(match(RP))
       {
           advance();
       }
       else
       {
           fprintf(stdout, "%d: Mismatched parenthesis\n", yylineno);
       }
   }
   else
   {
       fprintf(stdout, "%d Number or identifier expected\n", yylineno);
   }
}