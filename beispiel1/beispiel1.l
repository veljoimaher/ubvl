%{
#include "beispiel1.h"
#include "oxout.tab.h"
%}

comment		\/\/.*
number          [0-9]+
register        %r([abcd]x|[sb]p|[sd]i|[89]|1[0-5])
whitespace      [\n\t ]

%%

"+="		return (PLUSASSIGNOP);
"="		return (ASSIGNOP);
"+"		return (PLUSOP);	       
";"		return (';');
{register}	return (REGISTER); @{ @REGISTER.name@ = strdup(yytext); @}
{number}	return (NUMBER); @{ @NUMBER.val@ = atol(yytext); @}
{whitespace}+	;
{comment}	;
.		printf("Lexical error.\n"); exit(1);
