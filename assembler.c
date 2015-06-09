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

char *assembler_asgn (struct treenode *tn)
{
        char *r; 

        r = tn->left->reg;
        printf("\tmov %%%s, %%rax\n", tn->right->reg);
        printf("\tret\n\n");

	freeallreg ();
        return r;
}
char *assembler_lasgn_reg_expr (struct treenode *tn)
{
        if (tn->right->op == NUM)
                printf ("\tshl $1, %%%s\n", tn->right->reg);
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

        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
        printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");
 
        printf ("\tmov %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmov %%%s, %%%s\n", tn->right->reg, r);

        printf ("\tshr $1, %%%s\n", l);
        printf ("\tshr $1, %%%s\n", r);
        printf ("\taddq %%%s, %%%s\n", l, r);

        printf ("\tshl $1, %%%s\n", r);
        return r;

}
char *assembler_add_id_num (struct treenode *tn)
{
        char *l = newreg ();
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
 
        printf ("\tmov %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tshr $1, %%%s\n", l);
        printf ("\taddq %%%s, %%%s\n", l, tn->right->reg);

        printf ("\tshl $1, %%%s\n", tn->right->reg);
        return tn->right->reg;

}
char *assembler_add_num_id (struct treenode *tn)
{
        char *r = newreg ();
 
        printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");

        printf ("\tmov %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tshr $1, %%%s\n", r);
        printf ("\taddq %%%s, %%%s\n", r, tn->left->reg);
        printf ("\tshl $1, %%%s\n", tn->left->reg);
        return tn->left->reg;

}
char *assembler_add_num_num (struct treenode *tn)
{
        printf ("\taddq %%%s, %%%s\n", tn->left->reg, tn->right->reg);
        printf ("\tshl $1, %%%s\n", tn->right->reg);
        return tn->right->reg;

}
char *assembler_add (struct treenode *tn)
{
        char *l = newreg();
        char *r = newreg();

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

        printf ("\tmov %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmov %%%s, %%%s\n", tn->right->reg, r);

        printf ("\tshr $1, %%%s\n", l);
        printf ("\tshr $1, %%%s\n", r);
        printf ("\taddq %%%s, %%%s\n", l, r);

        printf ("\tshl $1, %%%s\n", r);
        return r;

}

char *assembler_sub_id_id (struct treenode *tn)
{
        char *l = newreg ();
        char *r = newreg ();
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
        
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tshr $1, %%%s\n", l);
        printf ("\tshr $1, %%%s\n", r);
        printf ("\tsubq %%%s, %%%s\n", r, l);
        
        printf ("\tshl $1, %%%s\n", l);
        return l;
}
char *assembler_sub_id_num (struct treenode *tn)
{
        char *reg = newreg ();
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, reg);
        printf ("\tshr $1, %%%s\n", reg);
        printf ("\tsubq %%%s, %%%s\n", tn->right->reg, reg);
        
        printf ("\tshl $1, %%%s\n", reg);
        return reg;
}
char *assembler_sub_num_id (struct treenode *tn)
{
        char *r = newreg ();
        printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");
 
        printf ("\tmov %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tshr $1, %%%s\n", r);
        printf ("\tsubq %%%s, %%%s\n", r, tn->left->reg); 
        
        printf ("\tshl $1, %%%s\n", tn->left->reg);
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
        
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tshr $1, %%%s\n", l);
        printf ("\tshr $1, %%%s\n", r);
        printf ("\tsubq %%%s, %%%s\n", r, l);
        
        printf ("\tshl $1, %%%s\n", l);
        return l;

}

