#ifndef __REG_H__
#define __REG_H__

#include "node.h"
#include "tree.h"

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
	int signal;
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
int reg_is_param (char *reg);
void freereg(char * reg);
void freeallreg ();
void reg_dump ();
char *get_label ();
int get_label_nr ();
struct treenode *reg_assign (struct treenode *tn, char *reg);
void reg_set_signal (char *reg);
int reg_get_signal (char *reg);
int next_label_nr ();

#endif

