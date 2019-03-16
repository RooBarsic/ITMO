/*
problem : 1494. Монобильярд
http://acm.timus.ru/problem.aspx?space=1&num=1494
Попробуем проиммитировать игру. Будем хранить 
помер последнего шара - который входил в лузу ( last ). 
Если онмер очередного взятого шара ( х ) - больше чем last,
то добавим от last+1 до х. 
Теперь посмотрим, если х == последнему шару который сейчас в лузе,
то удалим этот шар из лузы и перейдём к следующему взятому шару.
Иначе - мы понимаем что Чичиков - жульничал.

Time complexitu O(n)
*/
# include <bits/stdc++.h>
# define sz(s) int(s.size())
# define ll long long
  using namespace std;
  void solve(){
      int n, x, last;
      cin >> n;
      deque< int > luza;
      last = 0;
      for( int i = 1; i <= n; i++){
          cin >> x;
          if(x > last){
              for(int j = last + 1; j <= x; j++){
                  luza.push_back(j);
              }
              last = x;
          }
          if(luza.back() == x){
              luza.pop_back();
          }
          else {
              cout << "Cheater";
              return ;
          }
      }
      cout << "Not a proof";
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