char *assembler_mul_id_id (struct treenode *tn)
{
        char *l = newreg ();
        char *r = newreg ();

        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
        printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");

        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tshr $1, %%%s\n", l);
        printf ("\tshr $1, %%%s\n", r);
 
        printf ("\timul %%%s, %%%s\n", r, l);
        printf ("\tshl $1, %%%s\n", l);
        
        return l;
}
char *assembler_mul_id_num (struct treenode *tn)
{
        char *l = newreg ();
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");

        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tshr $1, %%%s\n", l);
 
        printf ("\timul %%%s, %%%s\n", tn->right->reg, l);
        printf ("\tshl $1, %%%s\n", l);
        
        return l;
}
char *assembler_mul_num_id (struct treenode *tn)
{
        char *r = newreg ();

        printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");

        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tshr $1, %%%s\n", r);

        printf ("\timul %%%s, %%%s\n", tn->left->reg, r);
        printf ("\tshl $1, %%%s\n", r);
        
        return r;
}
char *assembler_mul (struct treenode *tn)
{
        char *l = newreg ();
        char *r = newreg ();

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

        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tshr $1, %%%s\n", l);
        printf ("\tshr $1, %%%s\n", r);
 
        printf ("\timul %%%s, %%%s\n", r, l);
        printf ("\tshl $1, %%%s\n", l);
        
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

        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
        printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");
 
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tshr $1, %%%s\n", l);
        printf ("\tshr $1, %%%s\n", r);
 
        printf ("\tand %%%s, %%%s\n", r, l);
        printf ("\tshl $1, %%%s\n", l);
        return l;

}
char *assembler_and_id_num (struct treenode *tn)
{
        char *l = newreg ();
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
        
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tshr $1, %%%s\n", l);
        printf ("\tand %%%s, %%%s\n", tn->right->reg, l);
        printf ("\tshl $1, %%%s\n", l);
        return l;

}
char *assembler_and_num_id (struct treenode *tn)
{
        char *r = newreg ();
        printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");
 
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tshr $1, %%%s\n", r);
 
        printf ("\tand %%%s, %%%s\n", r, tn->left->reg);
        printf ("\tshl $1, %%%s\n", tn->left->reg);
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

        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
        printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");
 
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tshr $1, %%%s\n", l);
        printf ("\tshr $1, %%%s\n", r);
 
        printf ("\tand %%%s, %%%s\n", r, l);
        printf ("\tshl $1, %%%s\n", l);
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
        printf ("\tshl $1, %%%s\n", tn->right->reg);
        printf ("\tmov %%%s, 0(%%r15)\n", tn->left->reg);
        printf ("\tmov %%%s, 8(%%r15)\n", tn->right->reg);
        printf ("\tmov %%r15, %%%s\n", reg);
        printf ("\tadd $1, %%%s\n", reg);
        printf ("\tadd $16, %%r15\n");

        return reg;

}
char *assembler_dot_num_id (struct treenode *tn)
{
        char *reg = newreg ();
        printf ("\tshl $1, %%%s\n", tn->left->reg);
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
        printf ("\tshl $1, %%%s\n", tn->left->reg);
        printf ("\tshl $1, %%%s\n", tn->right->reg);
        printf ("\tmov %%%s, 0(%%r15)\n", tn->left->reg);
        printf ("\tmov %%%s, 8(%%r15)\n", tn->right->reg);
        printf ("\tmov %%r15, %%%s\n", reg);
        printf ("\tadd $1, %%%s\n", reg);
        printf ("\tadd $16, %%r15\n");
	freereg (tn->left->reg);
        return reg;
}
char *assembler_dot (struct treenode *tn)
{
        char *reg = newreg ();
        if (tn->left->op == NUM)
                printf ("\tshl $1, %%%s\n", tn->left->reg);
        if (tn->right->op == NUM)
                printf ("\tshl $1, %%%s\n", tn->right->reg);
        printf ("\tmov %%%s, 0(%%r15)\n", tn->left->reg);
        printf ("\tmov %%%s, 8(%%r15)\n", tn->right->reg);
        printf ("\tmov %%r15, %%%s\n", reg);
        printf ("\tadd $1, %%%s\n", reg);
        printf ("\tadd $16, %%r15\n");
        return reg;

}

char *assembler_less_id_id (struct treenode *tn)
{
        /* char *reg = newreg(); */
        char *l = newreg ();
        char *r = newreg ();
  
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
        printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");

        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tshr $1, %%%s\n", l);
        printf ("\tshr $1, %%%s\n", r);
        
        printf ("\tcmp %%%s, %%%s\n", l, r);
        printf ("\tsetl %%%s\n", get_reg_name (l, R8L));
        printf ("\tshl $1, %%%s\n", l);
        return l;
 }
