%option noyywrap
%{
#include <stdio.h>
#include "y.tab.h"

#define lexeme strcpy ((char *) malloc (yyleng+1), yytext)
%}

ID      [a-zA-Z][a-zA-Z0-9]*
DIGIT   [0-9]+
HEX     \$[0-9a-fA-f]+
KEY     (";"|"+"|"-"|"*"|"."|"<"|"="|"("|")")
ASGN    "->"
EQL     '='
IGNORE  [ \t\n]+
CMNT    \/\/.*

%%

{HEX}   { 
                return num; @{ @num.val@ = strtol (yytext + sizeof(char), NULL, 16); @}
        }
{DIGIT} {
                return num; @{ @num.val@ = strtol (yytext, NULL, 10); @}
        }
";"     return ';';
"+"     return '+';
"-"     return '-';
"*"     return '*';
"."     return '.';
"<"     return '<';
"="     return '=';
"("     return '(';
")"     return ')';

fun     return t_fun;
if      return t_if;
then    return t_then;
else    return t_else;
let     return t_let;
in      return t_in;
not     return t_not;
head    return t_head;
tail    return t_tail;
and     return t_and;
end     return t_end;
isnum   return t_isnum;
islist  return t_islist;
isfun   return t_isfun;

{ID}    { 
                /*return ident; @{ @ident.name@ = strdup(yytext); @} */
                return ident; @{ @ident.name@ = lexeme; @}
        }
{ASGN}  {
                return t_assign;
        }
{EQL}   {
                return t_equals;
        }
{IGNORE} {}
{CMNT}  {}
.       {
                printf ("Error\n");
                exit(1);
        }
%%
