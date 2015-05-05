#ifndef __NODE_H__
#define __NODE_H__

#define DEFINITION  0
#define FUNCTION    1
#define VARIABLE    2

struct node 
{
	struct node *next;
	struct node *prev;
        int type;
        //char* name;
        int val;
};

struct list
{
	struct node head;
	struct node tail;
};

struct list * list_create (void);
struct list * list_find (struct list *l, struct node *n);

void * list_insert (struct node *before, struct node *new);
struct node * list_head (struct list *list);
struct node * list_begin (struct list *list);
struct node * list_end (struct list *list);
struct node * list_next (struct node *node);
struct list * list_push_back (struct list *list, struct node *node);
void list_dump (struct list *l);

#endif
