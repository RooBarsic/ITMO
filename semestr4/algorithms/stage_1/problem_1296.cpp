/*
problem : 1296. Гиперпереход
http://acm.timus.ru/problem.aspx?space=1&num=1296
Lets a[l] + a[l + 1] + ... + a[r] -> sum in block l-r 
if sum in block l-r is <= 0 - it's not good for us,
becous even if a[l-1] + sum(l,r) or a[r+1] + sum(l,r) is > 0,
then why we not get a[l-1] or a[r+1] ( and get more better answer 
then a[l-1] + sum(l,r) or a[r+1] + sum(l,r) ).
So, we just fixed block l-r and try to move r to right. If we 
found that sum(l,r) <= 0, then we will move l to right until 
sum(l,r)  <= 0 and l <= r
*/
# include <bits/stdc++.h>
# define sz(s) int(s.size())
  using namespace std;
  void solve(){
      int n;
      long long arr[60010];
      cin >> n;
      int l = 1;
      long long sum = 0;
      long long ans = 0;
      for(int i = 1; i <= n; i++){
          cin >> arr[i];
          sum += arr[i];
          while((l <= i) && (sum <= 0)){
              sum -= arr[l];
              l++;
          }
          ans = max(ans, sum);
      }
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
