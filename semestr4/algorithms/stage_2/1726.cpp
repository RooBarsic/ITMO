/*
problem : 1726. Кто ходит в гости…
http://acm.timus.ru/problem.aspx?space=1&num=1726

Divide xs and ys, sort them, and for xs and ys count :
how much time we should add segment(x[i]----x[i+1] or y[i]----y[i+1]) 
into the our summ. At the end we divide our summ to ((n-1)*n)/2
becous its number of pair combinations in group of n people.

Time complexity O(n * log(n)) n <= 10^5
*/
# include <bits/stdc++.h>
# define sz(s) int(s.size())
# define ll long long
  using namespace std;
  void solve(){
      int n;
      ll xrr[100100], yrr[100100];
      cin >> n;
      for(int i = 1; i <= n; i++){
          cin >> xrr[i] >> yrr[i];
      }
      sort(xrr + 1, xrr + 1 + n);
      sort(yrr + 1, yrr + 1 + n);
      ll ans = 0ll;
      for(int i = 2; i <= n; i++){
          ans += (xrr[i] - xrr[i - 1]) * (n - i + 1) * (i - 1);
          ans += (yrr[i] - yrr[i - 1]) * (n - i + 1) * (i - 1);
      }
      ans /= (n * (n - 1)) / 2ll;
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
  
/// ------------------------------------------------------------------------------
