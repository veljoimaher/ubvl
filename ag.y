%{ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"
#define YYDEBUG 1

struct list *global;

void yyerror(const char *str)
{
        fprintf(stderr, "error: %s\n", str);
        exit(2);
}

main()
{
        yyparse();
        printf("Success\n");
        return 0;
}

int cnt = 0;
 %}
%token t_end t_isnum t_let t_fun t_not t_if t_else ident t_assign t_in t_tail t_equals t_and t_head num t_isfun t_islist t_then


%start StartProgram

/*
@autosyn  name
@autoinh  definition variable
*/
@autoinh variable
@autosyn let
@attributes { char *name; } ident
@attributes { struct list *variable; struct list *let; } LetExpr 
@attributes { struct list *variable; } Expr Term Ops DotTerm MulTerm PlusTerm AndTerm
@attributes { struct list *idef; struct list *sdef; } Def Lambda
@attributes { struct list *idef; } Program
@attributes { int val; } num

@traversal @postorder dbg
@traversal @preorder err

%%
StartProgram	: Program
			@{	
				@i @Program.idef@ = list_create ();
			@}
		;
Program         : 
                        @{
                        @}
                | Def ';' Program
                        @{
                                /* can't find a way to propagate father nodes global variables down the drain.. :( */
                                /*
				@i @Program.0.sdef@ = list_merge (@Def.sdef@, @Program.1.sdef@); 
				@i @Def.idef@ = list_merge (@Program.0.sdef@, @Program.1.idef@);
				@i @Program.0.idef@ = @Program.1.sdef@; 
				*/
				@i @Program.1.idef@ = @Def.sdef@;
                                @i @Def.idef@ = list_merge (@Program.0.idef@, @Def.sdef@);
			@}
                ;
Def             : ident '=' Lambda
                        @{     
                                @i @Def.sdef@ = insert_elem (DEFINITION, @Lambda.sdef@, @ident.name@, 10); 
                                @i @Lambda.idef@ = @Def.idef@;
                        @}
                ;
Lambda          : t_fun ident t_assign Expr t_end
                        @{
				@i @Lambda.sdef@ = list_create (); 
                                @i @Expr.variable@ = insert_elem (PARAMETER, @Lambda.idef@, @ident.name@, 1);
                        @}
                ;
Expr            : t_if Expr t_then Expr t_else Expr t_end
                        @{
                                /* simply pass on what we already have */
                                @i @Expr.1.variable@ = @Expr.0.variable@;
                                @i @Expr.2.variable@ = @Expr.0.variable@;
                                @i @Expr.3.variable@ = @Expr.0.variable@;
                        @}
                | Lambda
                        @{
                                /* simply pass on what we already have */
                                @i @Lambda.idef@ = @Expr.variable@;
                        @}
		| LetExpr
                | Ops
                | Term '+' Term PlusTerm
                | Term '-' Term
                | Term '*' Term MulTerm
                | Term t_and Term AndTerm
                | Term '.' Term DotTerm
                | Term '<' Term
                | Term '=' Term
                | Expr Term
                        @{
                                /* simply pass on what we already have */
                                @i @Expr.1.variable@ = @Expr.0.variable@;
                        @}
                ;

LetExpr         : t_let ident '=' Expr t_in Expr t_end
                        @{
                                /* simply pass on what we already have */
                                @i @Expr.variable@ = @LetExpr.variable@;

                                /* @Expr.2.variable@ gets everything from before (@Expr.0.variable@) and a new element */
                                @i @LetExpr.let@ = insert_elem (VARIABLE, list_create (), @ident.name@, 3);
                                @i @Expr.1.variable@ = insert_elem (VARIABLE, @LetExpr.variable@, @ident.name@, 4);
                        @}
                ;


Ops             : t_not Ops
                | t_head Ops
                | t_tail Ops
                | t_isnum Ops
                | t_islist Ops
                | t_isfun Ops
                | Term
                ;
DotTerm         : 
                | DotTerm '.' Term
                ;
AndTerm         : 
                | AndTerm t_and Term
                ;
PlusTerm        : 
                | PlusTerm '+' Term
                ;
MulTerm         : 
                | MulTerm '*' Term
                ;
Term            : '(' Expr ')'
                | num
                | ident
                        @{
                                @err isPresent (@Term.variable@, @ident.name@);
                        @}
                ;
%%
