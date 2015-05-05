%{ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"
#define YYDEBUG 1

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

 %}
%token t_end t_isnum t_let t_fun t_not t_if t_else ident t_assign t_in t_tail t_equals t_and t_head num t_isfun t_islist t_then


%start Program

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
@attributes { int val; } num

@traversal @postorder err

%%
Program         : 
                | Program Def ';'
                        @{
                                /* Lambda definition inherited attribute (goes downwards) */
                                @i @Def.idef@ = @Def.sdef@;     
                        @}
                ;
Def             : ident '=' Lambda
                        @{      
                                /* @Def.sdef@: Lambda definition syntethized attribute (goes upwards)
                                 * insert_elem creates a new list if not-existent,
                                 * otherwise it tries to insert another element and returns a new list object:
                                 * (e.g. does not modify the list that is given as a parameter)
                                 * IF @ident.name@ already present, exit (1)
                                 * IF @ident.name@ not present, add new element with name = @ident.name@
                                        @i @Lambda.idef@ = insert_elem (DEFINITION, @Def.idef@, @ident.name@);
                                 */
                                @i @Def.sdef@ = insert_elem (DEFINITION, list_merge_to_new (@Def.idef@, @Lambda.sdef@), @ident.name@); 
                                @i @Lambda.idef@ = insert_elem (DEFINITION, @Def.idef@, @ident.name@);
                        @}
                ;
Lambda          : t_fun ident t_assign Expr t_end
                        @{
                                /* @Expr.variable@ gets @Lambda.function@ from before and new function def here */
                                @i @Expr.variable@ = insert_elem (FUNCTION, @Lambda.idef@, @ident.name@); 
                                @i @Lambda.sdef@ = insert_elem (FUNCTION, @Lambda.idef@, @ident.name@);
                        @}
                | t_fun ident t_assign LetExpr t_end
                        @{
                                /* @Expr.variable@ gets @Lambda.function@ from before and new function def here */
                                @i @LetExpr.variable@ = insert_elem (FUNCTION, @Lambda.idef@, @ident.name@); 
                                @i @Lambda.sdef@ = insert_elem (FUNCTION, list_merge_to_new (@Lambda.idef@, @LetExpr.let@), @ident.name@);
                        @}
                ;
LetExpr         : t_let ident '=' Expr t_in Expr t_end
                        @{
                                /* simply pass on what we already have */
                                @i @Expr.variable@ = @LetExpr.variable@;

                                /* @Expr.2.variable@ gets everything from before (@Expr.0.variable@) and a new element */
                                @i @Expr.1.variable@ = insert_elem (VARIABLE, @LetExpr.variable@, @ident.name@);
                                @i @LetExpr.let@ = insert_elem (VARIABLE, @LetExpr.variable@, @ident.name@);
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
