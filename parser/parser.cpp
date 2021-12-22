#include <stdio.h>
#include "lex.h"
#include "parser.h"

void statements()
{
    /* statements -> expression SEMI
    *              | expression SEMI statements
    */
    expression();
    if (match(SEMI))
    {
        advance();
    }
    else
    {
        fprintf(stdout, "%d: Inserting missing semicolon\n", yylineno);
    }
    if (!match(EOI))
    {
        statements();
    }
}

void expression()
{
    /* expression -> term expression' */
    term();
    expr_prime();
}

void expr_prime()
{
    /* expressin' -> PLUS term expression'
    *              | epsilon
    */
   if (match(PLUS))
   {
       advance();
       term();
       expr_prime();
   }
}

void term()
{
    /* term -> factor term' */
    factor();
    term_prime();
}

void term_prime()
{
    /* term' -> TIMES factor term'
    *         |  epsilon
    */
   if(match(TIMES))
   {
       advance();
       factor();
       term_prime();
   }
}

void factor()
{
    /* factor -> NUM_OR_ID
    *          | LP expression RP
    */
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