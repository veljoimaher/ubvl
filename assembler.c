#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "tree.h"
#include "reg.h"

int lbl = 0;
void func_header (char *fname)
{
        printf ("\t.text\n");
        printf ("\t.global %s\n", fname);
        printf ("\t.type %s, @function\n", fname);
        printf ("%s:\n", fname);
}

void assembler_emit_signal (struct treenode *tn)
{
	if (reg_is_param (tn->left->reg) && reg_get_signal (tn->left->reg) == 0)
	{
		reg_set_signal (tn->left->reg);
		printf ("\tbt $0, %%%s\n", tn->left->reg);
		printf ("\tjc raisesig\n");
	}

	if (reg_is_param (tn->right->reg) && reg_get_signal (tn->right->reg) == 0)
	{
		reg_set_signal (tn->right->reg);
                printf ("\tbt $0, %%%s\n", tn->right->reg);
	        printf ("\tjc raisesig\n");
	}
}

char *assembler_asgn (struct treenode *tn)
{
        char *r; 

        r = tn->left->reg;
	if (reg_used ("rbx"))
		printf ("\tpop %%rbx\n");
        printf("\tmov %%%s, %%rax\n", tn->right->reg);
        printf("\tret\n\n");

	freeallreg ();
        return r;
}
char *assembler_lasgn_reg_expr (struct treenode *tn)
{
        if (tn->right->op == NUM)
                printf ("\tsal $1, %%%s\n", tn->right->reg);

        return tn->right->reg;
}
char *assembler_lasgn_reg_reg (struct treenode *tn)
{
        char *r = tn->left->reg;

        r = tn->left->reg;
        printf("\tmov %%%s, %%%s\n", tn->right->reg, tn->left->reg);

        return r;
}

char *assembler_add_id_id (struct treenode *tn)
{
        char *l = newreg();
        char *r = newreg();
/*
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
        printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");
*/
	assembler_emit_signal (tn);
        printf ("\tmov %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmov %%%s, %%%s\n", tn->right->reg, r);
	
        printf ("\tsar $1, %%%s\n", l);
        printf ("\tsar $1, %%%s\n", r);
        printf ("\taddq %%%s, %%%s\n", l, r);

        printf ("\tsal $1, %%%s\n", r);
	freereg (l);
	return r;

}
char *assembler_add_id_num (struct treenode *tn)
{
        char *l = newreg ();
/*
	printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
*/
	assembler_emit_signal (tn);	
        printf ("\tmov %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tsar $1, %%%s\n", l);
        printf ("\taddq %%%s, %%%s\n", l, tn->right->reg);

        printf ("\tsal $1, %%%s\n", tn->right->reg);
	freereg (l);
        return tn->right->reg;

}
char *assembler_add_num_id (struct treenode *tn)
{
        char *r = newreg ();
/* 
        printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");
*/
	assembler_emit_signal (tn);
        printf ("\tmov %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tsar $1, %%%s\n", r);
        printf ("\taddq %%%s, %%%s\n", r, tn->left->reg);
        printf ("\tsal $1, %%%s\n", tn->left->reg);
	freereg (r);
        return tn->left->reg;

}
char *assembler_add_num_num (struct treenode *tn)
{
        printf ("\taddq %%%s, %%%s\n", tn->left->reg, tn->right->reg);
        printf ("\tsal $1, %%%s\n", tn->right->reg);
	freereg (tn->left->reg);
        return tn->right->reg;

}
char *assembler_add (struct treenode *tn)
{
        char *l = newreg();
        char *r = newreg();
/*
        if (tn->left->op == NUM)
        {
                printf ("\tbt $0, %%%s\n", tn->left->reg);
                printf ("\tjc raisesig\n");
        }
        if (tn->right->op == NUM)
        {
                printf ("\tbt $0, %%%s\n", tn->right->reg);
                printf ("\tjc raisesig\n");
        }
*/
	assembler_emit_signal (tn);
        printf ("\tmov %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmov %%%s, %%%s\n", tn->right->reg, r);

        printf ("\tsar $1, %%%s\n", l);
        printf ("\tsar $1, %%%s\n", r);
        printf ("\taddq %%%s, %%%s\n", l, r);

        printf ("\tsal $1, %%%s\n", r);
	freereg (l);
	freereg (tn->left->reg);
	freereg (tn->right->reg);
        return r;

}