char *assembler_less_id_num (struct treenode *tn)
{
        char *reg = newreg();
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
        
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, reg);
        printf ("\tshr $1, %%%s\n", reg);
        
	/* cmp 
	 * dst > src  -> CF = 0, ZF = 0
	 * dst == src -> CF = 0, ZF = 1
	 * dst < src  -> CF = 1, ZF = 0
	 * x<3 - leftreg = x, right reg = 3
	 */
        printf ("\tcmp %%%s, %%%s\n", tn->right->reg, reg);
        printf ("\tsetl %%%s\n", get_reg_name (reg, R8L));
        printf ("\tshl $1, %%%s\n", reg);
        return reg;

}
char *assembler_less_num_id (struct treenode *tn)
{
        char *reg = newreg();
        printf ("\tbt $0, %%%s\n", tn->right->reg);
        printf ("\tjc raisesig\n");
        
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, reg);
        printf ("\tshr $1, %%%s\n", reg);
        
	/* cmp 
	 * dst > src  -> CF = 0, ZF = 0
	 * dst == src -> CF = 0, ZF = 1
	 * dst < src  -> CF = 1, ZF = 0
	 * x<3 - leftreg = x, right reg = 3
	 */
        printf ("\tcmp %%%s, %%%s\n", reg, tn->left->reg);
        printf ("\tsetl %%%s\n", get_reg_name (reg, R8L));
        printf ("\tshl $1, %%%s\n", reg);
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

        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tshr $1, %%%s\n", l);
        printf ("\tshr $1, %%%s\n", r);
        
        printf ("\tcmp %%%s, %%%s\n", l, r);
        printf ("\tsetl %%%s\n", get_reg_name (reg, R8L));
        printf ("\tshl $1, %%%s\n", reg);
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
        printf ("\tshr $1, %%%s\n", l);
        printf ("\tshr $1, %%%s\n", r);
        
        printf ("\tcmp %%%s, %%%s\n", l, r);
        printf ("\tsetz %%%s\n", get_reg_name (reg, R8L));
        printf ("\tshl $1, %%%s\n", reg);
        return reg;
}
char *assembler_eq_id_num (struct treenode *tn)
{
 
        char *reg = newreg();
        char *l = newreg ();
        printf ("\txor %%%s, %%%s\n", reg, reg);
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tshr $1, %%%s\n", l);
        
        printf ("\tcmp %%%s, %%%s\n", l, tn->right->reg);
        printf ("\tsetz %%%s\n", get_reg_name (reg, R8L));
        printf ("\tshl $1, %%%s\n", reg);
        return reg;

}
char *assembler_eq_num_id (struct treenode *tn)
{
 
        char *reg = newreg();
        char *r = newreg ();
        printf ("\txor %%%s, %%%s\n", reg, reg);
        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, r);
        printf ("\tshr $1, %%%s\n", r);
        
        printf ("\tcmp %%%s, %%%s\n", r, tn->left->reg);
        printf ("\tsetz %%%s\n", get_reg_name (reg, R8L));
        printf ("\tshl $1, %%%s\n", reg);
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
        printf ("\tshr $1, %%%s\n", l);
        printf ("\tshr $1, %%%s\n", r);
        
        printf ("\tcmp %%%s, %%%s\n", l, r);
        printf ("\tsetz %%%s\n", get_reg_name (reg, R8L));
        printf ("\tshl $1, %%%s\n", reg);
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
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjnc raisesig\n");
        printf ("\tmov %%%s, %%%s\n", tn->left->reg, reg);
        printf ("\tsubq $1, %%%s\n", reg);
	printf ("\tmovq 0(%%%s), %%%s\n", reg, reg);
        return reg;

}

char *assembler_tail (struct treenode *tn)
{
	char *reg = newreg ();
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjnc raisesig\n");
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
        printf ("\tshl $1, %%%s\n", reg);
        return reg;

}
char *assembler_islist (struct treenode *tn)
{
        char *reg = newreg ();
        printf ("\txor %%%s, %%%s\n", reg, reg);
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjnc notlist\n");
        printf ("\tmovq $1, %%%s\n", reg);
        
        printf ("notlist:\n");
        printf ("\tshl $1, %%%s\n", reg);
        return reg;

}
char *assembler_isfun (struct treenode *tn)
{
        char *l = newreg ();
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq $0, %%%s\n", l);
        printf ("\tshl $1, %%%s\n", l);
        return l;

}

