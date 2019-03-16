/*
1604. В Стране Дураков
http://acm.timus.ru/problem.aspx?space=1&num=1604

(1 <= k <= 10^4, 0 < arr[i] <= 10000, sum of arr[i] for i from 1 to k <= 1000
arr[i] - количество знаков типа i
Возьмём два знака X Y такие что arr[X] + arr[Y] - максимальна и arr[X] >= arr[Y]
Если мы сможем между каждым знаком X - поставить по одному знаку другого типа, то
для оставшихся знаков чередование не составит труда. Получаем
X Y X Y X Y X Y X Y X
тут последовательно между соседними парами знаков - будем вставлять не использованные знаки
Time complexity O(arr[1] + arr[2] + ... + arr[k]) - т.к. мы используем linced list 
*/
# include <bits/stdc++.h>
# define sz(s) int(s.size())
  using namespace std;
  struct my_node{
      int el;
      my_node *next;
      my_node(int x): el(x), next(NULL) {};
      void add_new_next(my_node *node){
          if(next == NULL) next = node;
          else {
              node->next = next;
              next = node;
          }
      }
      void add_n_x(int n, int x){
          if(n <= 0) return ;
          next = new my_node(x);
          my_node *node = next;
          for(int i = 2; i <= n; i++){
              node->next = new my_node(x);
              node = node->next;
          }
      }
  };
  void print_list(my_node *node){
      while(node != 0){
          cout << (node->el) << " ";
          node = node->next;
      }
  }
  int arr[10100];
  void solve(){
      int k;
      cin >> k;
      int mx_id = 1;
      for(int i = 1; i <= k; i++){
          cin >> arr[i];
          if(arr[mx_id] < arr[i]) mx_id = i;
      }
      my_node *my_list = new my_node(mx_id);
      my_list->add_n_x(arr[mx_id] - 1, mx_id);
      arr[mx_id] = 0;
      my_node *node = my_list;
      for(int i = 1; i <= k; i++){
          for(int j = 1; j <= arr[i]; j++){
              node->add_new_next(new my_node(i));
              node = node->next;
              if(node->next == NULL) node = my_list;
              else node = node->next;
          }
      }
      print_list(my_list);
  }
  int main()
  {
      int t = 1;
      while(t > 0){
          solve();
          t--;
          cout << '\n';
      }
      return 0;
  }

///-------------------------------------------------------------------------------------------------
