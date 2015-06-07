#ifndef __REG_H__
#define __REG_H__

#include "node.h"

#define NR_REGS 9
#define NR_LABELS 6

#define PARAM 0
#define TEMP  1

#define R64	0
#define R32	1
#define R16	2
#define R8H	3
#define R8L	4

struct reg
{
        char *name;
        int used;
        int type;
};

struct reg_map 
{
	char *r64;
	char *r32;
	char *r16;
	char *r8h;
	char *r8l;
};

struct label_map
{
        char *name;
        char used;
};

struct list * reg_init (struct list *l);
char * newreg();
char * get_reg_name (char *r, int type);
void freereg(char * reg);
void freeallreg ();
void reg_dump ();
char *get_label ();

#endif

