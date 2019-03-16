/*
problem : 1207. Медиана на плоскости
http://acm.timus.ru/problem.aspx?space=1&num=1207

2 ≤ N ≤ 10 000
xi, yi (−109 ≤ xi, yi ≤ 109) 
For any point we can find another point - that 
line beenwen this two points divide all another points 
in to two equal number groups
So we can give first point and find for her pair.
Используем знаковую площадь треугольников для деления точек на две стороны.

Time complexity O(n^2). n<=10^4
*/
# include <iostream>
# define sz(s) int(s.size())
# define ll long long
  using namespace std;
  ll arr[10100][2];
  ll area(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3){
      return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
  }
  void solve(){
      int n;
      cin >> n;
      for(int i = 1; i <= n; i++){
          cin >> arr[i][1] >> arr[i][2];
      }
      int mid = (n - 2) / 2;
      for(int i = 2; i <= n; i++){
          int num = 0;
          for(int j = 2; ((j < i) && (num <= mid)); j++){
              if(area(arr[1][1], arr[1][2], arr[i][1], arr[i][2], arr[j][1], arr[j][2]) < 0) num++;
          }
          for(int j = i + 1; ((j <= n) && (num <= mid)); j++){
              if(area(arr[1][1], arr[1][2], arr[i][1], arr[i][2], arr[j][1], arr[j][2]) < 0) num++;
          }
          if(num == (n - 2) / 2){
              cout << i << " 1";
              return ;
          }
      }
  }
  int main()
  {
	  ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
      int t = 1;
      while(t > 0){
          solve();
          t--;
          cout << '\n';
      }
      return 0;
  }


///-------------------------------------------------------------------------