char *assembler_sub_id_id (struct treenode *tn)
{
        char *l = newreg ();
        char *r = newreg ();
/*
	if (tn->left->op == NUM)
        {
                printf ("\tbt $0, %%%s\n", tn->left->reg);
                printf ("\tjc raisesig\n");
        }
        if (tn->right->op == NUM)
        {
                printf ("\tbt $0, %%%s\n", tn->right->reg);
                printf ("\tjc raisesig\n");
        }
*/        
	assembler_emit_signal (tn);
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tsar $1, %%%s\n", l);
        printf ("\tsar $1, %%%s\n", r);
        printf ("\tsubq %%%s, %%%s\n", r, l);
        
        printf ("\tsal $1, %%%s\n", l);
	freereg (tn->left->reg);
	freereg (tn->right->reg);
	freereg (r);
        return l;
}
char *assembler_sub_id_num (struct treenode *tn)
{
        char *reg = newreg ();
/*
	printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
*/
	assembler_emit_signal (tn);
	printf ("\tmovq %%%s, %%%s\n", tn->left->reg, reg);
        printf ("\tsar $1, %%%s\n", reg);
        printf ("\tsubq %%%s, %%%s\n", tn->right->reg, reg);
        
        printf ("\tsal $1, %%%s\n", reg);
	freereg (tn->right->reg);
        return reg;
}
char *assembler_sub_num_id (struct treenode *tn)
{
        char *r = newreg ();
/*
	printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");
*/ 
	assembler_emit_signal (tn);
        printf ("\tmov %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tsar $1, %%%s\n", r);
        printf ("\tsubq %%%s, %%%s\n", r, tn->left->reg); 
        
        printf ("\tsal $1, %%%s\n", tn->left->reg);
        return tn->left->reg;

}
char *assembler_sub_num_num (struct treenode *tn)
{
        printf ("NOT USED\n");
        return newreg ();

}
char *assembler_sub (struct treenode *tn)
{
        char *l = newreg ();
        char *r = newreg ();
/*
	if (tn->left->op == NUM)
        {
                printf ("\tbt $0, %%%s\n", tn->left->reg);
                printf ("\tjc raisesig\n");
        }
        if (tn->right->op == NUM)
        {
                printf ("\tbt $0, %%%s\n", tn->right->reg);
                printf ("\tjc raisesig\n");
        }
*/
	assembler_emit_signal (tn);
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
	if (tn->left->op != NUM)
        	printf ("\tsar $1, %%%s\n", l);

	if (tn->right->op != NUM)
	        printf ("\tsar $1, %%%s\n", r);

        printf ("\tsubq %%%s, %%%s\n", r, l);
        
        printf ("\tsal $1, %%%s\n", l);
	freereg (r);
	freereg (tn->left->reg);
	freereg (tn->right->reg);
        return l;

}

