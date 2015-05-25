# extend the ag to compile code in AMD64 Assembler code

All programs which have no:
* if
* let
* function calls
* lambda comming from Expr

should work.

Meaning these productions are valid:

Program: { Def ’;’ } 
       ;  
 
Def: ident = Lambda 
   ; 
 
Lambda: fun ident ’->’ Expr end 
      ;  
 
Expr: Term 
    | { not | head | tail | isnum | islist | isfun } Term  
    | Term
    | Term { ’+’ Term }  
    | Term ’-’ Term  
    | Term { ’*’ Term }  
    | Term { and Term }  
    | Term { ’.’ Term }  
    | Term ( ’<’ | ’=’ ) Term  
    ;  
 
Term: ’(’ Expr ’)’ 
    | num  
    | ident                   /* Variablenverwendung */  