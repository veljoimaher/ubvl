#ifndef __NODE_H__
#define __NODE_H__

#define DEFINITION  0
#define PARAMETER    1
#define VARIABLE    2

struct node 
{
	struct node *next;
	struct node *prev;
	char *name;
        int type;
        int val;
};

struct list
{
	struct node head;
	struct node tail;
};

struct list * list_create (void);

void * list_insert (struct node *before, struct node *new);
struct node * list_head (struct list *list);
struct node * list_begin (struct list *list);
struct node * list_end (struct list *list);
struct node * list_next (struct node *node);
struct node * list_back (struct list *list);
struct list * list_push_back (struct list *list, struct node *node);
void list_dump (struct list *l);
struct node * list_find (struct list *list, struct node *node);
struct node * list_find_any_type (struct list *list, struct node *node);
struct list * list_merge_to_new (struct list *first, struct list *second);
struct list * list_merge (struct list *first, struct list *second);
struct list * insert_elem (int type, struct list *list, char *name, int nr);

void isPresent (struct list *l, char *name);
void upucaj (struct list *l, struct list *s);
struct list * list_merge_to_newg (struct list *f, struct list *s);


#endif