char *assembler_mul_id_id (struct treenode *tn)
{
        char *l = newreg ();
        char *r = newreg ();
/*
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
        printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");
*/
	assembler_emit_signal (tn);
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tsar $1, %%%s\n", l);
        printf ("\tsar $1, %%%s\n", r);
 
        printf ("\timul %%%s, %%%s\n", r, l);
        printf ("\tsal $1, %%%s\n", l);
        freereg (r);	
        return l;
}
char *assembler_mul_id_num (struct treenode *tn)
{
        char *l = newreg ();
/*
	printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
*/
	assembler_emit_signal (tn);
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tsar $1, %%%s\n", l);
 
        printf ("\timul %%%s, %%%s\n", tn->right->reg, l);
        printf ("\tsal $1, %%%s\n", l);
	freereg (tn->right->reg);
        return l;
}
char *assembler_mul_num_id (struct treenode *tn)
{
        char *r = newreg ();
/*
        printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");
*/
	assembler_emit_signal (tn);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tsar $1, %%%s\n", r);

        printf ("\timul %%%s, %%%s\n", tn->left->reg, r);
        printf ("\tsal $1, %%%s\n", r);
        freereg (tn->left->reg);	
        return r;
}
char *assembler_mul (struct treenode *tn)
{
        char *l = newreg ();
        char *r = newreg ();

/*	
        if (tn->left->op == NUM)
        {
                printf ("\tbt $0, %%%s\n", tn->left->reg);
                printf ("\tjc raisesig\n");
        }
        if (tn->right->op == NUM)
        {
                printf ("\tbt $0, %%%s\n", tn->right->reg);
                printf ("\tjc raisesig\n");
        }
*/
	assembler_emit_signal (tn);
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tsar $1, %%%s\n", l);
        printf ("\tsar $1, %%%s\n", r);
 
        printf ("\timul %%%s, %%%s\n", r, l);
        printf ("\tsal $1, %%%s\n", l);
	freereg (tn->left->reg);
	freereg (tn->right->reg);
	freereg (r);        
        return l;
}
char *assembler_mul_num_num (struct treenode *tn)
{
        printf ("NOT USED\n");
        return newreg();

}
char *assembler_and_id_id (struct treenode *tn)
{
        char *l = newreg ();
        char *r = newreg ();
/*
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
        printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");
*/ 
	assembler_emit_signal (tn);
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tsar $1, %%%s\n", l);
        printf ("\tsar $1, %%%s\n", r);
 
        printf ("\tand %%%s, %%%s\n", r, l);
        printf ("\tsal $1, %%%s\n", l);
	freereg (r);
        return l;

}
char *assembler_and_id_num (struct treenode *tn)
{
        char *l = newreg ();
/*
	printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
*/
	assembler_emit_signal (tn);
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tsar $1, %%%s\n", l);
        printf ("\tand %%%s, %%%s\n", tn->right->reg, l);
        printf ("\tsal $1, %%%s\n", l);
	freereg (tn->right->reg);
        return l;

}
char *assembler_and_num_id (struct treenode *tn)
{
        char *r = newreg ();
/*
	printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");
*/ 
	assembler_emit_signal (tn);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tsar $1, %%%s\n", r);
 
        printf ("\tand %%%s, %%%s\n", r, tn->left->reg);
        printf ("\tsal $1, %%%s\n", tn->left->reg);
	freereg (r);
        return tn->left->reg;


}
char *assembler_and_num_num (struct treenode *tn)
{
        printf ("NOT USED\n");
        return newreg ();


}
char *assembler_and (struct treenode *tn)
{
        char *l = newreg ();
        char *r = newreg ();
/*
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
        printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");
*/ 
	assembler_emit_signal (tn);
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tsar $1, %%%s\n", l);
        printf ("\tsar $1, %%%s\n", r);
 
        printf ("\tand %%%s, %%%s\n", r, l);
        printf ("\tsal $1, %%%s\n", l);
	freereg (tn->left->reg);
	freereg (tn->right->reg);
	freereg (r);
        return l;

}

