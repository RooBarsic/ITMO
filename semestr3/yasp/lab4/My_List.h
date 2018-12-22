#ifndef linkedlist.h
#define linkedlist.h

struct ListNode{
    int element;
    struct listNode* left;
    struct listNode* right;
};

struct MyList{
    struct ListNode* front;
    struct ListNode* back;
    int kol;
};

/// make new listNode
struct ListNode* make_new_node(int x);

/// make new empty list
struct MyList* make_new_list();

/// list add front
void list_push_front(struct MyList* list, int x);

/// list add back
void list_push_back(struct MyList* list, int x);

/// list free
void list_free(struct MyList* list);

/// list get node by index
struct ListNode* list_get_node_by_index(struct MyList* list, int index);

/// list lenght
int list_size(struct MyList* list);

/// list get element by index
int list_get_element_by_index(struct MyList* list, int index);

/// sum of elements
int list_get_sum_of_elements(struct MyList* list);

/// do for each
void list_foreach(struct ListNode* node, void (*f)(int));

/// map list
struct MyList* list_map(struct MyList* list, int (*f)(int));

/// list map mult
struct MyList* list_map_mult(struct MyList* list, int (*f)(int));

/// list fold
int list_fold(int value, int (*f)(int, int), struct MyList* list);

/// iterate list
struct MyList* list_iterate(int value, int n, int (*f)(int));

#endif // MyList
