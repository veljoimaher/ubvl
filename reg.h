#ifndef __REG_H__
#define __REG_H__

#include "node.h"

#define NR_REGS 9

#define PARAM 0
#define TEMP  1

struct reg
{
        char *name;
        int used;
        int type;
};

void reg_init (struct list *l);
char * newreg();
void freereg(char * reg);
void freeallreg ();

#endif

