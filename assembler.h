#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

#include "tree.h"

void func_header (char *fname);
void assembler_emit_signal (struct treenode *tn);

char *assembler_asgn (struct treenode *tn);
char *assembler_lasgn_reg_expr (struct treenode *tn);
char * assembler_lasgn_reg_reg (struct treenode *tn);

char *assembler_add_id_id (struct treenode *tn);
char *assembler_add_id_num (struct treenode *tn);
char *assembler_add_num_id (struct treenode *tn);
char *assembler_add_num_num (struct treenode *tn);
char *assembler_add (struct treenode *tn);

char *assembler_sub_id_id (struct treenode *tn);
char *assembler_sub_id_num (struct treenode *tn);
char *assembler_sub_num_id (struct treenode *tn);
char *assembler_sub_num_num (struct treenode *tn);
char *assembler_sub (struct treenode *tn);

char *assembler_mul_id_id (struct treenode *tn);
char *assembler_mul_id_num (struct treenode *tn);
char *assembler_mul_num_id (struct treenode *tn);
char *assembler_mul_num_num (struct treenode *tn);
char *assembler_mul (struct treenode *tn);

char *assembler_and_id_id (struct treenode *tn);
char *assembler_and_id_num (struct treenode *tn);
char *assembler_and_num_id (struct treenode *tn);
char *assembler_and_num_num (struct treenode *tn);
char *assembler_and (struct treenode *tn);

char *assembler_dot_id_id (struct treenode *tn);
char *assembler_dot_id_num (struct treenode *tn);
char *assembler_dot_num_id (struct treenode *tn);
char *assembler_dot_num_num (struct treenode *tn);
char *assembler_dot (struct treenode *tn);

char *assembler_less_id_id (struct treenode *tn);
char *assembler_less_id_num (struct treenode *tn);
char *assembler_less_num_id (struct treenode *tn);
char *assembler_less_num_num (struct treenode *tn);
char *assembler_less (struct treenode *tn);

char *assembler_eq_id_id (struct treenode *tn);
char *assembler_eq_id_num (struct treenode *tn);
char *assembler_eq_num_id (struct treenode *tn);
char *assembler_eq_num_num (struct treenode *tn);
char *assembler_eq (struct treenode *tn);

char *assembler_not (struct treenode *lc);
char *assembler_head (struct treenode *lc);
char *assembler_tail (struct treenode *lc);
char *assembler_isnum (struct treenode *lc);
char *assembler_islist (struct treenode *lc);
char *assembler_isfun (struct treenode *lc);

char *assembler_if (struct treenode *lc);
char *assembler_then (struct treenode *lc);
char *assembler_else (struct treenode *lc);
char *assembler_let (struct treenode *lc);
char *assembler_in (struct treenode *tn);

char *assembler_fcall (struct treenode *tn);

char *assembler_thenelse (struct treenode *tn);

#endif
