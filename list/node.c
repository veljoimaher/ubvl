#include <stdlib.h>
#include <stdio.h>
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

struct node * list_begin (struct list *list)
{
	if (list == NULL)
		return NULL;
	return list->head.next;
}

struct node * list_end (struct list *list)
{
	if (list == NULL)
		return NULL;

	return &list->tail;
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

void list_dump (struct list *list)
{
	int cnt = 0;
	struct node *n;
	n = list_head (list);
	while ( (n = list_next (n)) != list_end (list))
	{
		fprintf (stdout, "%d\t type: %d, val: %d\n", cnt, n->type, n->val);
		cnt++;
	}
}

