#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"

int main (void)
{

	struct list *ll = list_create ();
	struct node *tmp_node;
	int i = 0;
	int nr = 0;
	srand (time (NULL));
	printf ("inserting elem [type,val]: ");
	for (i=0; i<10; i++)
	{
		nr = rand ();
		printf ("[%d,%d] ", i, nr);
		tmp_node = (struct node *) malloc (sizeof (struct node));
		tmp_node->type = i;
		tmp_node->val = nr;
		list_push_back (ll, tmp_node);
	}
	printf ("\n");
	printf ("now dumping list\n");
	list_dump (ll);
	return 0;
}
