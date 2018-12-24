# include <stdio.h>
# include <malloc.h>

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
struct ListNode* make_new_node(int x){
    struct ListNode* newNode = (struct ListNode* )malloc(1 * sizeof(struct ListNode*));
    newNode->element = x;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/// make new empty list
struct MyList* make_new_list(){
    struct MyList* newList = (struct MyList* )malloc(1 * sizeof(struct MyList*));
    newList->front = NULL;
    newList->back = NULL;
    newList->kol = 0;
    return newList;
}

/// list add front
void list_push_front(struct MyList* list, int x){
    if(list == NULL) return ;

    struct ListNode* newNode = make_new_node(x);
    if(list->kol == 0){
        list->front = newNode;
        list->back = newNode;
    }
    else {
        (newNode->right) = (list->front);
        (list->front)->left = newNode;
        list->front = newNode;
    }
    list->kol++;
}

/// list add back
void list_push_back(struct MyList* list, int x){
    if(list == NULL) return ;

    struct ListNode* newNode = make_new_node(x);
    if(list->kol == 0){
        list->front = newNode;
        list->back = newNode;
    }
    else {
        (list->back)->right = newNode;
        newNode->left = (list->back);
        list->back = newNode;
    }
    list->kol++;
}

/// list free
void list_free(struct MyList* list){
    if(list == NULL) return ;

    struct ListNode* node;
    node = (list->front);

    printf("start freeing \n");
    printf("start freeing \n");
    while(node != NULL){
        //printf("element = %d \n", (node->element));
        struct ListNode* next = (node->right);
        free(node);

        node = next;
    }

    free(list);

    printf(" end freeing \n");
}

/// list get node by index
struct ListNode* list_get_node_by_index(struct MyList* list, int index){
    if((0 <= index) && (index < (list->kol))){
        struct ListNode* node = (list->front);
        while(index > 0){
            node = (node->right);
            index--;
        }
        return node;
    }
    return NULL;
}

/// list lenght
int list_size(struct MyList* list){
    if(list == NULL) return 0;
    return (list->kol);
}

/// list get element by index
int list_get_element_by_index(struct MyList* list, int index){
    if((0 <= index) && (index < (list->kol))){
        struct ListNode* node = (list->front);
        while(index > 0){
            node = (node->right);
            index--;
        }
        return node->element;
    }
    return 0;
}

/// sum of elements
int list_get_sum_of_elements(struct MyList* list){
    if(list == NULL) return 0;
    if(list->kol == 0) return 0;
    struct ListNode* node = (list->front);
    int sum = 0;
    while(node != NULL){
        sum += (node->element);
        node = (node->right);
    }
    return sum;
}

/// do for each
void list_foreach(struct ListNode* node, void (*f)(int)){
    while(node != NULL){
        f(node->element);
        node = (node->right);
    }
}

/// map list
struct MyList* list_map(struct MyList* list, int (*f)(int)){
    if(list == NULL) return NULL;

    struct MyList* newList = make_new_list();
    struct ListNode* node = (list->front);
    while(node != NULL){
        list_push_back(newList, f(node->element));
        node = (node->right);
    }

    return newList;
}

/// list map mult
struct MyList* list_map_mult(struct MyList* list, int (*f)(int)){
    if(list == NULL) return NULL;

    struct ListNode* node = (list->front);
    while(node != NULL){
        (node->element) = f(node->element);
        node = (node->right);
    }

    return list;
}

/// list fold
int list_fold(int value, int (*f)(int, int), struct MyList* list){
    if(list == NULL) return value;

    struct ListNode* node = (list->front);
    while(node != NULL){
        value = f(value, (node->element));
        node = (node->right);
    }

    return value;
}

/// iterate list
struct MyList* list_iterate(int value, int n, int (*f)(int)){
    struct MyList* list = make_new_list();
    for(int i = 1; i <= n; i++){
        list_push_back(list, value);
        value = f(value);
        //printf("val = %d \n", value);
    }
    return list;
}

/// out print list
void print_list(struct MyList* list){
    if(list == NULL) return ;
    struct ListNode* node = (list->front);
    printf("Lilst : ");
    for(; node; node = (node->right)){
        printf("%d ", (node->element));
    }
    printf("\n");
}













