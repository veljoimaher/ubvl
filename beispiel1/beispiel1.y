%{
#include <stdlib.h>
#include <assert.h>
#include "beispiel1.h"
%}
     
%token ASSIGNOP PLUSASSIGNOP
%left PLUSOP
%token REGISTER NUMBER ';'

@attributes { char* name; } REGISTER
@attributes { long val; } NUMBER
@attributes { treenode *n; } stmt expr constexpr

@traversal @preorder codegen

%{
treenode *newOperatorNode(int op, treenode *left, treenode *right);
treenode *newRegisterNode(char* name);
treenode *newNumberNode(long num);
extern void invoke_burm(NODEPTR_TYPE root);
%}

%start	stmt_list

%%
	     
stmt_list: 	/* empty */
	|	stmt ';' stmt_list
		@{
			@codegen invoke_burm(@stmt.n@);
		@}
	;

stmt	:	
		REGISTER ASSIGNOP expr
		@{ @i @stmt.n@ = newOperatorNode(ASSIGN,newRegisterNode(@REGISTER.name@),@expr.n@); @}
	|	REGISTER PLUSASSIGNOP expr
		@{ @i @stmt.n@ = newOperatorNode(ADDASSIGN,newRegisterNode(@REGISTER.name@),@expr.n@); @}
	;

expr	:	REGISTER
		@{ @i @expr.n@ = newRegisterNode(@REGISTER.name@); @}
	|	constexpr
		@{ @i @expr.n@ = @constexpr.n@; @}
	;

constexpr:	NUMBER
		@{ @i @constexpr.n@ = newNumberNode(@NUMBER.val@); @}
	|	constexpr PLUSOP constexpr
		@{ @i @constexpr.n@ = newOperatorNode(ADD,@constexpr.1.n@,@constexpr.2.n@); @}
	;
	
%%

treenode *newOperatorNode(int op, treenode *left, treenode *right)
{
  treenode *newNode = malloc(sizeof(treenode));

  if (newNode == NULL) { printf("Out of memory.\n"); exit(4);}

  newNode->op = op;
  newNode->kids[0] = left;
  newNode->kids[1] = right;
  newNode->regname=0;
  newNode->val=0;

  return newNode;
}

treenode *newRegisterNode(char* regname)
{
  treenode *newNode = newOperatorNode(REG,NULL,NULL);
  newNode->regname = regname;
  return newNode;
}

treenode *newNumberNode(long num)
{
  treenode *newNode = newOperatorNode(NUM,NULL,NULL);
  newNode->val = num;
  return newNode;
}

int yyerror(char *e)
{
	printf("Parser error: '%s'...\n", e);
	exit(2);
}

int main(void)
{
	yyparse();
	return 0;
}
