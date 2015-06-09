%{ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"
#include "tree.h"
#define YYDEBUG 1
#include "reg.h"

struct list *global;

void yyerror(const char *str)
{
        fprintf(stderr, "error: %s\n", str);
        exit(2);
}

main()
{
        yyparse();
        /* printf("Success\n"); */
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
@attributes { struct list *variable; struct list *let; struct treenode *tn; struct treenode *tnp; struct treenode *tnp1; struct treenode *var; } LetExpr 
@attributes { struct list *variable; struct treenode *tn; } Expr Term Ops DotTerm MulTerm PlusTerm AndTerm
@attributes { struct list *idef; struct list *sdef; struct treenode *tn; } Def Lambda
@attributes { struct list *idef; } Program
@attributes { int val; } num

@traversal @preorder err
@traversal @postorder codegen1
@traversal @postorder codegen
@traversal @preorder codegenpre

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
                        @}
                
Def             : ident '=' Lambda
                        @{     
                                @i @Def.sdef@ = insert_elem (DEFINITION, @Lambda.sdef@, @ident.name@, 10); 
                                @i @Lambda.idef@ = @Def.idef@;
                                @i @Def.tn@ = new_op_node (ASGN, new_id_node (@ident.name@, @Lambda.idef@), @Lambda.tn@);
				@codegen func_header (@ident.name@);
				@codegen invoke_burm (@Def.tn@);
                        @}
                ;
Lambda          : t_fun ident t_assign Expr t_end
                        @{
				@i @Lambda.sdef@ = list_create (); 
                                @i @Expr.variable@ = insert_elem (PARAMETER, @Lambda.idef@, @ident.name@, 1);
                                @i @Lambda.tn@ = new_op_node(LASGN, new_id_node (@ident.name@, reg_init(@Expr.variable@)), @Expr.tn@);
                        @}
                ;
Expr            : t_if Expr t_then Expr t_else Expr t_end
                        @{
                                /* simply pass on what we already have */
                                @i @Expr.1.variable@ = @Expr.0.variable@;
                                @i @Expr.2.variable@ = @Expr.0.variable@;
                                @i @Expr.3.variable@ = @Expr.0.variable@;
                                /* !!! Expr.0 treenode is incorrect. We will fix it for the next release !!! 
                                @codegen (new_op_node (IF, @Expr.1.tn@, new_op_node (THEN, @Expr.2.tn@, new_op_node (ELSE, @Expr.3.tn@, (struct treenode *)NULL))));
                                @codegenif invoke_burm (new_op_node (IF, @Expr.1.tn@, new_op_node (THEN, @Expr.2.tn@, new_op_node (ELSE, @Expr.3.tn@, (struct treenode *)NULL))));
                                */
                                @codegen printf ("IF THEN ELSE\n");
                                @i @Expr.0.tn@ = new_op_node (ORPHAN, new_id_node (get_label (), list_create ()), (struct treenode *)NULL);
                                @codegen invoke_burm (new_op_node (IF, @Expr.1.tn@, new_op_node (THEN, @Expr.2.tn@, @Expr.3.tn@)));
                                /*@codegen invoke_burm (new_op_node (IF, @Expr.1.tn@, (struct treenode *)NULL));
                                @codegen printf ("%s:\n", lbl);
                                @codegen invoke_burm (new_op_node (THEN, @Expr.2.tn@, (struct treenode *)NULL));
                                @codegen invoke_burm (new_op_node (ELSE, @Expr.3.tn@, (struct treenode *)NULL));
                                *//*@codegen invoke_burm (new_op_node (IF, @Expr.1.tn@, 
                                                                   new_op_node (THEN, @Expr.2.tn@, 
                                                                                       new_op_node (ELSE, @Expr.3.tn@, (struct treenode *)NULL))));
                                                                                       */
                        @}
                | Lambda
                        @{
                                /* simply pass on what we already have */
                                @i @Lambda.idef@ = @Expr.variable@;
                        @}
		| LetExpr
                        @{
                        @}
                | Ops
                        @{
                        @}
                | PlusTerm
                        @{
                              /*  @i @Expr.0.tn@ = new_op_node (ADD, @Term.0.tn@, @Term.1.tn@); */
				@i @Expr.0.tn@ = @PlusTerm.tn@;
                        @}
                | Term '-' Term
                        @{
                                @i @Expr.0.tn@ = new_op_node (SUB, @Term.0.tn@, @Term.1.tn@);
                        @}
                | MulTerm
                        @{
                                /* @i @Expr.0.tn@ = new_op_node (MUL, @Term.0.tn@, @Term.1.tn@); */
				@i @Expr.0.tn@ = @MulTerm.tn@;
                        @}
                | AndTerm
                        @{
                                /* @i @Expr.0.tn@ = new_op_node (AND, @Term.0.tn@, @Term.1.tn@); */
				@i @Expr.0.tn@ = @AndTerm.tn@;
                        @}
                | DotTerm
                        @{
                                /* @i @Expr.0.tn@ = new_op_node (DOT, @Term.0.tn@, @Term.1.tn@); */
				@i @Expr.0.tn@ = @DotTerm.tn@;
                        @}
                | Term '<' Term
                        @{
                                @i @Expr.0.tn@ = new_op_node (LESS, @Term.0.tn@, @Term.1.tn@);
                        @}
                | Term '=' Term
                        @{
                                @i @Expr.0.tn@ = new_op_node (EQ, @Term.0.tn@, @Term.1.tn@);
                        @}
                | Expr Term
                        @{
                                /* simply pass on what we already have */
                                @i @Expr.1.variable@ = @Expr.0.variable@;
                                @i @Expr.0.tn@ = new_op_node (FCALL, @Expr.1.tn@, @Term.tn@); 
                        @}
                ;

LetExpr         : t_let ident '=' Expr t_in Expr t_end
                        @{
                                /* simply pass on what we already have */
                                @i @Expr.variable@ = @LetExpr.variable@;

                                /* @Expr.2.variable@ gets everything from before (@Expr.0.variable@) and a new element */
                                @i @LetExpr.let@ = insert_elem (VARIABLE, list_create (), @ident.name@, 3);
                                @i @Expr.1.variable@ = insert_elem (VARIABLE, @Expr.variable@, @ident.name@, 4);

                                @i @LetExpr.var@ = new_id_node (@ident.name@, @Expr.1.variable@);
                                @i @LetExpr.tnp@ = new_op_node (LET, @LetExpr.var@, @Expr.0.tn@);
                                @i @LetExpr.tnp1@ = new_op_node (IN, @LetExpr.var@, @Expr.1.tn@);
                                @codegen printf ("LBL%s:\n", @ident.name@);        
                                @i @LetExpr.tn@ = new_op_node (ORPHAN, new_id_node (@ident.name@, @Expr.1.variable@), (struct treenode *)NULL);
                                @codegen
                                {
                                        invoke_burm (@LetExpr.tnp@);                                       
                                }
                                @codegen
                                {
                                        invoke_burm (@LetExpr.tnp1@);
                                }
                        @}
                ;


Ops             : t_not Ops
                        @{
                                @i @Ops.tn@ = new_op_node (NOT, @Ops.1.tn@, (struct treenode *)NULL);
                        @}
                | t_head Ops
                        @{
                                @i @Ops.tn@ = new_op_node (HEAD, @Ops.1.tn@, (struct treenode *)NULL);
                        @}
                | t_tail Ops 
                        @{
                                @i @Ops.tn@ = new_op_node (TAIL, @Ops.1.tn@, (struct treenode *)NULL);
                        @}
                | t_isnum Ops
                        @{
                                @i @Ops.tn@ = new_op_node (ISNUM, @Ops.1.tn@, (struct treenode *)NULL);
                        @}
                | t_islist Ops
                        @{
                                @i @Ops.tn@ = new_op_node (ISLIST, @Ops.1.tn@, (struct treenode *)NULL);
                        @}
                | t_isfun Ops
                        @{
                                @i @Ops.tn@ = new_op_node (ISFUN, @Ops.1.tn@, (struct treenode *)NULL);
                        @}

                | Term
                        @{
                        @}
                ;
DotTerm         :
	        Term '.' Term	
                @{
                                /* @i @DotTerm.0.tn@ = new_op_node (DOT, (struct treenode *)NULL, (struct treenode *)NULL); */
				@i @DotTerm.0.tn@ = new_op_node (DOT, @Term.0.tn@, @Term.1.tn@);
                @}
                | Term '.' DotTerm
                @{
                                @i @DotTerm.0.tn@ = new_op_node (DOT, @Term.tn@, @DotTerm.1.tn@);
                @}
                ;
AndTerm         :
	        Term t_and Term	
                @{
                               /* @i @AndTerm.0.tn@ = new_op_node (AND, (struct treenode *)NULL, (struct treenode *)NULL); */
				@i @AndTerm.0.tn@ = new_op_node (AND, @Term.0.tn@, @Term.1.tn@);
                @}

                | AndTerm t_and Term
                @{
                                @i @AndTerm.0.tn@ = new_op_node (AND, @AndTerm.1.tn@, @Term.tn@);
                @}
                ;
PlusTerm        : 
		Term '+' Term
                @{
                                /* @i @PlusTerm.0.tn@ = new_op_node (ADD, (struct treenode *)NULL, (struct treenode *)NULL); */
				@i @PlusTerm.0.tn@ = new_op_node (ADD, @Term.0.tn@, @Term.1.tn@);	
                @}

                | PlusTerm '+' Term
                @{
                                @i @PlusTerm.0.tn@ = new_op_node (ADD, @PlusTerm.1.tn@, @Term.tn@);
                @}
                ;
MulTerm         : 
		Term '*' Term
                @{
                                 /* @i @MulTerm.0.tn@ = new_op_node (MUL, (struct treenode *)NULL, (struct treenode *)NULL); */
				@i @MulTerm.0.tn@ = new_op_node (MUL, @Term.0.tn@, @Term.1.tn@);
                @}

                | MulTerm '*' Term
                @{
                                @i @MulTerm.0.tn@ = new_op_node (MUL, @MulTerm.1.tn@, @Term.tn@);
                @}
                ;
Term            : '(' Expr ')'
                @{
                @}
                | num
                @{
                                @i @Term.tn@ = new_num_node (@num.val@);
                @}
                | ident
                        @{
                                @err isPresent (@Term.variable@, @ident.name@);
                                @i @Term.tn@ = new_id_node (@ident.name@, reg_init(@Term.variable@));
                        @}
                ;
%%
