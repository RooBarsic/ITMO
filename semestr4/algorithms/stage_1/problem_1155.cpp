/// problem : 1155. Дуоны
/// http://acm.timus.ru/problem.aspx?space=1&num=1155
/*
Для каждой пары - запишем в массив - какие вершины мы рассматриваем и 
как именно собираемся их ликвидировать. Далее пока можем уменьшать степень
пары вершин - делаем это;
-------
|     |
H-E-F-G
| | | |
D-A-B-C
|     |
-------

*/
# include <bits/stdc++.h>
# define sz(s) int(s.size())
  using namespace std;
  int a, b, c, d, e, f, g, h;
  int get_number(char x){
      switch(x){
          case 'A': return a;
          case 'B': return b;
          case 'C': return c;
          case 'D': return d;
          case 'E': return e;
          case 'F': return f;
          case 'G': return g;
          case 'H': return h;
      }
      return 0;
  }
  void annihilation(char x){
      switch(x){
          case 'A': a--; break;
          case 'B': b--; break;
          case 'C': c--; break;
          case 'D': d--; break;
          case 'E': e--; break;
          case 'F': f--; break;
          case 'G': g--; break;
          case 'H': h--; break;
      }
  }
  bool check_pair(string s){
      if((get_number(s[0]) > 0) && (get_number(s[1]) > 0)){
          annihilation(s[0]);
          annihilation(s[1]);
          return true;
      }
      return false;
  }
  void solve(){
      cin >> a >> b >> c >> d >> e >> f >> g >> h;
      vector<string> cheking
         {"DH", "DH-", "DA", "DA-", "DC", "DC-", "DF", "AB+\nDA-\nFB-",
          "HD", "HD-", "HE", "HE-", "HG", "HG-", "HB", "EF+\nHE-\nFB-",
          "EH", "EH-", "EA", "EA-", "EF", "EF-", "EC", "FB+\nEF-\nBC-",
          "AD", "AD-", "AE", "AE-", "AB", "AB-", "AG", "FB+\nAB-\nFG-",
          "FE", "FE-", "FB", "FB-", "FG", "FG-", "FD", "EA+\nFE-\nDA-",
          "BA", "BA-", "BF", "BF-", "BC", "BC-", "BH", "EA+\nBA-\nHE-",
          "GF", "GF-", "GC", "GC-", "GH", "GH-", "GA", "EF+\nGF-\nAE-",
          "CG", "CG-", "CB", "CB-", "CD", "CD-", "CE", "AB+\nCB-\nAE-"};

      string ans = "";
      int steps = 0;
      for(int i = 0, k = sz(cheking); i < k; i += 2){
          while(check_pair(cheking[i])){
              ans += cheking[i + 1] + "\n";
          }
      }
      
      if((a + b + c + d + e + f + g + h > 0)) cout << "IMPOSSIBLE";
      else cout << ans;
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
