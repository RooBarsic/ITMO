/*
http://acm.timus.ru/problem.aspx?space=1&num=1162
1162. Currency Exchange

Используем модифицированный алгоритм Форда-Беллмана для нахождения 
отрицательного цикла в графе ( Т.к. нам не надо восстанавливать 
* ответ, на надо только сказать ДА или НЕТ )
https://e-maxx.ru/algo/negative_cycle
Только мы будем искать не отрицательный цикл, а положительный

Time complexity : O(n*m) 
 */

# include <bits/stdc++.h>
using namespace std;
struct CashPoint{
    int currencyA, currencyB;
    double commissionAB, commissionBA;
    double rateAB, rateBA;
} arr[110];
double dp[110];

int iterate(int m){
    bool noIterations = true;
    for(int i = 1; i <= m; i++){
        double sum = (dp[arr[i].currencyA] - arr[i].commissionAB) * arr[i].rateAB;
        //cout << arr[i].currencyA << "->" << arr[i].currencyB << " sum = " << sum << '\n';
        if(dp[arr[i].currencyB] < sum){
            dp[arr[i].currencyB] = sum;
            noIterations = false;
        }
        sum = (dp[arr[i].currencyB] - arr[i].commissionBA) * arr[i].rateBA;
        if(dp[arr[i].currencyA] < sum){
            dp[arr[i].currencyA] = sum;
            noIterations = false;
        }
        sum = (dp[arr[i].currencyA] - arr[i].commissionAB) * arr[i].rateAB;
        if(dp[arr[i].currencyB] < sum){
            dp[arr[i].currencyB] = sum;
            noIterations = false;
        }
    }
    return !noIterations;
}

void solve(){
    int n, m, s;
    double value;
    cin >> n >> m >> s >> value;
    for(int i = 1; i <= m; i++){
        cin >> arr[i].currencyA >> arr[i].currencyB
            >> arr[i].rateAB >> arr[i].commissionAB
            >> arr[i].rateBA >> arr[i].commissionBA;
        //cout << " data : A " << arr[i].currencyA << " B " << arr[i].currencyB << '\n';
    }
    dp[s] = value;
    for(int i = 1; i < n; i++){
        iterate(m);
    }
    if(iterate(m)) cout << "YES";
    else cout << "NO";
}

int main(){
    int k = 1;
    while(k > 0){
        solve();
        k--;
        cout << '\n';
    }
	return 0;
}
