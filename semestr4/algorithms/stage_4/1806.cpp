/*
///http://acm.timus.ru/problem.aspx?space=1&num=1806
 Мобильные телеграфы
Для каждого солдата, по мере необходимости, найлём его соседей 
* ( соседи - те солдеты кому он может передать сообшение )
по номеру его телефона.
А дальше используем алгоритм Дейкстры от солдата 1 с восстановлением ответа
на priority_queue. И если получилось отправить сообшение солдату n - скажем 
об этом, и перепрыгнемся по предкам солдата n - до солдата 1, и выведем 
путь передачи сообщения от солдата к солдату.

Time complexity
S - length of phone number
calcDelay - O(S)
fillNeibours - O( (S*S + S*10)*log(n)*S )
runDigstra - O((n*n)*log(n) * O(fillNeibours)) ==> O( ((n*log(n))^2) * S^3 )  
* */
# include <bits/stdc++.h>
# define sz(s) int(s.size())
using namespace std;
int pi = 1000000000 + 7;
map< string, int > mp_id;
string phone[50100];
int delay[50100], dp[50100], pred[50100], color[50100];
vector< pair<int, int> > neibours[50100];

inline int calcDelay(string a, string b){
    int l = 0;
    for(int i = 0, k = sz(a); i < k; i++){
        if(a[i] != b[i]) break;
        l++;
    }
    return delay[l];
}

inline void fillNeibours(int id, string s){
    for(int i = 0, k = sz(s); i < k; i++){
        for(int j = i + 1; j < k; j++){
            string t = s;
            swap(t[i], t[j]);
            if((t != s) && (mp_id.find(t) != mp_id.end())) neibours[id].push_back({mp_id[t], calcDelay(s, t)});
        }
        for(int e = 0; e <= 9; e++){
            if(int(s[i]) - int('0') != e){
                string t = s;
                t[i] = char(int('0') + e);
                if(mp_id.find(t) != mp_id.end()) neibours[id].push_back({mp_id[t], calcDelay(s, t)});
            }
        }
    }
}

inline void runDigsra(int n, int start){
    priority_queue< pair<int, int> > deq_a;
    deq_a.push({-dp[start], start});
    while(!deq_a.empty()){
        int v = deq_a.top().second;
        deq_a.pop();
        if(neibours[v].empty()) fillNeibours(v, phone[v]);
        for(auto A : neibours[v]){
            int x = A.first;
            int w = A.second;
            if(dp[x] > dp[v] + w){
                dp[x] = dp[v] + w;
                deq_a.push({-dp[x], x});
                pred[x] = v;
            }
        }
    }
}

inline void solve(){
    int n;
    cin >> n;
    for(int i = 0; i <= 9; i++){
        cin >> delay[i];
    }
    for(int i = 1; i <= n; i++){
        cin >> phone[i];
        mp_id[phone[i]] = i;
        dp[i] = pi;
        pred[i] = i;
    }
    dp[1] = 0;
    runDigsra(n, 1);
    if(dp[n] == pi) cout << "-1";
    else {
        cout << dp[n];
        cout << '\n';
        deque< int > transaction;
        int v = n;
        while(v != pred[v]){
            transaction.push_front(v);
            v = pred[v];
        }
        transaction.push_front(v);
        cout << sz(transaction) << '\n';
        for(int x : transaction){
            cout << x << " ";
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
    int k = 1;
    while(k > 0){
        solve();
        k--;
        cout << '\n';
    }
	return 0;
}
