#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"

// return pointer on newly created list
struct list *list_create (void)
{
	struct list *new = (struct list *) malloc ( sizeof (struct list));

	new->head.prev = NULL;
	new->head.next = &new->tail;
	new->tail.prev = &new->head;
	new->tail.next = NULL;
	return new;
}

void * list_insert (struct node *before, struct node *new)
{
	if (before == NULL || new == NULL)
	{
		fprintf (stderr, "list_insert() - provided node does not exist\n");
		return NULL;
	}

	new->prev = before->prev;
	new->next = before;
	before->prev->next = new;
	before->prev = new;
	return new;
}

struct node * list_head (struct list *list)
{
	if (list == NULL)
		return NULL;
	return &list->head;
}

struct node * list_end (struct list *list)
{
	if (list == NULL)
		return NULL;

	return &list->tail;
}

struct node * list_begin (struct list *list)
{
	if (list == NULL)
		return NULL;
	return list->head.next;
}

struct node * list_back (struct list *list)
{
	if (list == NULL)
		return NULL;

	return list->tail.prev;
}

struct node * list_next (struct node *node)
{
	if (node == NULL)
		return NULL;

	return node->next;
}

struct list * list_push_back (struct list *list, struct node *node)
{
	list_insert (list_end (list), node);
	return list;
}



/*
 * FROM HERE ON FUNCTIONS FOR UEBERSETZERBAU
 */


/* quick and dirty but VERY expensive */
struct list * list_merge_to_new (struct list *f, struct list *s)
{
	struct node *tmp_n;
        struct node *fn = list_head (f);
	struct node *sn = list_head (s);
	struct list *new = list_create ();
	struct list *new_p = new;

        while ( (fn = list_next (fn)) != list_end (f))
        {
		tmp_n = (struct node *) malloc ( sizeof (struct node) );
		tmp_n->name = fn->name;
		tmp_n->val = fn->val;
		tmp_n->type = fn->type;
		list_push_back (new, tmp_n);
        }

	while ( (sn = list_next (sn)) != list_end (s))
        {
		tmp_n = (struct node *) malloc ( sizeof (struct node) );
		tmp_n->name = sn->name;
		tmp_n->val = sn->val;
		tmp_n->type = sn->type;

		if ( list_find (new_p, sn) != NULL) 
			return NULL;

		list_push_back (new, tmp_n);
        }


	return new;
}

struct node * list_find (struct list *list, struct node *node)
{
	struct node *n = list_head (list);
	struct node *np = node;

	if (np->name == NULL)
		return NULL;

	while ( (n = list_next (n)) != list_end (list))
	{
		if (n->name != NULL)
		{
			if (strncmp (n->name, np->name, strlen (np->name)) == 0)
				return n;
		}
	}
	return NULL;
}

void list_dump (struct list *list)
{
	int cnt = 0;
	struct node *n;
	n = list_head (list);
	while ( (n = list_next (n)) != list_end (list))
	{
		fprintf (stdout, "%d\t type: %d, name: '%s', val: %d\n", cnt, n->type, n->name, n->val);
		cnt++;
	}
}