char *assembler_dot_id_id (struct treenode *tn)
{
	char *reg = newreg ();
        printf ("\tmov %%%s, 0(%%r15)\n", tn->left->reg);
        printf ("\tmov %%%s, 8(%%r15)\n", tn->right->reg);
        printf ("\tmov %%r15, %%%s\n", reg);
        printf ("\tadd $1, %%%s\n", reg);
        printf ("\tadd $16, %%r15\n");

        return reg;
}
char *assembler_dot_id_num (struct treenode *tn)
{
        char *reg = newreg ();
        printf ("\tsal $1, %%%s\n", tn->right->reg);
        printf ("\tmov %%%s, 0(%%r15)\n", tn->left->reg);
        printf ("\tmov %%%s, 8(%%r15)\n", tn->right->reg);
        printf ("\tmov %%r15, %%%s\n", reg);
        printf ("\tadd $1, %%%s\n", reg);
        printf ("\tadd $16, %%r15\n");
	freereg (tn->right->reg);
        return reg;

}
char *assembler_dot_num_id (struct treenode *tn)
{
        char *reg = newreg ();
        printf ("\tsal $1, %%%s\n", tn->left->reg);
        printf ("\tmov %%%s, 0(%%r15)\n", tn->left->reg);
        printf ("\tmov %%%s, 8(%%r15)\n", tn->right->reg);
        printf ("\tmov %%r15, %%%s\n", reg);
        printf ("\tadd $1, %%%s\n", reg);
        printf ("\tadd $16, %%r15\n");
	freereg (tn->left->reg);
        return reg;
}
char *assembler_dot_num_num (struct treenode *tn)
{
        char *reg = newreg ();
        printf ("\tsal $1, %%%s\n", tn->left->reg);
        printf ("\tsal $1, %%%s\n", tn->right->reg);
        printf ("\tmov %%%s, 0(%%r15)\n", tn->left->reg);
        printf ("\tmov %%%s, 8(%%r15)\n", tn->right->reg);
        printf ("\tmov %%r15, %%%s\n", reg);
        printf ("\tadd $1, %%%s\n", reg);
        printf ("\tadd $16, %%r15\n");
	freereg (tn->left->reg);
	freereg (tn->right->reg);
        return reg;
}
char *assembler_dot (struct treenode *tn)
{
        char *reg = newreg ();
        if (tn->left->op == NUM)
                printf ("\tsal $1, %%%s\n", tn->left->reg);
        if (tn->right->op == NUM)
                printf ("\tsal $1, %%%s\n", tn->right->reg);
        printf ("\tmov %%%s, 0(%%r15)\n", tn->left->reg);
        printf ("\tmov %%%s, 8(%%r15)\n", tn->right->reg);
        printf ("\tmov %%r15, %%%s\n", reg);
        printf ("\tadd $1, %%%s\n", reg);
        printf ("\tadd $16, %%r15\n");
	freereg (tn->right->reg);
	freereg (tn->left->reg);
        return reg;

}

char *assembler_less_id_id (struct treenode *tn)
{
        /* char *reg = newreg(); */
        char *l = newreg ();
        char *r = newreg ();
/*  
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
        printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");
*/
	assembler_emit_signal (tn);
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tsar $1, %%%s\n", l);
        printf ("\tsar $1, %%%s\n", r);
        printf ("\tcmp %%%s, %%%s\n", r, l);
        printf ("\tsetl %%%s\n", get_reg_name (l, R8L));
        printf ("\tsal $1, %%%s\n", l);
	freereg (r);
        return l;
 }
