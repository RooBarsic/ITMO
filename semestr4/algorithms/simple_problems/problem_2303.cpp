/// problems : 2303. (стек) Расстановка скобок

#include <iostream>
#include <string>
#define MAXSTACKSIZE 100

using namespace std;

bool IsStringRight(string&); // прототип функции проверки

struct STACK{ // структура СТЕК
   char A[MAXSTACKSIZE]; // контейнер элементов
   int v; // индекс вершины стека

   void stack_push_back(char e){
        if(v == MAXSTACKSIZE) return ;
        A[v] = e;
        v++;
    }

    char stack_back(){
        if(v == 0) return '#';
        char res = A[v - 1];
        v--;
        return res;
    }
};

STACK S;

int main(){
   // Наальное состояние = Вершина стека = 0
   S.v = 0;

   string str;
   cin >> str; // ввод строки
   if(IsStringRight(str)){
      cout << "String is right";
   }
   else {
      cout << "String is wrong";
   }
   return 0;
}



bool IsStringRight(string& str){
// НАПИШИТЕ ЭТУ ФУНКЦИЮ
// ВОЗВРАЩАЕТ ИСТИНУ В СЛУЧАЕ, ЕСЛИ СТРОКА "ПРАВИЛЬНАЯ"
// ВОЗВРАЩАЕТ ЛОЖЬ, ЕСЛИ СТРОКА "НЕ ПРАВИЛЬНАЯ"
    for(int i = 0, k = int(str.size()); i < k; i++){
        switch(str[i]){
            case '(': S.stack_push_back(')'); break;
            case '[': S.stack_push_back(']'); break;
            case '{': S.stack_push_back('}'); break;
            case ')':
                if(S.stack_back() != ')') return false;
                break;
            case ']':
                if(S.stack_back() != ']') return false;
                break;
            case '}':
                if(S.stack_back() != '}') return false;
                break;
        }
    }
    return true;
}

