/**
timus problem : 1005. Куча камней
http://acm.timus.ru/problem.aspx?space=1&num=1005
Решим задачу перебором, поддерживая при этом разность
элементов в кучах. Из всех вариантов - возьмём налучший(min).
	Time complexity - O(2^n);
 * */
# include <iostream>
  using namespace std;
  int ans;
  int arr[20];
  void way(int n, int differ){
      if(n == 0) ans = min(ans, abs(differ));
      else {
          way(n - 1, differ + arr[n]);
          way(n - 1, differ - arr[n]);
      }
  }
  void solve(){
      int n;
      cin >> n;
      for(int i = 1; i <= n; i++){
          cin >> arr[i];
      }
      ans = 2000000;
      way(n, 0);
      cout << ans;
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