char *assembler_less_id_num (struct treenode *tn)
{
        char *reg = newreg();
/*
	printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
*/        
	assembler_emit_signal (tn);
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, reg);
        printf ("\tsar $1, %%%s\n", reg);
        
	/* cmp 
	 * dst > src  -> CF = 0, ZF = 0
	 * dst == src -> CF = 0, ZF = 1
	 * dst < src  -> CF = 1, ZF = 0
	 * x<3 - leftreg = x, right reg = 3
	 */
        printf ("\tcmp %%%s, %%%s\n", tn->right->reg, reg);
        printf ("\tsetl %%%s\n", get_reg_name (reg, R8L));
        printf ("\tsal $1, %%%s\n", reg);
	freereg (tn->right->reg);
        return reg;

}
char *assembler_less_num_id (struct treenode *tn)
{
        char *reg = newreg();
/*
	printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");
*/        
	assembler_emit_signal (tn);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, reg);
        printf ("\tsar $1, %%%s\n", reg);
        
	/* cmp 
	 * dst > src  -> CF = 0, ZF = 0
	 * dst == src -> CF = 0, ZF = 1
	 * dst < src  -> CF = 1, ZF = 0
	 * x<3 - leftreg = x, right reg = 3
	 */
        printf ("\tcmp %%%s, %%%s\n", reg, tn->left->reg);
        printf ("\tsetl %%%s\n", get_reg_name (reg, R8L));
        printf ("\tsal $1, %%%s\n", reg);
	freereg (tn->left->reg);
        return reg;


}
char *assembler_less_num_num (struct treenode *tn)
{
        printf ("NOT USED\n");
        return newreg();

}
char *assembler_less (struct treenode *tn)
{
        char *reg = newreg();
        char *l = newreg ();
        char *r = newreg ();
/*  
        if (tn->left->op == NUM)
        {
                printf ("\tbt $0, %%%s\n", tn->left->reg);
                printf ("\tjc raisesig\n");
        }
        if (tn->right->op == NUM)
        {
                printf ("\tbt $0, %%%s\n", tn->right->reg);
                printf ("\tjc raisesig\n");
        }
*/
	assembler_emit_signal (tn);
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tsar $1, %%%s\n", l);
        printf ("\tsar $1, %%%s\n", r);
        printf ("\txor %%%s, %%%s\n", reg, reg); 
        printf ("\tcmp %%%s, %%%s\n", r, l);
        printf ("\tsetl %%%s\n", get_reg_name (reg, R8L));
        printf ("\tsal $1, %%%s\n", reg);
	freereg (l);
	freereg (r);
	freereg (tn->left->reg);
	freereg (tn->right->reg);
        return reg;
}

char *assembler_eq_id_id (struct treenode *tn)
{
        char *reg = newreg();
        char *l = newreg ();
        char *r = newreg ();
        printf ("\txor %%%s, %%%s\n", reg, reg);
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tsar $1, %%%s\n", l);
        printf ("\tsar $1, %%%s\n", r);
        
        printf ("\tcmp %%%s, %%%s\n", l, r);
        printf ("\tsetz %%%s\n", get_reg_name (reg, R8L));
        printf ("\tsal $1, %%%s\n", reg);
	freereg (l);
	freereg (r);
        return reg;
}
char *assembler_eq_id_num (struct treenode *tn)
{
 
        char *reg = newreg();
        char *l = newreg ();
        printf ("\txor %%%s, %%%s\n", reg, reg);
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tsar $1, %%%s\n", l);
        
        printf ("\tcmp %%%s, %%%s\n", l, tn->right->reg);
        printf ("\tsetz %%%s\n", get_reg_name (reg, R8L));
        printf ("\tsal $1, %%%s\n", reg);
	freereg (tn->right->reg);
	freereg (l);
        return reg;

}
char *assembler_eq_num_id (struct treenode *tn)
{
 
        char *reg = newreg();
        char *r = newreg ();
        printf ("\txor %%%s, %%%s\n", reg, reg);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tsar $1, %%%s\n", r);
        
        printf ("\tcmp %%%s, %%%s\n", r, tn->left->reg);
        printf ("\tsetz %%%s\n", get_reg_name (reg, R8L));
        printf ("\tsal $1, %%%s\n", reg);
	freereg (tn->left->reg);
	freereg (r);
        return reg;
}
char *assembler_eq_num_num (struct treenode *tn)
{
  
        char *reg = newreg ();
        printf ("NOT USED\n");
        return reg;

}
char *assembler_eq (struct treenode *tn)
{
        char *reg = newreg();
        char *l = newreg ();
        char *r = newreg ();
        printf ("\txor %%%s, %%%s\n", reg, reg);
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tsar $1, %%%s\n", l);
        printf ("\tsar $1, %%%s\n", r);
        
        printf ("\tcmp %%%s, %%%s\n", l, r);
        printf ("\tsetz %%%s\n", get_reg_name (reg, R8L));
        printf ("\tsal $1, %%%s\n", reg);
	freereg (l);
	freereg (r);
        return reg;
}

