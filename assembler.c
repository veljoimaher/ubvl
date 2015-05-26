#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "tree.h"
#include "register.h"



assembler_asgn (struct treenode *lc, struct treenode *rc)
{
        printf("POCETAK\n");

}
assembler_lasgn_reg_expr (struct treenode *lc, struct treenode *rc)
{
        printf("func param: %d\n", lc->op);

}
assembler_lasgn_reg_reg (struct treenode *lc, struct treenode *rc)
{
        printf("lambda reg reg\n");

}

assembler_add_id_id (struct treenode *lc, struct treenode *rc)
{
        printf ("ADD (reg, reg)\n");

}
assembler_add_id_num (struct treenode *lc, struct treenode *rc)
{
        printf ("ADD (reg, rc)\n");

}
assembler_add_num_id (struct treenode *lc, struct treenode *rc)
{
        printf ("ADD (rc, reg)\n");

}
assembler_add_num_num (struct treenode *lc, struct treenode *rc)
{
printf ("ADD (rc, rc)\n");

        
        
}
assembler_add (struct treenode *lc, struct treenode *rc)
{
        printf ("ADD (term, term)\n");

}

assembler_sub_id_id (struct treenode *lc, struct treenode *rc)
{
        printf ("SUB (reg, reg)\n");

}
assembler_sub_id_num (struct treenode *lc, struct treenode *rc)
{
        printf ("SUB (reg, rc)\n");

}
assembler_sub_num_id (struct treenode *lc, struct treenode *rc)
{

        printf ("SUB (rc, reg)\n");
}
assembler_sub_num_num (struct treenode *lc, struct treenode *rc)
{
        printf ("SUB (rc, rc)\n");

}
assembler_sub (struct treenode *lc, struct treenode *rc)
{

        printf ("SUB (term, term)\n");
}

assembler_mul_id_id (struct treenode *lc, struct treenode *rc)
{
        printf ("MUL (reg, reg)\n");

}
assembler_mul_id_num (struct treenode *lc, struct treenode *rc)
{
        printf ("MUL (reg, rc)\n");

}
assembler_mul_num_id (struct treenode *lc, struct treenode *rc)
{
        printf ("MUL (rc, reg)\n");

}
assembler_mul_num_num (struct treenode *lc, struct treenode *rc)
{
        printf ("MUL (rc, rc)\n");

}
assembler_mul (struct treenode *lc, struct treenode *rc)
{
        printf ("MUL (term, term)\n");

}

assembler_and_id_id (struct treenode *lc, struct treenode *rc)
{
        printf ("AND (reg, reg)\n");
        
}
assembler_and_id_num (struct treenode *lc, struct treenode *rc)
{

        printf ("AND (reg, rc)\n");
}
assembler_and_num_id (struct treenode *lc, struct treenode *rc)
{
        printf ("AND (rc, reg)\n");

}
assembler_and_num_num (struct treenode *lc, struct treenode *rc)
{
        printf ("AND (rc, rc)\n");

}
assembler_and (struct treenode *lc, struct treenode *rc)
{
        printf ("AND (term, term)\n");

}

assembler_dot_id_id (struct treenode *lc, struct treenode *rc)
{
        printf ("DOT (reg, reg)\n");

}
assembler_dot_id_num (struct treenode *lc, struct treenode *rc)
{
        printf ("DOT (reg, rc)\n");

}
assembler_dot_num_id (struct treenode *lc, struct treenode *rc)
{

        printf ("DOT (rc, reg)\n");
}
assembler_dot_num_num (struct treenode *lc, struct treenode *rc)
{

        printf ("DOT (rc, rc)\n");
}
assembler_dot (struct treenode *lc, struct treenode *rc)
{
        printf ("DOT (term, term)\n");

}
 
assembler_less_id_id (struct treenode *lc, struct treenode *rc)
{
        printf ("LESS (reg, reg)\n");

}
assembler_less_id_num (struct treenode *lc, struct treenode *rc)
{
        printf ("LESS (reg, rc)\n");

}
assembler_less_num_id (struct treenode *lc, struct treenode *rc)
{
        printf ("LESS (rc, reg)\n");

}
assembler_less_num_num (struct treenode *lc, struct treenode *rc)
{
        printf ("LESS (rc, rc)\n");

}
assembler_less (struct treenode *lc, struct treenode *rc)
{
        printf ("LESS (term, term)\n");

}

assembler_eq_id_id (struct treenode *lc, struct treenode *rc)
{
        printf ("EQ (reg, reg)\n");

}
assembler_eq_id_num (struct treenode *lc, struct treenode *rc)
{
        printf ("EQ (reg, rc)\n");

}
assembler_eq_num_id (struct treenode *lc, struct treenode *rc)
{
        printf ("EQ (rc, reg)\n");

}
assembler_eq_num_num (struct treenode *lc, struct treenode *rc)
{
        printf ("EQ (rc, rc)\n");

}
assembler_eq (struct treenode *lc, struct treenode *rc)
{
        printf ("EQ (term, term)\n");

}

assembler_not (struct treenode *lc)
{

}
assembler_head (struct treenode *lc)
{

}
assembler_tail (struct treenode *lc)
{

}
assembler_isnum (struct treenode *lc)
{

}
assembler_islist (struct treenode *lc)
{

}
assembler_isfun (struct treenode *lc)
{

}


