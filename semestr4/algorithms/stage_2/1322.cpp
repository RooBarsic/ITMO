/*
problem : 1322. Шпион
http://acm.timus.ru/problem.aspx?space=1&num=1322
Пусть нам дано: (s)=("BCABAAA", 3). Тогда выпишем 
в столбик нашу преобразованную последовательность символов
"BCABAAA". Запишем её как последний столбик предыдущей 
матрицы, при этом все предыдущие столбцы оставляем пустыми.
Далее построчно отсортируем матрицу, затем в предыдущий 
столбец запишем "BCABAAA". Опять построчно отсортируем 
матрицу. Продолжая таким образом, можно восстановить 
полный список всех циклических сдвигов строки, которую 
нам надо найти. Выстроив полный отсортированный список
сдвигов, выберем строку с номером, который нам был изначально 
дан. В итоге мы получим искомую строку.

Time complexity O(N + M), where N = s.size(), M - number of
different elements
*/
# include <bits/stdc++.h>
# define sz(s) int(s.size())
# define ll long long
  using namespace std;
  int kol[100], beginn[100], nextt[100100];
  int get_id(char a){
      if(a <= 'Z') return int(a) - int('A');
      if(a == '_') return 26;
      return int(a) - int('a') + 27;
  }
  void solve(){
      int k;
      string s;
      cin >> k >> s;
      for(int i = 0, kpf = sz(s); i < kpf; i++){
          kol[get_id(s[i])]++;
      }
      beginn[0] = 0;
      for(int i = 1; i <= 70; i++){
          beginn[i] = beginn[i - 1] + kol[i - 1];
      }
      for(int i = 0, kpf = sz(s); i < kpf; i++){
          int id = get_id(s[i]);
          int position = beginn[id];
          beginn[id]++;
          nextt[position] = i;
      }
      int x = nextt[k - 1];
      for(int i = 0, kpf = sz(s); i < kpf; i++){
          cout << s[x];
          x = nextt[x];
      }
  }
  int main(){
       // freopen("tester.cpp", "r", stdin);
      int t = 1;
      while(t > 0){
          solve();
          t--;
          cout << '\n';
      }
      return 0;
  }
  














  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  Разбор https://neerc.ifmo.ru/wiki/index.php?title=%CF%F0%E5%EE%E1%F0%E0%E7%EE%E2%E0%ED%E8%E5_%C1%E0%F0%F0%EE%F3%E7%E0-%D3%E8%EB%E5%F0%E0
