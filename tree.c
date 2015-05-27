#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "node.h"

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

        /* treenode_dump (tree); */
        return tree;
}

struct treenode *new_id_node (char *id_name, struct list *ids)
{
        struct treenode *tree = new_op_node (IDENT, (struct treenode *)NULL, (struct treenode *)NULL);

        tree->reg = get_node_reg (id_name, ids);
        tree->name = id_name;
        printf ("%s reg: %s\n", tree->name, tree->reg);
        
        /* treenode_dump (tree); */
        return tree;
}

struct treenode *new_num_node (long num)
{
        struct treenode *tree = new_op_node (NUM, (struct treenode *)NULL, (struct treenode *)NULL);

        tree->val = num;

        /* treenode_dump (tree); */
        return tree;
}

char *get_node_reg (char *id_name, struct list *ids)
{
        struct node *n;

        n = list_head (ids);
        while ( (n = list_next (n)) != list_end (ids))
        {
                if ((strcmp (n->name, id_name)) && n->type == PARAMETER)
                        return n->reg;
        }

        return "NULL";
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
        if (tn->left != NULL)
                printf ("left: %d\n", tn->left->op);
	else
		printf ("left: NULL\n");
        if (tn->right != NULL)
                printf ("right: %d\n", tn->right->op);
	else
		printf ("right: NULL\n");
}

void tree_dump (struct treenode *t)
{
        if (t != NULL)
        {
                printf ("op: %d, name: %s, val: %d\n", t->op, t->name, t->val);

                if (LEFT_CHILD(t) != NULL)
                {
                        tree_dump (LEFT_CHILD(t));
                }

                if (RIGHT_CHILD(t) != NULL)
                {
                        tree_dump (RIGHT_CHILD(t));
                }

        }
}
