/// 2301. (Односвязный линейный список) Слияние двух сортированных списков

#include <iostream>
#include <limits.h>

using namespace std;

struct NODE{

   int Number;
   NODE *Next;
};

NODE * MakeList(int*, int);
NODE *JoinTwoList(NODE*, NODE*);
void print_list(NODE* node);

int main(){
   int Arr1[]={2,3,5,9};
   int Arr2[]={4,6,7,11,16};
   NODE *Head1, *Head2;
   Head1=MakeList(Arr1,sizeof(Arr1)/sizeof(int));
   Head2=MakeList(Arr2,sizeof(Arr2)/sizeof(int));
   NODE *Head = JoinTwoList(Head1, Head2);

   cout << "Head";
   for(NODE* p1=Head; p1!=NULL; p1=p1->Next){    /// @@@  тут начинаем с NODE* p1=Head; а не NODE* p1=Head->Next;
      cout << " -> " << p1->Number;
   }
   return 0;
}

void print_list(NODE* head){
    if(head == NULL) return ;
    cout << head->Number << " ";
    print_list(head->Next);
}

NODE *JoinTwoList(NODE *head1, NODE *head2){
// Выполнить слияние списков с головами Head1 и Head2
// Функция возвращает указатель на голову списка,
// являющегося результатом слияния
// ............................

    if(head1 == NULL) return head2; /// если первый список пуст, возвращаем второй
    if(head2 == NULL) return head1; /// если второй список пуст, возвращаем первый
    NODE* head3 = new NODE;
    head3->Next = NULL;
    if(head1->Number < head2->Number){                  /// если элемент head1 < head2, то
        head3->Number = head1->Number;                  ///   сначала добавляем элемет head1 в head3
        head3->Next = JoinTwoList(head1->Next, head2);  ///     потом хвостом head3 - будет результат слияния хвоста head1 и head2
    }
    else {                                              /// если элемент head1 >= head2, то
        head3->Number = head2->Number;                  ///   сначала добавляем элемет head2 в head3
        head3->Next = JoinTwoList(head1, head2->Next);  ///     потом хвостом head3 - будет результат слияния head1 и head2->Next
    }
    return head3;                                       /// возвращаем head3
}



NODE * MakeList(int Arr[], int n){
    //cout << " n = " << n << '\n';
    // Эта функция создаёт один список
    // Arr - массив чисел, которые должны быть помещены в список
    // n - их количество
    NODE *Head=new NODE,*x;
    Head->Next=NULL; //Явно указываем на NULL
    Head->Number=INT_MAX; // Условное значение головы
    x=Head;
    // Создание собственно списка
    if(n > 0){   /// @@@ смотрим - надо ли добавить положительное число элементов
        Head->Number = Arr[0];     /// @@@ добавляем первый элемент
        for (int i = 1; i < n; i++) {  /// @@@ добавляем остальные элементы - по тому коду - который был на сайте
            x->Next=new NODE;
            x=x->Next;
            x->Number=Arr[i];
            x->Next = NULL;
        }
    }
    return Head;
}