char *assembler_not (struct treenode *tn)
{

	printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
	printf ("\tbtc $1, %%%s\n", tn->left->reg);

        return tn->left->reg;
}
/*
 if WORD LSB == 0, data is 63bit number - to get value of the number use bitwise architmetical right shift

 if WORD LSB == 1 && LSB+1 BIT == 0 -> data is pointer to list field
 - to get tag-less data substract 1 from data (address of the field must be always divisible with 8)
 - head of the listfield is on offset 0 of tag-less pointer. next/rest field is on offset 8.
 - one list field is 16 bytes long
*/
char *assembler_head (struct treenode *tn)
{
        char *reg = newreg ();
	if (reg_is_param (tn->left->reg) && reg_get_signal (tn->left->reg) == 0)
	{
		reg_set_signal (tn->left->reg);
		printf ("\tbt $0, %%%s\n", tn->left->reg);
        	printf ("\tjnc raisesig\n");
	}
        printf ("\tmov %%%s, %%%s\n", tn->left->reg, reg);
        printf ("\tsubq $1, %%%s\n", reg);
	printf ("\tmovq 0(%%%s), %%%s\n", reg, reg);
        return reg;

}

char *assembler_tail (struct treenode *tn)
{
	char *reg = newreg ();
	if (reg_is_param (tn->left->reg) && reg_get_signal (tn->left->reg) == 0)
        {
                reg_set_signal (tn->left->reg);
                printf ("\tbt $0, %%%s\n", tn->left->reg);
                printf ("\tjnc raisesig\n");
        }
        printf ("\tmov %%%s, %%%s\n", tn->left->reg, reg);
        printf ("\tsubq $1, %%%s\n", reg);
	printf ("\tmovq 8(%%%s), %%%s\n", reg, reg);
        return reg;
}

char *assembler_isnum (struct treenode *tn)
{
        char *reg = newreg ();
        printf ("\txor %%%s, %%%s\n", reg, reg);
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc notnum\n");
        printf ("\tmovq $1, %%%s\n", reg);
        
        printf ("\tnotnum:\n");
        printf ("\tsal $1, %%%s\n", reg);
        return reg;

}
char *assembler_islist (struct treenode *tn)
{
        char *reg = newreg ();
	int label = get_label_nr ();
        printf ("\txor %%%s, %%%s\n", reg, reg);
                printf ("\tbt $0, %%%s\n", tn->left->reg);
                printf ("\tjnc .L%i\n", label);

        printf ("\tmovq $2, %%%s\n", reg);
        printf (".L%i:\n", label);
        return reg;

}
char *assembler_isfun (struct treenode *tn)
{
        char *l = newreg ();
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq $0, %%%s\n", l);
        printf ("\tsal $1, %%%s\n", l);
        return l;

}
/*
char *assembler_if (struct treenode *tn)
{
        char *reg = newreg ();
	int sig_label;
	int end_label;
	tn->label = get_label_nr ();

	if (tn->left->op == IDENT)
	{
		if (reg_is_param (tn->left->reg) && reg_get_signal (tn->left->reg) == 0)
		{
			reg_set_signal (tn->left->reg);
			printf ("\tbt $0, %%%s\n", tn->left->reg);
			sig_label = get_label_nr ();
			printf ("\tjc .L%i\n", sig_label);
		}
		printf ("\tcmpq $0, %%%s\n", tn->left->reg);
		end_label = get_label_nr ();
		printf ("\tje .L%i\n", tn->right->left->label);

		if (tn->right->right->left->op == NUM)
		       printf ("\tsal $1, %%%s\n", tn->right->left->reg);
		printf ("\tmovq %%%s, %%%s\n", tn->right->left->reg, reg);
		printf ("\tjmp .L%i\n", end_label);

		printf (".L%i:\n", sig_label);
		printf ("\tbt $1, %%%s\n", tn->left->reg);
		printf ("\tjc raisesig\n");
		printf ("\tmovq %%%s, %%%s\n", tn->left->reg, reg);
		printf ("\tsubq $1, %%%s\n", reg);
		printf ("\tcmpq $0, %%%s\n", reg);
		printf ("\tje .L%i\n", tn->right->left->label);
		if (tn->right->right->left->op == NUM)
		       printf ("\tsal $1, %%%s\n", tn->right->left->reg);
		printf ("\tmovq %%%s, %%%s\n", tn->right->left->reg, reg);
		printf ("\tjmp .L%i\n", end_label);

		printf (".L%i:\n", tn->label);
		if (tn->right->left->left->op == NUM)
		       printf ("\tsal $1, %%%s\n", tn->right->right->reg);
		printf ("\tmovq %%%s, %%%s\n", tn->right->right->reg, reg);

		printf (".L%i:\n", end_label);

	} 
	else 
	{
		assembler_emit_signal (tn);
		printf ("\tcmpq $0, %%%s\n", tn->left->reg);
		end_label = get_label_nr ();
                printf ("\tje .L%i\n", tn->right->left->label);

                if (tn->right->left->left->op == NUM)
                       printf ("\tsal $1, %%%s\n", tn->right->left->reg);

                printf ("\tmovq %%%s, %%%s\n", tn->right->left->reg, reg);
                printf ("\tjmp .L%i\n", end_label);
                printf (".L%i:\n", tn->label);
                if (tn->right->right->left->op == NUM)
                       printf ("\tsal $1, %%%s\n", tn->right->right->reg);
                printf ("\tmovq %%%s, %%%s\n", tn->right->right->reg, reg);

                printf (".L%i:\n", end_label);


	}
        return reg;
}
*/

