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
        char *r = tn->left->reg;

        r = tn->right->reg;
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
        char *r = newreg();
        printf ("\tmov %%%s, %%%s\n", tn->left->reg, r);
        printf ("\taddq %%%s, %%%s\n", tn->right->reg, r);

        return r;

}
char *assembler_add_id_num (struct treenode *tn)
{
        printf ("\taddq %%%s, %%%s\n", tn->left->reg, tn->right->reg);

        return tn->right->reg;

}
char *assembler_add_num_id (struct treenode *tn)
{
        printf ("\taddq %%%s, %%%s\n", tn->left->reg, tn->right->reg);
        return tn->right->reg;

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
        printf ("\tsubq %%%s, %%%s\n", tn->left->reg, tn->right->reg);
        return tn->right->reg;

}
char *assembler_sub_id_num (struct treenode *tn)
{
        printf ("\tsubq %%%s, %%%s\n", tn->left->reg, tn->right->reg);
        return tn->right->reg;

}
char *assembler_sub_num_id (struct treenode *tn)
{
        printf ("\tsubq %%%s, %%%s\n", tn->left->reg, tn->right->reg);
        return tn->right->reg;
}
char *assembler_sub_num_num (struct treenode *tn)
{
        printf ("\tsubq %%%s, %%%s\n", tn->left->reg, tn->right->reg);
        return tn->right->reg;

}
char *assembler_sub (struct treenode *tn)
{
        printf ("\tsubq %%%s, %%%s\n", tn->left->reg, tn->right->reg);
        return tn->right->reg;

}

char *assembler_mul_id_id (struct treenode *tn)
{
        printf ("MUL (reg, reg)\n");
        return newreg();

}
char *assembler_mul_id_num (struct treenode *tn)
{
        printf ("MUL (reg, rc)\n");
        return newreg();

}
char *assembler_mul_num_id (struct treenode *tn)
{
        printf ("MUL (rc, reg)\n");
        return newreg();

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
        printf ("AND (reg, reg)\n");
        return newreg();

}
char *assembler_and_id_num (struct treenode *tn)
{

        printf ("AND (reg, rc)\n");
        return newreg();
}
char *assembler_and_num_id (struct treenode *tn)
{
        printf ("AND (rc, reg)\n");
        return newreg();

}
char *assembler_and_num_num (struct treenode *tn)
{
        printf ("AND (rc, rc)\n");
        return newreg();

}
char *assembler_and (struct treenode *tn)
{
        printf ("AND (term, term)\n");
        return newreg();

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

char *assembler_not (struct treenode *lc)
{
        printf ("\tnot %%%s\n", lc->left->reg);
        return lc->left->reg;
}
char *assembler_head (struct treenode *lc)
{
        return newreg();

}
char *assembler_tail (struct treenode *lc)
{
        return newreg();

}
char *assembler_isnum (struct treenode *lc)
{
        return newreg();

}
char *assembler_islist (struct treenode *lc)
{
        return newreg();

}
char *assembler_isfun (struct treenode *lc)
{
        return newreg();

}
