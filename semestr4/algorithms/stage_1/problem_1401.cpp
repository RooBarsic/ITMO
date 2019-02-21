/*
problem : 1401. Игроки
http://acm.timus.ru/problem.aspx?space=1&num=1401
Разделяй и властвуй. 
Поделим исходный квадрат более маленькие квадраты ( подзадачи )
и решив задачу для более маленьких квадрвтов - решим и общую задачу
*/
# include <bits/stdc++.h>
# define sz(s) int(s.size())
  using namespace std;
  int x0, y0, color;
  int arr[600][600];
  void way(int x, int y, int det, int type){
      if(det == 1){
          if((x0 == x) && (y0 == y)){  /// type 3
              color++;
              arr[x][y + 1] = arr[x + 1][y] = arr[x + 1][y + 1] = color;
          }
          else if((x0 == x) && (y0 == y + 1)){ /// type 4
              color++;
              arr[x][y] = arr[x + 1][y] = arr[x + 1][y + 1] = color;
          }
          else if((x0 == x + 1) && (y0 == y)){ /// type 2
              color++;
              arr[x][y] = arr[x][y + 1] = arr[x + 1][y + 1] = color;
          }
          else if((x0 == x + 1) && (y0 == y + 1)){ /// type 1
              color++;
              arr[x][y] = arr[x][y + 1] = arr[x + 1][y] = color;
          }
          else if(type == 1){ 
              color++;
              arr[x][y] = arr[x][y + 1] = arr[x + 1][y] = color;
          }
          else if(type == 2){
              color++;
              arr[x][y] = arr[x][y + 1] = arr[x + 1][y + 1] = color;
          }
          else if(type == 3){
              color++;
              arr[x][y + 1] = arr[x + 1][y] = arr[x + 1][y + 1] = color;
          }
          else if(type == 4){
              color++;
              arr[x][y] = arr[x + 1][y] = arr[x + 1][y + 1] = color;
          }
      }
      else {
          int d2 = det / 2;
          if(type == 0){     /// star in (x <= x0 <= x + det) (y <= y0 <= y + det)
              if((x <= x0) && (x0 <= x + d2) && (y <= y0) && (y0 <= y + d2)){
                  /// in term 1
                  way(x, y, d2, 0);
                  way(x, y + d2 + 1, d2, 2);
                  way(x + d2 + 1, y + d2 + 1, d2, 3);
                  way(x + d2 + 1, y, d2, 4);
                  color++;
                  arr[x + d2 + 1][y + d2] = color;
                  arr[x + d2 + 1][y + d2 + 1] = color;
                  arr[x + d2][y + d2 + 1] = color;
              }
              else if((x <= x0) && (x0 <= x + d2) && (y + d2 + 1<= y0) && (y0 <= y + det)){
                  /// in term 2
                  way(x, y, d2, 1);
                  way(x, y + d2 + 1, d2, 0);
                  way(x + d2 + 1, y + d2 + 1, d2, 3);
                  way(x + d2 + 1, y, d2, 4);
                  color++;
                  arr[x + d2][y + d2] = color;
                  arr[x + d2 + 1][y + d2] = color;
                  arr[x + d2 + 1][y + d2 + 1] = color;
              }
              else if((x + d2 + 1 <= x0) && (x0 <= x + det) && (y + d2 + 1 <= y0) && (y0 <= y + det)){
                  /// in term 3
                  way(x, y, d2, 1);
                  way(x, y + d2 + 1, d2, 2);
                  way(x + d2 + 1, y + d2 + 1, d2, 0);
                  way(x + d2 + 1, y, d2, 4);
                  color++;
                  arr[x + d2][y + d2] = color;
                  arr[x + d2 + 1][y + d2] = color;
                  arr[x + d2][y + d2 + 1] = color;
              }
              else if((x + d2 + 1 <= x0) && (x0 <= x + det) && (y <= y0) && (y0 <= y + d2)){
                  /// in term 4
                  way(x, y, d2, 1);
                  way(x, y + d2 + 1, d2, 2);
                  way(x + d2 + 1, y + d2 + 1, d2, 3);
                  way(x + d2 + 1, y, d2, 0);
                  color++;
                  arr[x + d2][y + d2] = color;
                  arr[x + d2][y + d2 + 1] = color;
                  arr[x + d2 + 1][y + d2 + 1] = color;
              }
          }
          else if(type == 1){
              /// type 3
              way(x, y, d2, 1);
              way(x, y + d2 + 1, d2, 2);
              way(x + d2 + 1, y + d2 + 1, d2, 1);
              way(x + d2 + 1, y, d2, 4);
              color++;
              arr[x + d2][y + d2] = color;
              arr[x + d2 + 1][y + d2] = color;
              arr[x + d2][y + d2 + 1] = color;
          }
          else if(type == 2){
              /// term 4
              way(x, y, d2, 1);
              way(x, y + d2 + 1, d2, 2);
              way(x + d2 + 1, y + d2 + 1, d2, 3);
              way(x + d2 + 1, y, d2, 2);
              color++;
              arr[x + d2][y + d2] = color;
              arr[x + d2][y + d2 + 1] = color;
              arr[x + d2 + 1][y + d2 + 1] = color;
          }
          else if(type == 3){
              /// term 1
              way(x, y, d2, 3);
              way(x, y + d2 + 1, d2, 2);
              way(x + d2 + 1, y + d2 + 1, d2, 3);
              way(x + d2 + 1, y, d2, 4);
              color++;
              arr[x + d2 + 1][y + d2] = color;
              arr[x + d2 + 1][y + d2 + 1] = color;
              arr[x + d2][y + d2 + 1] = color;
          }
          else if(type == 4){
              /// term 2
              way(x, y, d2, 1);
              way(x, y + d2 + 1, d2, 4);
              way(x + d2 + 1, y + d2 + 1, d2, 3);
              way(x + d2 + 1, y, d2, 4);
              color++;
              arr[x + d2][y + d2] = color;
              arr[x + d2 + 1][y + d2] = color;
              arr[x + d2 + 1][y + d2 + 1] = color;
          }
      }
  }
  void solve(){
      int n;
      cin >> n >> x0 >> y0;
      color = 0;
      n = (1 << n);
      way(1, 1, n - 1, 0);
      for(int i = 1; i <= n; i++){
          for(int j = 1; j <= n; j++){
              cout << arr[i][j] << " ";
          }
          cout << '\n';
      }
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
