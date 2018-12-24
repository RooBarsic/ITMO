#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include"My_List.c"

#define MyList struct MyList
#define ListNode struct ListNode

FILE* get_file(char* fileName){
    FILE* file = fopen(fileName, "r");
    if(file == NULL){
        printf("Can't open file( \n");
        return NULL;
    }
    printf("File was opend) \n");
    return file;
}

void input_data_from_file(MyList* list, char* fileName){
    FILE* input_file = get_file(fileName);
    if(input_file == NULL) return ;

    int x;
    printf("start inputing data \n");
    while(fscanf(input_file, "%d", &x) == 1){
        printf("x = %d \n", x);
        list_push_back(list, x);
    }
    printf("end inputing data \n");

    fclose(input_file);
}

void input_rever_data_from_file(MyList* list, char* fileName){
    FILE* input_file = get_file(fileName);
    if(input_file == NULL) return ;

    int x;
    printf("start inputing data \n");
    while(fscanf(input_file, "%d", &x) == 1){
        printf("x = %d \n", x);
        list_push_front(list, x);
    }
    printf("end inputing data \n");

    fclose(input_file);
}

void print_nth_element_of_list(MyList* list){
    int id;
    printf(" print id : ");
    scanf("%d", &id);

    int x = list_get_element_by_index(list, id);
    if(x == 0) printf(" Sorry. List too short! ");
    else printf("%d element of list is %x \n", id, x);
}

void f_print_a(int a){printf("%d ",a);return;}
void f_println_a(int a){printf("%d\n",a);return;}
int f_square(int a){return (a*a);}
int f_cube(int a){return a*a*a;}
int f_sum(int x,int a){return x+a;}
int f_max(int x,int a){return ((x>a)?x:a);}
int f_min(int x,int a){return ((x>a)?a:x);}
int f_module(int x){return abs(x);}
int f_mult_2(int base){return base * 2;}

bool save_to_file(MyList* list, const char* filename){
    FILE* out_file = fopen(filename, "w");
    if(out_file == NULL) return false;
    if(list == NULL) return true;

    ListNode* node = (list->front);
    while(node){
        fprintf(out_file, "%d ", (node->element));
        node = (node->right);
    }

    fclose(out_file);
    return true;
}

bool serialize_list(MyList* list, const char* filename){
    FILE* out_file = fopen(filename, "w");
    if(out_file == NULL){
        return false;
        fclose(out_file);
    }
    if(list == NULL) return true;

    ListNode* node = (list->front);
    while(node){
        fwrite(&(node->element),sizeof(int),1,out_file);
        node = (node->right);
    }

    fclose(out_file);
    return true;
}

bool deserialize_list(MyList** list, const char* filename){
    int x;
    FILE* input_file = fopen(filename,"rb");
    if (input_file){
        while (fread(&x,sizeof(int), 1, input_file)>0){
            list_push_back(list, x);
        }
        fclose(input_file);
        return true;
    } else
    {
        fclose(input_file);
        return false;
    }
    //fclose(fr);
}

int main(){
/// Assigment 1
    printf("Program1 begin \n");
    MyList* list = make_new_list();

    printf("\n save input data into list \n");
    input_rever_data_from_file(list, "input.txt");

    printf("\n print received list \n");
    print_list(list);

    printf("\n Sum of elements in list = %d \n", list_get_sum_of_elements(list));

    printf("\n print nth element of list \n");
    print_nth_element_of_list(list);

    print_list(list);

    list_free(list);

    printf("\n Program1 end \n");

/// Assigment 2
    printf("\n Program2 begin \n");
    MyList* list2 = make_new_list();

    printf("\n save input data into list \n");
    input_data_from_file(list2, "input.txt");

    /// for each -------------------------------------
    printf("\n Test for each : \n");
    void (*f)(int) = NULL;
    f = &f_print_a;
    list_foreach(list2->front, f);
    f = &f_println_a;
    list_foreach(list2->front, f);
    f = &f_println_a;

    /// map -----------------------------------------
    printf("\n Test map : \n");
    f = &f_square;
    MyList* list3 = list_map(list2, f);
    print_list(list3);

    f = &f_cube;
    MyList* list4 = list_map(list2, f);
    print_list(list4);

    /// fold -------------------------------------------
    printf("\n Test fold : \n ");
    f = &f_sum;
    printf(" sum = %d \n", list_fold(0, f, list2));
    printf(" min = %d \n", list_fold(list_get_element_by_index(list2, 0), &f_min, list2));
    printf(" max = %d \n", list_fold(list_get_element_by_index(list2, 0), &f_max, list2));

    /// map mult -------------------------------------------
    printf("\n Test map mult : \n ");
    f = &f_module;
    list2 = list_map_mult(list2, f);
    print_list(list2);

    /// iterate -------------------------------------------
    printf("\n Test itterate : \n ");
    MyList* list5 = list_iterate(1, 10, &f_mult_2);
    print_list(list5);

    /// save list file -------------------------------------------
    printf("\n Test save list : \n ");
    printf("list 5 = "); print_list(list5);
    printf("%s", save_to_file(list5, "out1.txt")?"true":"false");
    MyList* list6 = make_new_list();
    input_data_from_file(list6, "out1.txt");
    printf("list6 = "); print_list(list6);

    /// serialize and deserialize list --------------------------------------------------
    printf("\n Test serialize and deserialize list : \n ");
    printf("list 5 = "); print_list(list5);
    printf("%s", serialize_list(list5, "out2.txt")?"true":"false");
    MyList* list7 = make_new_list();
    deserialize_list(list7, "out2.txt");
    printf("list7 = "); print_list(list7);

    list_free(list2);
    list_free(list3);
    list_free(list4);
    list_free(list5);
    list_free(list6);
    list_free(list7);

    printf("\n Program2 end \n");
}
