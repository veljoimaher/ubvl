#ifndef __NODE_H__
#define __NODE_H__

#define DEFINITION  0
#define FUNCTION    1
#define VARIABLE    2

struct list {

        int type;
        struct list *next; 
        /* user defined data fields follow here */
        char* name;
        int val;
};

struct list *insert_elem (int type, struct list *l, char *name);
struct list *merge_elems (struct list *l1, struct list *l2);
void isPresent (struct list *l, char *name);

#endif
