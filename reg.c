#include <stdio.h>
#include <string.h>
#include "reg.h"

char *arg_regs[] = { "rdi", "rsi", "rdx", "rcx", "r8", "r9" };
char *temp_regs[] = { "r11", "rbx", "rax" };

int args_regs_used[6] = {0, 0, 0, 0, 0, 0};
int temp_regs_used[3] = {0, 0, 0};
int local_labels = 1;

/* struct reg all_regs [9]; */
struct reg all_regs[NR_REGS] =
{
	{"rdi", 0, 0, PARAM},
	{"rsi", 0, 0, TEMP},
	{"rdx", 0, 0, TEMP},
	{"rcx", 0, 0, TEMP},
	{"r8", 0, 0, TEMP},
	{"r9", 0, 0, TEMP},
	{"r11", 0, 0, TEMP},
	{"rbx", 0, 0, TEMP},
	{"rax", 0, 0, TEMP}
};

struct reg_map all_map[] = 
{
	/* r8 - r15 does not have 8bit high register */
	/* r64,   r32,  r16,  r8h,  r8l */
	{ "rax", "eax", "ax", "ah", "al" },
	{ "rbx", "ebx", "bx", "bh", "bl" },
	{ "rcx", "ecx", "cx", "ch", "cl" },
	{ "rdx", "edx", "dx", "dh", "dl" },
	{ "rsi", "esi", "si", "sih", "sil" },
	{ "rdi", "edi", "di", "dih", "dil" },
	{ "r8", "r8d", "r8w", "r8b", "r8b" },
	{ "r9", "r9d", "r9w", "r9b", "r9b" },
	{ "r10","r10d","r10w","r10b","r10b" },
	{ "r11", "r11d","r11w","r11b","r11b" },
	{ "r12", "r12d","r12w","r12b","r12b" },
	{ "r13", "r13d","r13w","r13b","r13b" },
	{ "r14", "r14d","r14w","r14b","r14b" },
	{ "r15", "r15d","r15w","r15b","r15b" }
};

/* labels definition */
struct label_map label[] =
{
        {"_IF_0", 0},
        {"_IF_1", 0},
        {"_IF_2", 0},
        {"_IF_3", 0},
        {"_IF_4", 0},
        {"_IF_5", 0},
};

struct list * reg_init (struct list *l)
{
	int nr_params = 0;
	struct list *lp = l;
	struct node *n = list_head (lp);

	while ( (n = list_next (n)) != list_end (lp))
	{
		if (n->type == PARAMETER || n->type == VARIABLE)
		{
			all_regs[nr_params].type = PARAM;
			all_regs[nr_params].used = 1;
			n->reg = strdup (all_regs[nr_params].name);
			nr_params++;
		}
	}
	return l;
}

int reg_is_param (char *reg)
{
	int i;
	int reg_size =  sizeof (all_regs)/ sizeof (struct reg);
	if (!reg)
		return 0;

	for (i=0; i<reg_size; i++)
	{
		if (strcmp (reg, all_regs[i].name) == 0)
		{
			if (all_regs[i].type == PARAM)
				return 1;
			else 
				return 0;
		}
	}
	return 0;
}

void reg_set_signal (char *reg)
{
	int i;
	int reg_size = sizeof (all_regs)/sizeof (struct reg);
	if (!reg)
		return;
	for (i=0; i<reg_size; i++)
	{
		if (strcmp (reg, all_regs[i].name) == 0)
		{
			all_regs[i].signal = 1;
		}
	}
}

int reg_get_signal (char *reg)
{
	int i; 
	int reg_size = sizeof (all_regs)/sizeof (struct reg);
	if (!reg)
		return -1;

	for (i=0; i<reg_size; i++)
	{
		if (strcmp (reg, all_regs[i].name) == 0)
		{
			return all_regs[i].signal;
		}
	}
	return -1;
}

int get_label_nr ()
{
	return local_labels++;
}

int next_label_nr ()
{
	return local_labels;
}

int cur_label_nr ()
{
	return local_labels-1;
}

char *get_label ()
{
        int i;

        for (i=0; i<NR_LABELS; i++)
        {
                if (label[i].used == 0)
                {
                        label[i].used = 1;
                        return label[i].name;
                }
        }
        printf ("no new labels\n");
        return "label unavailable";
}


struct treenode *reg_assign (struct treenode *tn, char *reg)
{
        tn->reg = reg;
        return tn;
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

char * get_reg_name (char *r, int type)
{
	int i;
	int map_size;
	struct reg_map *found = NULL;
	char *ret;

	map_size = sizeof (all_map)/ sizeof (struct reg_map);

	for (i=0; i<map_size; i++)
	{
		if (strcmp (r, all_map[i].r64) == 0)
			found = &all_map[i];
		if (strcmp (r, all_map[i].r32) == 0)
			found = &all_map[i];
		if (strcmp (r, all_map[i].r16) == 0)
			found = &all_map[i];
		if (strcmp (r, all_map[i].r8h) == 0)
			found = &all_map[i];
		if (strcmp (r, all_map[i].r8l) == 0)
			found = &all_map[i];
	}

	if (found == NULL)
		return "not found";

	switch (type)
	{
		case R64:
			ret = found->r64;
			break;
		case R32:
			ret = found->r32;
			break;
		case R16:
			ret = found->r16;
			break;
		case R8H:
			ret = found->r8h;
			break;
		case R8L:
			ret = found->r8l;
			break;
		default:
			ret = "not found";
			break;
	}

	return ret;
}

void freereg(char * reg)
{
	int i;
	for (i = 0; i<NR_REGS; i++)
	{
		if (strcmp (reg, all_regs[i].name) == 0)
			all_regs[i].used = 0;
			all_regs[i].signal = 0;
	}
}

void freeallreg ()
{
	int i;
	all_regs[0].used = 1;
	all_regs[0].type = PARAM;
	all_regs[0].signal = 0;

	for (i=1; i<NR_REGS; i++)
	{
		all_regs[i].type = TEMP;
		all_regs[i].used = 0;
		all_regs[i].signal = 0;
	}
}

void reg_dump ()
{
	int i;
	for (i=0; i<NR_REGS; i++)
	{
		printf ("name: '%s', used: %d, type: '%s', signal: '%d'\n", all_regs[i].name, all_regs[i].used, all_regs[i].type?"TEMP":"PARAM", all_regs[i].signal);
	}
}
