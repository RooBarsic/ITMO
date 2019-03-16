/*
problem : 1521. Военные учения 2
http://acm.timus.ru/problem.aspx?space=1&num=1521
пусть сейчас выщел солдат x. Следуюший солдат должен стоять на
k позиций дальше от x. Если между номерами x+1 (l+1) и x+k (r) - есть
солдат который уже вышел - найдём их количество ( d ) и сдвинем r на 
d позиций. После того как вышел солдат x - мы помечаем его номер - как 
вышедший. Для более эффективного подсчёта - используем дерево Фенвика 
для суммы на отрезке.  

Time complexity n*logk*logn
*/
# include <bits/stdc++.h>
# define sz(s) int(s.size())
# define ll long long
  using namespace std;
  int n, k;
  int trr[100100];
  int sum_0x(int x){
      int s = 0;
      for(; x >= 0; x = (x & (x + 1)) - 1){
          s += trr[x];
      }
      return s;
  }
  void upd_t(int x, int det){
      for(; x < n; x = (x | (x + 1))){
          trr[x] += det;
      }
  }
  int sum_lr(int l, int r){
      return sum_0x(r) - sum_0x(l - 1);
  }
  int get_next(int l){
      int d = k;
      while(d > 0){
          int r = (l + d) % n;
          l = ( l + 1) % n;
          d = 0;
          if(l <= r) d = sum_lr(l, r);
          else d = sum_lr(l, n - 1) + sum_lr(0, r);
          l = r;
      }
      return l;
  }
  void solve(){
      int x;
      cin >> n >> k;
      cout << k << " ";
      x = k - 1;
      for(int i = 2; i <= n; i++){
          upd_t(x, 1);
          x = get_next(x);
          cout << x + 1 << " ";
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