void assembler_begin_if (struct treenode *ifn, struct treenode *l, struct treenode *r)
{
	printf ("\tjmp .L%i\n", r->label);
	printf (".L%i:\n", ifn->label);
}

char *assembler_if (struct treenode *tn)
{
	char *reg = newreg ();
	printf ("\n");
	printf ("\tcmpq $0, %%%s\n", tn->left->reg);
	printf ("\tje .L%i\n", tn->thenlabel);
	printf ("\tjmp .L%i\n", tn->label);

	printf (".L%i:\n", tn->elseendlabel);
	if (tn->right->left->left->op == NUM)
		printf ("\tsal $1, %%%s\n", tn->right->left->reg);
	printf ("\tmovq %%%s, %%%s\n", tn->right->left->reg, reg);
	printf ("\tjmp .L%i\n", tn->endlabel);

	printf (".L%i:\n", tn->thenendlabel);
	if (tn->right->right->left->op == NUM)
		printf ("\tsal $1, %%%s\n", tn->right->right->reg);
	printf ("\tmovq %%%s, %%%s\n", tn->right->right->reg, reg);

	printf (".L%i:\n", tn->endlabel);
	return reg;
}

char *assembler_then (struct treenode *tn)
{
	/* tn->label = get_label_nr (); */
	printf ("\tjmp .L%i\n", tn->thenendlabel);
	printf (".L%i:\n", tn->label);
	return tn->left->reg;
}

char *assembler_else (struct treenode *tn)
{
	/* tn->label = get_label_nr (); */
	printf ("\tjmp .L%i\n", tn->elseendlabel);
	printf (".L%i:\n", tn->label);
	return tn->left->reg;
}

char *assembler_thenelse (struct treenode *tn)
{
	return "";
}

char *assembler_let (struct treenode *tn)
{
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, tn->right->reg);
        return tn->left->reg;
}

char *assembler_in (struct treenode *tn)
{
        return tn->right->reg;
}

char *assembler_fcall (struct treenode *tn)
{
        printf ("\n");
        printf ("\tmovq %%%s, %%rdi\n", tn->right->reg); 
        printf ("\tjmp %s\n", tn->left->name);
        /*printf ("\tmovq %%rax, %%%s\n", tn->right->reg); 
        */
        return tn->right->reg;

}