char *assembler_if (struct treenode *tn)
{
        char *reg = newreg ();
        /*if (tn->left)
                printf ("left # name: %s, reg: %%%s\n", tn->left->name, tn->left->reg);
        if (tn->right)
                printf ("right # name: %s, reg: %%%s\n", tn->right->name, tn->right->reg);
        printf ("\tjnz LBL%d\n", lbl);
                */

        printf ("\n");
        
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, reg);
        printf ("\tshr $1, %%%s\n", reg);
        printf ("\tcmp $0, %%%s\n", reg);
        printf ("\tjz LBL%d\n", lbl);
        
        return reg;
}
char *assembler_then (struct treenode *tn)
{
        int label = lbl;
        printf ("\n");
        /*
        if (tn->left)
                printf ("left # name: %s, reg: %%%s\n", tn->left->name, tn->left->reg);
        if (tn->right)
                printf ("right # name: %s, reg: %%%s\n", tn->right->name, tn->right->reg);
              */ 
        printf ("\tshl $1, %%%s\n", tn->left->reg);
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, tn->reg);
        printf ("\tjmp LBL%d\n", ++lbl);
        printf ("LBL%d:\n", label);
        return tn->left->reg;
}

char *assembler_else (struct treenode *tn)
{
        printf ("\n");
        /*if (tn->left)
                printf ("left # name: %s, reg: %%%s\n", tn->left->name, tn->left->reg);
        if (tn->right)
                printf ("right # name: %s, reg: %%%s\n", tn->right->name, tn->right->reg);
                */
                
        printf ("\tshl $1, %%%s\n", tn->left->reg);
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, tn->reg);
        printf ("\tjmp LBL%d\n", lbl);
        return tn->left->reg;
}

char *assembler_orphan (struct treenode *tn)
{
        /*printf ("ORPHAN\n"); 
        if (tn->left)
                printf ("left # name: %s, reg: %%%s\n", tn->left->name, tn->left->reg);
        if (tn->right)
                printf ("right # name: %s, reg: %%%s\n", tn->right->name, tn->right->reg);
        */

        printf ("\tjmp LBL%s\n", tn->left->name); 
        printf ("LBL%d:\n", lbl++); 
        return tn->left->reg;
}

char *assembler_let (struct treenode *tn)
{
        /*if (tn->left)
        printf ("let:\n");
                printf ("left # name: %s, reg: %%%s\n", tn->left->name, tn->left->reg);
        if (tn->right)
                printf ("right # name: %s, reg: %%%s\n", tn->right->name, tn->right->reg);
        */

        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, tn->left->reg);
        printf ("\n");
        return tn->left->reg;
}

char *assembler_in (struct treenode *tn)
{
        /*if (tn->left)
        printf ("in:\n");
                printf ("left # name: %s, reg: %%%s\n", tn->left->name, tn->left->reg);
        if (tn->right)
                printf ("right # name: %s, reg: %%%s\n", tn->right->name, tn->right->reg);

        */

        printf ("\tmovq %%%s, %%%s\n", tn->right->reg, tn->left->reg);
        printf ("\n");
        printf ("\tjmp LBL%d\n", lbl);
        return tn->left->reg;
}

char *assembler_fcall (struct treenode *tn)
{
        /*if (tn->left)
                printf ("left # name: %s, reg: %%%s\n", tn->left->name, tn->left->reg);
        if (tn->right)
                printf ("right # name: %s, reg: %%%s\n", tn->right->name, tn->right->reg);
                */
        

        printf ("\n");
        printf ("\tmovq %%%s, %%rdi\n", tn->right->reg); 
        printf ("\tjmp %s\n", tn->left->name);
        /*printf ("\tmovq %%rax, %%%s\n", tn->right->reg); 
        */
        return tn->right->reg;

}
