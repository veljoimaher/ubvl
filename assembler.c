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

char *assembler_asgn (struct treenode *lc, struct treenode *rc)
{
        printf("POCETAK\n");

        return "";

}
char *assembler_lasgn_reg_expr (struct treenode *lc, struct treenode *rc)
{
        printf("func param: %d\n", lc->op);
        return "";

}
char *assembler_lasgn_reg_reg (struct treenode *lc, struct treenode *rc)
{
        printf("lambda reg reg\n");
        return "";

}

char *assembler_add_id_id (struct treenode *lc, struct treenode *rc)
{
        printf ("ADD (reg, reg)\n");
        return "";

}
char *assembler_add_id_num (struct treenode *lc, struct treenode *rc)
{
        printf ("ADD (reg, rc)\n");
        return "";

}
char *assembler_add_num_id (struct treenode *lc, struct treenode *rc)
{
        printf ("ADD (rc, reg)\n");
        return "";

}
char *assembler_add_num_num (struct treenode *lc, struct treenode *rc)
{
        printf ("ADD (rc, rc)\n");
        return "";
        
}
char *assembler_add (struct treenode *lc, struct treenode *rc)
{
        printf ("ADD (term, term)\n");
        return "";

}

char *assembler_sub_id_id (struct treenode *lc, struct treenode *rc)
{
        printf ("SUB (reg, reg)\n");
        return "";

}
char *assembler_sub_id_num (struct treenode *lc, struct treenode *rc)
{
        printf ("SUB (reg, rc)\n");
        return "";

}
char *assembler_sub_num_id (struct treenode *lc, struct treenode *rc)
{

        printf ("SUB (rc, reg)\n");
        return "";
}
char *assembler_sub_num_num (struct treenode *lc, struct treenode *rc)
{
        printf ("SUB (rc, rc)\n");
        return "";

}
char *assembler_sub (struct treenode *lc, struct treenode *rc)
{

        printf ("SUB (term, term)\n");
        return "";
}

char *assembler_mul_id_id (struct treenode *lc, struct treenode *rc)
{
        printf ("MUL (reg, reg)\n");
        return "";

}
char *assembler_mul_id_num (struct treenode *lc, struct treenode *rc)
{
        printf ("MUL (reg, rc)\n");
        return "";

}
char *assembler_mul_num_id (struct treenode *lc, struct treenode *rc)
{
        printf ("MUL (rc, reg)\n");
        return "";

}
char *assembler_mul_num_num (struct treenode *lc, struct treenode *rc)
{
        printf ("MUL (rc, rc)\n");
        return "";

}
char *assembler_mul (struct treenode *lc, struct treenode *rc)
{
        printf ("MUL (term, term)\n");
        return "";

}

char *assembler_and_id_id (struct treenode *lc, struct treenode *rc)
{
        printf ("AND (reg, reg)\n");
        return "";
        
}
char *assembler_and_id_num (struct treenode *lc, struct treenode *rc)
{

        printf ("AND (reg, rc)\n");
        return "";
}
char *assembler_and_num_id (struct treenode *lc, struct treenode *rc)
{
        printf ("AND (rc, reg)\n");
        return "";

}
char *assembler_and_num_num (struct treenode *lc, struct treenode *rc)
{
        printf ("AND (rc, rc)\n");
        return "";

}
char *assembler_and (struct treenode *lc, struct treenode *rc)
{
        printf ("AND (term, term)\n");
        return "";

}

char *assembler_dot_id_id (struct treenode *lc, struct treenode *rc)
{
        printf ("DOT (reg, reg)\n");
        return "";

}
char *assembler_dot_id_num (struct treenode *lc, struct treenode *rc)
{
        printf ("DOT (reg, rc)\n");
        return "";

}
char *assembler_dot_num_id (struct treenode *lc, struct treenode *rc)
{

        printf ("DOT (rc, reg)\n");
        return "";
}
char *assembler_dot_num_num (struct treenode *lc, struct treenode *rc)
{

        printf ("DOT (rc, rc)\n");
        return "";
}
char *assembler_dot (struct treenode *lc, struct treenode *rc)
{
        printf ("DOT (term, term)\n");
        return "";

}
 
char *assembler_less_id_id (struct treenode *lc, struct treenode *rc)
{
        printf ("LESS (reg, reg)\n");
        return "";

}
char *assembler_less_id_num (struct treenode *lc, struct treenode *rc)
{
        printf ("LESS (reg, rc)\n");
        return "";

}
char *assembler_less_num_id (struct treenode *lc, struct treenode *rc)
{
        printf ("LESS (rc, reg)\n");
        return "";

}
char *assembler_less_num_num (struct treenode *lc, struct treenode *rc)
{
        printf ("LESS (rc, rc)\n");
        return "";

}
char *assembler_less (struct treenode *lc, struct treenode *rc)
{
        printf ("LESS (term, term)\n");
        return "";

}

char *assembler_eq_id_id (struct treenode *lc, struct treenode *rc)
{
        printf ("EQ (reg, reg)\n");
        return "";

}
char *assembler_eq_id_num (struct treenode *lc, struct treenode *rc)
{
        printf ("EQ (reg, rc)\n");
        return "";

}
char *assembler_eq_num_id (struct treenode *lc, struct treenode *rc)
{
        printf ("EQ (rc, reg)\n");
        return "";

}
char *assembler_eq_num_num (struct treenode *lc, struct treenode *rc)
{
        printf ("EQ (rc, rc)\n");
        return "";

}
char *assembler_eq (struct treenode *lc, struct treenode *rc)
{
        printf ("EQ (term, term)\n");
        return "";

}

char *assembler_not (struct treenode *lc)
{

        return "";
}
char *assembler_head (struct treenode *lc)
{
        return "";

}
char *assembler_tail (struct treenode *lc)
{
        return "";

}
char *assembler_isnum (struct treenode *lc)
{
        return "";

}
char *assembler_islist (struct treenode *lc)
{
        return "";

}
char *assembler_isfun (struct treenode *lc)
{
        return "";

}
