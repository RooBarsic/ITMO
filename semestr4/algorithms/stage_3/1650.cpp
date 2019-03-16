/*
problem : 1650. Миллиардеры
http://acm.timus.ru/problem.aspx?space=1&num=1650
man_city - по имени человека - получить город его нахождения
man_money - по имени человека - получить его сумму денег
city_money - по названию города - получить сумму денег в городе
result - по названию города - получить количество дней лидирования 
этого города в списке богатейших городов
st_top - хранить города в упорядоченном, по сумме их денег, виде

Проимитируем процессы прилёта в город и отлёта из него
Когда человек меняет свой город, мы уменьшаем сумму денег 
города в котором он был - на сумму денег этого человека.
И увеличиваем сумму денег города прибытия - на сумму
денег этого человека

map и set - позволяют нам совершать все операции добавления и модификации
за log от количества элементов

Time complexity : O(k*log(n+k) + n*log(n))
*/
# include <bits/stdc++.h>
# define sz(s) int(s.size())
# define ll long long
  using namespace std;
  map< string, string > man_city;
  map< string, ll > man_money, city_money, result;
  set< pair< ll , string > > st_top;
  void solve(){
      int n, m, k;
      cin >> n;
      for(int i = 1; i <= n; i++){
          string p_name, p_city;
          ll p_salary;
          cin >> p_name >> p_city >> p_salary;
          man_money[p_name] = p_salary;
          man_city[p_name] = p_city;
          city_money[p_city] += p_salary;
      }
      for(auto it = city_money.begin(); it != city_money.end(); it++){
          st_top.insert({-it->second, it->first});
      }
      cin >> m >> k;
      int d2 = 0;
      for(int i = 1; i <= k; i++){
          int d;
          string p_name, p_city;
          cin >> d >> p_name >> p_city;

          if(d2 != d){
            auto it1 = st_top.begin();
            auto it2 = it1;
            it2++;
            if(sz(st_top) > 1){
                if(it1->first != it2->first)
                    result[it1->second] += d - d2;
            }
            else result[it1->second] += d - d2;
          }

          st_top.erase(st_top.find({-city_money[man_city[p_name]], man_city[p_name]}));
          if(st_top.find({-city_money[p_city], p_city}) != st_top.end())
                st_top.erase(st_top.find({-city_money[p_city], p_city}));

          city_money[man_city[p_name]] -= man_money[p_name];
          st_top.insert({-city_money[man_city[p_name]], man_city[p_name]});

          city_money[p_city] += man_money[p_name];
          st_top.insert({-city_money[p_city], p_city});

          man_city[p_name] = p_city;
          d2 = d;
      }
      auto it1 = st_top.begin();
      auto it2 = st_top.begin();
      it2++;
      if(sz(st_top) > 1){
          if(it1->first != it2->first)
              result[it1->second] += m - d2;
      }
      else result[it1->second] += m - d2;
      for(auto it = result.begin(); it != result.end(); it++){
          if(it->second > 0) cout << (it->first) << " " << (it->second) << '\n';
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

