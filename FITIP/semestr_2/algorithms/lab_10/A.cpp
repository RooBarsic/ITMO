#include <iostream>
using namespace std;
 
int vertex_degree[110];
 
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x;
        int y;
        cin >> x >> y;
 
        vertex_degree[x]++;
        vertex_degree[y]++;
    }
 
    for (int i = 1; i <= n; i++) {
        cout << vertex_degree[i] << " ";
    }
}
 
int main() {
    //freopen("test_input.txt", "r", stdin);
    freopen("input.txt", "r", stdin);
    freopen("output.txt ", "w", stdout);
 
    int test_num = 1;
    while (test_num > 0) {
        test_num--;
        solve();
        cout << '\n';
    }
 
    return 0;
}