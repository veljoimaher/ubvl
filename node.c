#include <stdlib.h>
#include <stdio.h>
#include "node.h"


struct list *insert_elem (int type, struct list *l, char *name)
{

        struct list *new;
        struct list *head;
        new = (struct list *) malloc (sizeof (struct list));
        head = (struct list *) malloc (sizeof (struct list));

        if (l == NULL)
        {
                printf ("passed list is empty: creating new list\n");
                l = (struct list *) malloc (sizeof (struct list));
                l->next = NULL;
        }
        else
                printf ("passed non list is empty\n");

        head = new;
        while (l != NULL)
        {
                new->name = l->name;
                new->type = l->type;
                new->next = l->next;

                new = new->next;
                l = l->next;
        }

        printf ("inserting new element\n");
        new->name = name;
        new->type = type;
        new->next = NULL;
        new->name = name;

        return head;
}

struct list *merge_elems (struct list *l1, struct list *l2)
{

        return NULL;
}

void isPresent (struct list *l, char *name)
{

}

