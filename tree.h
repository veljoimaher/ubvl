#ifndef __TREE_H__
#define __TREE_H__

#include "node.h"

enum {
        NOT=1, HEAD, TAIL, ISNUM, ISLIST, ISFUN, ADD, SUB, MUL, AND, LESS, EQ, IDENT, NUM, ASGN,
        LASGN, THEN, ELSE, IF, LET, DOT, ORPHAN, IN, FCALL, THENELSE
};

#ifndef BURM
        typedef struct burm_state *STATEPTR_TYPE;
#endif

struct treenode {

        int op;
        struct treenode *left;
        struct treenode *right;
        STATEPTR_TYPE state;
        char *reg;
        char *name;
        int val;
        int label;

};
typedef struct treenode treenode_ptr;

/* 
 * iburg macros 
 */
#define NODEPTR_TYPE treenode_ptr *
#define OP_LABEL(p) ( (p)->op )
#define LEFT_CHILD(p) ( (p)->left )
#define RIGHT_CHILD(p) ( (p)->right )
#define STATE_LABEL(p) ( (p)->state )
#define PANIC printf

/*
 * function definitions
 */
struct treenode *new_op_node (int op, struct treenode *left, struct treenode *right);
struct treenode *new_id_node (char *id_name, struct list *ids);
struct treenode *new_num_node (long num);
char *get_node_reg (char *id_name, struct list *ids);

void treenode_dump (struct treenode *tn);
void invoke_burm (NODEPTR_TYPE root);
void tree_dump (struct treenode *t);
#endif
