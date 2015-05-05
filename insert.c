#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int main (void)
{
        int i;
        struct list *full;
        struct list *new;
        struct grelem *a;

        full = (struct list *) malloc (sizeof (struct list));
        full->name = "b";
        full->type = 0;
        full->next = NULL;

        new = insert_elem (0, full, "a");

        while (new != NULL)
        {
                printf ("new->name: %s\n", new->name);
                printf ("new->type: %d\n", new->type);
                new = new->next;
        }

        return 0;
}
