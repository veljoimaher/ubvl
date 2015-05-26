#include <stdio.h>
#include <string.h>
#include "reg.h"

char *arg_regs[] = { "rdi", "rsi", "rdx", "rcx", "r8", "r9" };
char *temp_regs[] = { "r11", "rbx", "rax" };

int args_regs_used[6] = {0, 0, 0, 0, 0, 0};
int temp_regs_used[3] = {0, 0, 0};

char * newreg()
{
	int i;
	for (i = 0; i<3; i++)
	{
		if (temp_regs_used[i] == 0)
		{
			temp_regs_used[i] = 1;
			return temp_regs[i];
		}
	}
	printf ("no new regs\n");
	return "unavail";
}

void freereg(char * reg)
{
	int i;
	for (i = 0; i<3; i++)
	{
		if (strcmp (reg, temp_regs[i]) == 0)
			temp_regs_used[i] = 0;
	}
}

