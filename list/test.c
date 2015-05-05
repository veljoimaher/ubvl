#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"

int main (void)
{

	struct list *ll = list_create ();
	struct list *merged;
	struct node *tmp_node;
	struct node *tmp_node_new;
	struct node find_me;
	find_me.name = "ime";
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

	/* test list_find */
	tmp_node = list_back (ll);
	tmp_node->name = "ime";
	struct node * find = list_find (ll, &find_me);

	if (find == NULL)
		printf ("string not found\n");
	else
		printf ("string found, node val: %d, type: %d\n", find->val, find->type);



	/* test merge  without duplicates */
	printf ("testing merge without duplicates with: \n");
	struct list *ll_second = list_create ();
	for (i=0; i<15; i++)
	{
		nr = rand ();
		printf ("[%d,%d] ", i, nr);
		tmp_node_new = (struct node *) malloc (sizeof (struct node));
		tmp_node_new->type = i;
		tmp_node_new->val = nr;
		list_push_back (ll_second, tmp_node_new);
	}
	printf ("\n");
	printf ("now dumping first and second list\n");
	printf ("\nfirst list:\n");
	list_dump (ll);
	printf ("\nsecond list:\n");
	list_dump (ll_second);
	printf ("now merging\n");
	merged = list_merge_to_new (ll, ll_second);
	printf ("done merging printing merged lists\n");
	if (merged != NULL)
		list_dump (merged);
	else
		printf ("duplicate entries while trying to merge\n");

	free (merged);
	printf ("now testing merge with duplicate NAME\n");
	tmp_node = list_back (ll_second);
	tmp_node->name = "ime";

	merged = list_merge_to_new (ll, ll_second);
	if (merged != NULL)
		list_dump (merged);
	else
		printf ("duplicate entries while trying to merge\n");

	free (merged);
	return 0;
}
