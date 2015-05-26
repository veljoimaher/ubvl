#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__


assembler_asgn (struct treenode *lc, struct treenode *rc);
assembler_lasgn_reg_expr (struct treenode *lc, struct treenode *rc);
assembler_lasgn_reg_reg (struct treenode *lc, struct treenode *rc)

assembler_add_id_id (struct treenode *lc, struct treenode *rc);
assembler_add_id_num (struct treenode *lc, struct treenode *rc);
assembler_add_num_id (struct treenode *lc, struct treenode *rc);
assembler_add_num_num (struct treenode *lc, struct treenode *rc);
assembler_add (struct treenode *lc, struct treenode *rc);

assembler_sub_id_id (struct treenode *lc, struct treenode *rc);
assembler_sub_id_num (struct treenode *lc, struct treenode *rc);
assembler_sub_num_id (struct treenode *lc, struct treenode *rc);
assembler_sub_num_num (struct treenode *lc, struct treenode *rc);
assembler_sub (struct treenode *lc, struct treenode *rc);

assembler_mul_id_id (struct treenode *lc, struct treenode *rc);
assembler_mul_id_num (struct treenode *lc, struct treenode *rc);
assembler_mul_num_id (struct treenode *lc, struct treenode *rc);
assembler_mul_num_num (struct treenode *lc, struct treenode *rc);
assembler_mul (struct treenode *lc, struct treenode *rc);

assembler_and_id_id (struct treenode *lc, struct treenode *rc);
assembler_and_id_num (struct treenode *lc, struct treenode *rc);
assembler_and_num_id (struct treenode *lc, struct treenode *rc);
assembler_and_num_num (struct treenode *lc, struct treenode *rc);
assembler_and (struct treenode *lc, struct treenode *rc);

assembler_dot_id_id (struct treenode *lc, struct treenode *rc);
assembler_dot_id_num (struct treenode *lc, struct treenode *rc);
assembler_dot_num_id (struct treenode *lc, struct treenode *rc);
assembler_dot_num_num (struct treenode *lc, struct treenode *rc);
assembler_dot (struct treenode *lc, struct treenode *rc);

assembler_less_id_id (struct treenode *lc, struct treenode *rc);
assembler_less_id_num (struct treenode *lc, struct treenode *rc);
assembler_less_num_id (struct treenode *lc, struct treenode *rc);
assembler_less_num_num (struct treenode *lc, struct treenode *rc);
assembler_less (struct treenode *lc, struct treenode *rc);

assembler_eq_id_id (struct treenode *lc, struct treenode *rc);
assembler_eq_id_num (struct treenode *lc, struct treenode *rc);
assembler_eq_num_id (struct treenode *lc, struct treenode *rc);
assembler_eq_num_num (struct treenode *lc, struct treenode *rc);
assembler_eq (struct treenode *lc, struct treenode *rc);

assembler_not (struct treenode *lc);
assembler_head (struct treenode *lc);
assembler_tail (struct treenode *lc);
assembler_isnum (struct treenode *lc);
assembler_islist (struct treenode *lc);
assembler_isfun (struct treenode *lc);

#endif
