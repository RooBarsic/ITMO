/// timus problem : 2025. Стенка на стенку
/// http://acm.timus.ru/problem.aspx?space=1&num=2025
/// We have x groups with a people and y groups with (a+1) peopel& so ans =
/// a(n-a) + a(n-2a) + ... + a(n-xa) + (a+1)(n-xa-(a+1)) + 
/// + (a+1)(n-xa-2(a+1)) + ... + (a+1)(n-xa-y(a+1))
/// solution time complexity = O(T)
# include <iostream>
  using namespace std;
  void solve(){
      int n, k;
      cin >> n >> k;
      int a = n / k; /// people in one group
      int x = k - (n % k); /// x groups with a peopel
      int y = n % k; /// y groups with a+1 people
      int ans = a * ((x * n) - ((a * x * (x + 1)) / 2));
      ans += (a + 1) * (((n - (x * a)) * y) - (((a + 1) * y * (y + 1)) / 2));
      cout << ans;
  }
  int main()
  {
      int t;
      cin >> t;
      while(t > 0){
          solve();
          t--;
          cout << '\n';
      }
      return 0;
  }
