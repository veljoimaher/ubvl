char rcsid_pattern[] = "$Id: pattern.c,v 4.2 1992/01/07 17:32:57 todd Exp $";

#include <stdio.h>
#include "b.h"

Pattern
newPattern(op) Operator op;
{
	Pattern p;

	p = (Pattern) zalloc(sizeof(struct pattern));
	p->op = op;
	return p;
}

void
dumpPattern(p) Pattern p;
{
	int i;

	if (!p) {
		printf("[no-pattern]");
		return;
	}

	if (p->op) {
		printf("%s", p->op->name);
		if (p->op->arity > 0) {
			printf("(");
			for (i = 0; i < p->op->arity; i++) {
				printf("%s ", p->children[i]->name);
			}
			printf(")");
		}
	} else {
		printf("%s", p->children[0]->name);
	}
}
