/*
problem : 1160. Network
http://acm.timus.ru/problem.aspx?space=1&num=1160&locale=ru
Задача сводится на нахождение минимального отстовного дерева
Используем алгоритм Крускала http://e-maxx.ru/algo/mst_kruskal
с системой непересакаюшихся множеств 
http://e-maxx.ru/algo/mst_kruskal_with_dsu

Time complexity O(mlog(m))
*/
# include <bits/stdc++.h>
# define sz(s) int(s.size())
# define ll long long
  using namespace std;
  int pred[1010], kol[1010];
  vector< pair< int, pair< int, int > > > mrr; 
  vector< pair< int, int > > ans_network;
  int find_pred(int v){
      if(pred[v] == v) return v;
      return pred[v] = find_pred(pred[v]);
  }
  void union_ab(int a, int b){
      a = find_pred(a);
      b = find_pred(b);
      if(kol[a] < kol[b]) swap(a, b);
      pred[b] = a;
      kol[a] += kol[b];
  }
  void init_snm(int n){
      for(int i = 1; i <= n; i++){
          pred[i] = i;
          kol[i] = 1;
      }
  }
  void solve(){
      int n, m;
      cin >> n >> m;
      init_snm(n);
      for(int i = 1; i <= m; i++){
          int a, b, c;
          cin >> a >> b >> c;
          mrr.push_back({c, {a, b}});
      }
      sort(mrr.begin(), mrr.end());
      int max_length =0;
      for(int i = 0; i < m; i++){
          int a = mrr[i].second.first;
          int b = mrr[i].second.second;
          int len = mrr[i].first;
          if(find_pred(a) != find_pred(b)){
              max_length = max(max_length, len);
              union_ab(a, b);
              ans_network.push_back({a, b});
          }
      }
      n--;
      cout << max_length << '\n' << n << '\n';
      for(int i = 0; i < n; i++){
          cout << ans_network[i].first << " " << ans_network[i].second << '\n';
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
