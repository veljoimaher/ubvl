%{ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"
#include "tree.h"
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
@autosyn let tn
@attributes { char *name; } ident
@attributes { struct list *variable; struct list *let; } LetExpr 
@attributes { struct list *variable; struct treenode *tn; } Expr Term Ops DotTerm MulTerm PlusTerm AndTerm
@attributes { struct list *idef; struct list *sdef; struct treenode *tn; } Def Lambda
@attributes { struct list *idef; } Program
@attributes { int val; } num

@traversal @preorder err codegen

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
				@i @Program.1.idef@ = @Def.sdef@;
                                @i @Def.idef@ = list_merge (@Program.0.idef@, @Def.sdef@);
                                @codegen invoke_burm(@Def.tn@);
			@}
                
Def             : ident '=' Lambda
                        @{     
                                @i @Def.sdef@ = insert_elem (DEFINITION, @Lambda.sdef@, @ident.name@, 10); 
                                @i @Lambda.idef@ = @Def.idef@;
                                @i @Def.tn@ = new_op_node (ASGN, new_id_node (@ident.name@, @Lambda.idef@), @Lambda.tn@);
                        @}
                ;
Lambda          : t_fun ident t_assign Expr t_end
                        @{
				@i @Lambda.sdef@ = list_create (); 
                                @i @Expr.variable@ = insert_elem (PARAMETER, @Lambda.idef@, @ident.name@, 1);
                                @i @Lambda.tn@ = new_op_node(LASGN, new_id_node (@ident.name@, @Expr.variable@), @Expr.tn@); 
                        @}
                ;
Expr            : t_if Expr t_then Expr t_else Expr t_end
                        @{
                                /* simply pass on what we already have */
                                @i @Expr.1.variable@ = @Expr.0.variable@;
                                @i @Expr.2.variable@ = @Expr.0.variable@;
                                @i @Expr.3.variable@ = @Expr.0.variable@;
                                @i @Expr.0.tn@ = new_op_node (IF, NULL, NULL);
                        @}
                | Lambda
                        @{
                                /* simply pass on what we already have */
                                @i @Lambda.idef@ = @Expr.variable@;
                                @i @Expr.0.tn@ = new_op_node (THEN, NULL, NULL);
                        @}
		| LetExpr
                        @{
                                @i @Expr.0.tn@ = new_op_node (ELSE, NULL, NULL);
                        @}
                | Ops
                        @{
                                @i @Expr.0.tn@ = new_op_node (ISNUM, NULL, NULL);
                        @}
                | Term '+' Term PlusTerm
                        @{
                                @i @Expr.0.tn@ = new_op_node (ADD, NULL, NULL);
                        @}
                | Term '-' Term
                        @{
                                @i @Expr.0.tn@ = new_op_node (SUB, NULL, NULL);
                        @}
                | Term '*' Term MulTerm
                        @{
                                @i @Expr.0.tn@ = new_op_node (MUL, NULL, NULL);
                        @}
                | Term t_and Term AndTerm
                        @{
                                @i @Expr.0.tn@ = new_op_node (AND, NULL, NULL);
                        @}
                | Term '.' Term DotTerm
                        @{
                                @i @Expr.0.tn@ = new_op_node (DOT, NULL, NULL);
                        @}
                | Term '<' Term
                        @{
                                @i @Expr.0.tn@ = new_op_node (LESS, NULL, NULL);
                        @}
                | Term '=' Term
                        @{
                                @i @Expr.0.tn@ = new_op_node (EQ, NULL, NULL);
                        @}
                | Expr Term
                        @{
                                /* simply pass on what we already have */
                                @i @Expr.1.variable@ = @Expr.0.variable@;
                                @i @Expr.0.tn@ = new_op_node (EQ, NULL, NULL);
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
                @{
                                @i @DotTerm.0.tn@ = new_op_node (DOT, NULL, NULL);
                @}
                | DotTerm '.' Term
                @{
                                @i @DotTerm.0.tn@ = new_op_node (DOT, NULL, NULL);
                @}
                ;
AndTerm         : 
                @{
                                @i @AndTerm.0.tn@ = new_op_node (AND, NULL, NULL);
                @}

                | AndTerm t_and Term
                @{
                                @i @AndTerm.0.tn@ = new_op_node (AND, NULL, NULL);
                @}
                ;
PlusTerm        : 
                @{
                                @i @PlusTerm.0.tn@ = new_op_node (ADD, NULL, NULL);
                @}

                | PlusTerm '+' Term
                @{
                                @i @PlusTerm.0.tn@ = new_op_node (ADD, NULL, NULL);
                @}
                ;
MulTerm         : 
                @{
                                @i @MulTerm.0.tn@ = new_op_node (MUL, NULL, NULL);
                @}

                | MulTerm '*' Term
                @{
                                @i @MulTerm.0.tn@ = new_op_node (MUL, NULL, NULL);
                @}
                ;
Term            : '(' Expr ')'
                @{
                                @i @Term.tn@ = new_op_node (IF, NULL, NULL);
                @}
                | num
                @{
                                @i @Term.tn@ = new_num_node (@num.val@);
                @}
                | ident
                        @{
                                @err isPresent (@Term.variable@, @ident.name@);
                                @i @Term.tn@ = new_id_node (@ident.name@, @Term.variable@);
                        @}
                ;
%%
