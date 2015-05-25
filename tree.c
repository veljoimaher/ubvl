#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

/*
 * function definitions
 */
void invoke_burm (NODEPTR_TYPE root)
{
        burm_label (root);
        burm_reduce (root, 1);
}

struct treenode *new_op_node (int op, struct treenode *left, struct treenode *right)
{
        struct treenode *tree = (struct treenode *) malloc (sizeof (struct treenode));

        tree->op = op;
        tree->left = left;
        tree->right = right;
        tree->reg = 0;
        tree->val = 0;
        tree->name = "n/a";

        return tree;
}

struct treenode *new_id_node (char *id_name, struct list *ids)
{
        struct treenode *tree = new_op_node (IDENT, NULL, NULL);

        /* tree->reg = get_node_reg (id_name, ids);
         */
        tree->name = id_name;

        return tree;
}

struct treenode *new_num_node (long num)
{
        struct treenode *tree = new_op_node (NUM, NULL, NULL);

        tree->val = num;

        return tree;
}

void treenode_dump (struct treenode *tn)
{
        if (tn == NULL)
        {
                fprintf (stderr, "Can't dump struct treenode: struct treenode is NULL\n");
                exit (4);
        }
                
        printf ("Dumping struct treenode:\n");
        printf ("type: %d\n", tn->op);
        printf ("name: %s\n", tn->name);
        printf ("val: %d\n", tn->val);
}
