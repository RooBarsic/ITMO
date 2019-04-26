/*
problem : 1450. Российские газопроводы
http://acm.timus.ru/problem.aspx?space=1&num=1450
Для решения импользуем алгоритм дейкстры для кратчайших 
путей, но мы будем искать путь максимальной стоимости.
O(m * log(n) )
В алгоритме стоит искользовать priority_queue или 
можно просто испольщовать модифицированный поиск в ширину
за O( n + m ), но не сет!
*/
# include <bits/stdc++.h>
# define sz(s) int(s.size())
# define ll long long
  using namespace std;
  int dp[510];
  vector< pair< int, int > > vrr[510];
  void solve(){
      int n, m, f, s;
      cin >> n >> m;
      for(int i = 1; i <= m; i++){
          int x, y, c;
          cin >> x >> y >> c;
          vrr[x].push_back({y, c});
      }
      cin >> s >> f;
      deque< pair< int, int > > que_a;
      que_a.push_back({0, s});
      while(!que_a.empty() > 0){
          int v = que_a.front().second;
          que_a.pop_front();
          for(auto A : vrr[v]){
              int x = A.first;
              int c = A.second;
              if(dp[v] + c > dp[x]){
                  //cout << " v = " << v << " x = " << x << " c = " << c << '\n';
                  dp[x] = dp[v] + c;
                  que_a.push_back({-dp[x], x});
              }
          }
      }
      if(dp[f] == 0) cout << "No solution";
      else cout << dp[f];
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
