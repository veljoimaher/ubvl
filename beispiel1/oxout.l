/* output from Ox version G1.04 */
%{
#include "beispiel1.h"
#include "oxout.tab.h"
%}

comment		\/\/.*
number          [0-9]+
register        %r([abcd]x|[sb]p|[sd]i|[89]|1[0-5])
whitespace      [\n\t ]


%{


struct yyyT1 { char* name; }; 
typedef struct yyyT1 *yyyP1; 


struct yyyT2 { long val; }; 
typedef struct yyyT2 *yyyP2; 


struct yyyT3 { treenode *n; }; 
typedef struct yyyT3 *yyyP3; 
                                                      /*custom*/  
typedef unsigned char yyyWAT; 
typedef unsigned char yyyRCT; 
typedef unsigned short yyyPNT; 
typedef unsigned char yyyWST; 

#include <limits.h>
#define yyyR UCHAR_MAX  

 /* funny type; as wide as the widest of yyyWAT,yyyWST,yyyRCT  */ 
typedef unsigned short yyyFT;

                                                      /*stock*/  




struct yyyGenNode {void *parent;  
                   struct yyyGenNode **cL; /* child list */ 
                   yyyRCT *refCountList; 
                   yyyPNT prodNum;                      
                   yyyWST whichSym; /* which child of parent? */ 
                  }; 

typedef struct yyyGenNode yyyGNT; 



struct yyyTB {int isEmpty; 
              int typeNum; 
              int nAttrbs; 
              char *snBufPtr; 
              yyyWAT *startP,*stopP; 
             };  




extern struct yyyTB yyyTermBuffer; 
extern yyyWAT yyyLRCIL[]; 
extern void yyyGenLeaf(); 


%}
%%

"+="		{yyyGenLeaf(0,0,yyyLRCIL+0,yyyLRCIL+0);return (PLUSASSIGNOP);}
"="		{yyyGenLeaf(0,0,yyyLRCIL+0,yyyLRCIL+0);return (ASSIGNOP);}
"+"		{yyyGenLeaf(0,0,yyyLRCIL+0,yyyLRCIL+0);return (PLUSOP);}	       
";"		{yyyGenLeaf(0,0,yyyLRCIL+0,yyyLRCIL+0);return (';');}
{register}	{yyyGenLeaf(1,1,yyyLRCIL+0,yyyLRCIL+1); (((yyyP1)(yyyTermBuffer.snBufPtr))->name) = strdup(yytext); return (REGISTER);} 
{number}	{yyyGenLeaf(1,2,yyyLRCIL+1,yyyLRCIL+2); (((yyyP2)(yyyTermBuffer.snBufPtr))->val) = atol(yytext); return (NUMBER);} 
{whitespace}+	;
{comment}	;
.		printf("Lexical error.\n"); exit(1);
