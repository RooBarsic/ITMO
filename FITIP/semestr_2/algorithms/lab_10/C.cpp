#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>

using namespace std;
 
#define MAX_NODES_NUMBER 50010

vector<pair<int, pair<int, int>>> edges; // {weight, {start_node, finish_node}}
int node_ancestor[MAX_NODES_NUMBER];
int component_size[MAX_NODES_NUMBER];

void init_dsu(int n) {
    for (int i = 1; i <= n; i++) {
        node_ancestor[i] = i;
        component_size[i] = 1;
    }
}

int find_node_ancestor(int node) {
    if (node == node_ancestor[node]) {
        return node;
    }
    node_ancestor[node] = find_node_ancestor(node_ancestor[node]);

    return node_ancestor[node];
}

void union_nodes(int node_a, int node_b) {
    node_a = find_node_ancestor(node_a);
    node_b = find_node_ancestor(node_b);

    if (node_a != node_b) {
        if (component_size[node_a] < component_size[node_b]) {
            swap(node_a, node_b);
        }

        node_ancestor[node_b] = node_a;
        component_size[node_a] += component_size[node_b];
    }
}

void solve() {
    int n;
    int m;
    cin >> n >> m;

    init_dsu(n);
    edges.clear();

    for (int i = 1; i <= m; i++) {
        int b;
        int e;
        int w;
        cin >> b >> e >> w;
        edges.push_back({w, {b, e}});
    }

    sort(edges.begin(), edges.end());

    long long ans = 0.; 
    for (int i = 0; i < m; i++) {
        int node_a = edges[i].second.first;
        int node_b = edges[i].second.second;

        if (find_node_ancestor(node_a) != find_node_ancestor(node_b)) {
            union_nodes(node_a, node_b);

            ans += edges[i].first * 1ll;
        }
    }

    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
    //freopen("test_input.txt", "r", stdin);
    freopen("spantree2.in", "r", stdin);
    freopen("spantree2.out", "w", stdout);
 
    int test_num = 1;
    while (test_num > 0) {
        test_num--;
        solve();
        //cout << '\n';
    }
 
    return 0;
}