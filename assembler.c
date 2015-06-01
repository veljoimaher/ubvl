#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "tree.h"
#include "reg.h"

void func_header (char *fname)
{
        printf ("\t.text\n");
        printf ("\t.global %s\n", fname);
        printf ("\t.type %s, @function\n", fname);
        printf ("%s:\n", fname);
}

char *assembler_asgn (struct treenode *tn)
{
        char *r = tn->left->reg;

        r = tn->left->reg;
        printf("\tmov %%%s, %%rax\n", tn->right->reg);
        printf("\tret\n");

        return r;
}
char *assembler_lasgn_reg_expr (struct treenode *tn)
{
        char *r = tn->right->reg;

        if (strcmp (r, "rdi"))
                printf ("\tshl $1, %%%s\n", r);

        return r;
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
        return tn->left->reg;

}
char *assembler_add_num_num (struct treenode *tn)
{
        printf ("\taddq %%%s, %%%s\n", tn->left->reg, tn->right->reg);
        return tn->right->reg;

}
char *assembler_add (struct treenode *tn)
{
        printf ("\taddq %%%s, %%%s\n", tn->left->reg, tn->right->reg);
        return tn->right->reg;

}

char *assembler_sub_id_id (struct treenode *tn)
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
        printf ("\tsubq %%%s, %%%s\n", r, l);
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
        return tn->left->reg;

}
char *assembler_sub_num_num (struct treenode *tn)
{
        printf ("\tsubq %%%s, %%%s\n", tn->right->reg, tn->left->reg);
        return tn->left->reg;

}
char *assembler_sub (struct treenode *tn)
{
        printf ("\tsubq %%%s, %%%s\n", tn->right->reg, tn->left->reg);
        return tn->left->reg;

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
        
        return r;
}
char *assembler_mul_num_num (struct treenode *tn)
{
        printf ("MUL (rc, rc)\n");
        return newreg();

}
char *assembler_mul (struct treenode *tn)
{
        printf ("MUL (term, term)\n");
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
        return tn->left->reg;


}
char *assembler_and_num_num (struct treenode *tn)
{
        printf ("\tand %%%s, %%%s\n", tn->right->reg, tn->left->reg);
        return tn->left->reg;


}
char *assembler_and (struct treenode *tn)
{
        printf ("\tand %%%s, %%%s\n", tn->right->reg, tn->left->reg);
        return tn->left->reg;


}

char *assembler_dot_id_id (struct treenode *tn)
{
        printf ("DOT (reg, reg)\n");
        return newreg();

}
char *assembler_dot_id_num (struct treenode *tn)
{
        printf ("DOT (reg, rc)\n");
        return newreg();

}
char *assembler_dot_num_id (struct treenode *tn)
{

        printf ("DOT (rc, reg)\n");
        return newreg();
}
char *assembler_dot_num_num (struct treenode *tn)
{

        printf ("DOT (rc, rc)\n");
        return newreg();
}
char *assembler_dot (struct treenode *tn)
{
        printf ("DOT (term, term)\n");
        return newreg();

}

char *assembler_less_id_id (struct treenode *tn)
{
        printf ("LESS (reg, reg)\n");
        return newreg();

}
char *assembler_less_id_num (struct treenode *tn)
{
        printf ("LESS (reg, rc)\n");
        return newreg();

}
char *assembler_less_num_id (struct treenode *tn)
{
        printf ("LESS (rc, reg)\n");
        return newreg();

}
char *assembler_less_num_num (struct treenode *tn)
{
        printf ("LESS (rc, rc)\n");
        return newreg();

}
char *assembler_less (struct treenode *tn)
{
        printf ("LESS (term, term)\n");
        return newreg();

}

char *assembler_eq_id_id (struct treenode *tn)
{
        printf ("EQ (reg, reg)\n");
        return newreg();

}
char *assembler_eq_id_num (struct treenode *tn)
{
        printf ("EQ (reg, rc)\n");
        return newreg();

}
char *assembler_eq_num_id (struct treenode *tn)
{
        printf ("EQ (rc, reg)\n");
        return newreg();

}
char *assembler_eq_num_num (struct treenode *tn)
{
        printf ("EQ (rc, rc)\n");
        return newreg();

}
char *assembler_eq (struct treenode *tn)
{
        printf ("EQ (term, term)\n");
        return newreg();

}

char *assembler_not (struct treenode *tn)
{
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc raisesig\n");
        printf ("\tbtc $1, %%%s\n", tn->left->reg);

        return tn->left->reg;
}
char *assembler_head (struct treenode *tn)
{
        char *reg = newreg ();
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjnc raisesig\n");

        printf ("\tmov %%%s, %%%s\n", tn->left->reg, reg);
        printf ("\tsubq $1, %%%s\n", reg);
        
        return reg;

}
char *assembler_tail (struct treenode *tn)
{
        return newreg();

}
char *assembler_isnum (struct treenode *tn)
{
        char *reg = newreg ();
        printf ("\txor %%%s, %%%s\n", reg, reg);
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjc notnum\n");
        printf ("\tmovq $1, %%%s\n", reg);
        
        printf ("\tnotnum:\n");
        return reg;

}
char *assembler_islist (struct treenode *tn)
{
        char *reg = newreg ();
        printf ("\txor %%%s, %%%s\n", reg, reg);
        printf ("\tbt $0, %%%s\n", tn->left->reg);
        printf ("\tjnc notlist\n");
        printf ("\tmovq $1, %%%s\n", reg);
        
        printf ("\tnotlist:\n");
        return reg;

}
char *assembler_isfun (struct treenode *tn)
{
        char *l = newreg ();
        printf ("\tmovq %%%s, %%%s\n", tn->left->reg, l);
        printf ("\tmovq $0, %%%s\n", l);
        return l;

}
