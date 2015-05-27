#include <stdio.h>
#include <string.h>
#include "reg.h"

char *arg_regs[] = { "rdi", "rsi", "rdx", "rcx", "r8", "r9" };
char *temp_regs[] = { "r11", "rbx", "rax" };

int args_regs_used[6] = {0, 0, 0, 0, 0, 0};
int temp_regs_used[3] = {0, 0, 0};

/* struct reg all_regs [9]; */
struct reg all_regs[NR_REGS] =
{
	{"rdi", 0, PARAM},
	{"rsi", 0, TEMP},
	{"rdx", 0, TEMP},
	{"rcx", 0, TEMP},
	{"r8", 0, TEMP},
	{"r9", 0, TEMP},
	{"r11", 0, TEMP},
	{"rbx", 0, TEMP},
	{"rax", 0, TEMP}
};

void reg_init (struct list *l)
{
	int i;
	int nr_params = 0;
	struct node *n = list_head (l);
	while ( (n = list_next (n)) != list_end (l))
	{
		if (n->type == PARAMETER)
		{
			all_regs[nr_params].type = PARAM;
			all_regs[nr_params].used = 1;
			n->reg = strdup (all_regs[nr_params].name);
			nr_params++;
		}
	}
}

char * newreg()
{
	int i;
	for (i = 0; i<NR_REGS; i++)
	{
		if ( all_regs[i].used == 0 )
		{
			all_regs[i].used = 1;
			return all_regs[i].name;
		}

	}
	printf ("no new regs\n");
	return "unavail";
}

void freereg(char * reg)
{
	int i;
	for (i = 0; i<NR_REGS; i++)
	{
		if (strcmp (reg, all_regs[i].name) == 0)
			all_regs[i].used = 0;
	}
}

void freeallreg ()
{
	int i;
	all_regs[0].used = 0;
	all_regs[0].type = PARAM;

	for (i=1; i<NR_REGS; i++)
	{
		all_regs[i].type = TEMP;
		all_regs[i].used = 0;
	}
}

void reg_dump ()
{
	int i;
	for (i=0; i<NR_REGS; i++)
	{
		printf ("name: '%s', used: %d, type: '%s'\n", all_regs[i].name, all_regs[i].used, all_regs[i].type?"TEMP":"PARAM");
	}
}
