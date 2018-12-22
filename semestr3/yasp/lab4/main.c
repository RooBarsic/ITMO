#include<stdio.h>
#include"My_List.h"


FILE* get_file(char* fileName){
    FILE* file = fopen(fileName, "r");
    if(file == NULL){
        printf("Can't open file( \n");
        return NULL;
    }
    printf("File was opend) \n");
    return file;
}

void input_data_from_file(struct MyList* list, char* fileName){
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

void print_nth_element_of_list(struct MyList* list){
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

int main(){
/// Assigment 1
    printf("Program1 begin \n");
    struct MyList* list = make_new_list();

    printf("\n save input data into list \n");
    input_data_from_file(list, "input.txt");

    printf("\n print received list \n");
    print_list(list);

    printf("\n Sum of elements in list = %d \n", list_get_sum_of_elements(list));

    printf("\n print nth element of list \n");
    print_nth_element_of_list(list);

    print_list(list);

    list_free(list);

    printf("\n Program1 end \n");
}

