#ifndef __TREE_H__
#define __TREE_H__

#include "node.h"

enum {
        NOT=1, HEAD, TAIL, ISNUM, ISLIST, ISFUN, ADD, SUB, MUL, AND, LESS, EQ, IDENT, NUM, ASGN,
        LASGN, THEN, ELSE, IF
};

#ifdef USE_IBURG
#ifndef BURM
        typedef struct burm_state *STATEPTR_TYPE;
#endif
#else
#define STATEPTR_TYPE int
#endif

struct treenode {

        int op;
        STATEPTR_TYPE state;
        struct treenode *left;
        struct treenode *right;
        char *reg;
        char *name;
        int val;

};

/* 
 * iburg macros 
 */
#define NODEPTR_TYPE struct treenode *
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

void treenode_dump (struct treenode *tn);
void invoke_burm (NODEPTR_TYPE root);
#endif
