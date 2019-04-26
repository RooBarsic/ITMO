/*
problem : 1080. Раскраска карты
http://acm.timus.ru/problem.aspx?space=1&num=1080
Расскраска - невозможна в случае наличия цикла из 
нечетного числа элементов. 
Попробуем расскрасить вершины в каждой компоненте 
связанности, и если вдруг обнаружили - что есть ребро
между двумя покрашенными вершинами одного цвета - пректарим
расскраску
Time complexity : O(n + (n * (n + 1)) / 2 )
*/
# include <bits/stdc++.h>
# define sz(s) int(s.size())
# define ll long long
  using namespace std;
  bool status;
  vector< int > vrr[110];
  int color[110];
  void way(int v, int pred, int paint){
      color[v] = paint;
      for(int x : vrr[v]){
          if(x == pred) continue;
          if(color[x] == 0) way(x, v, paint%2 + 1);
          else if(color[x] == paint) status = false;
          if(!status) return ;
      }
  }
  void solve(){
      int n;
      cin >> n;
      for(int i = 1; i <= n; i++){
          int x;
          while((cin >> x) && (x != 0)){
              vrr[i].push_back(x);
              vrr[x].push_back(i);
          }
      }
      status = 1;
      for(int i = 1; i <= n; i++){
          if(color[i] == 0) way(i, 0, 1);
      }
      if(!status) cout << "-1";
      else {
          for(int i = 1; i <= n; i++){
              cout << color[i] - 1;
          }
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
