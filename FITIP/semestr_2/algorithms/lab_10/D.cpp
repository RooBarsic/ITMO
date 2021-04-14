#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
 
#define MAX_NODES_NUMBER 1010

vector<pair<long long, pair<int, int>>> ordered_edges; // {weight, {start_node, finish_node}}

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
        node_ancestor[node_b] = node_a;
        component_size[node_a] += component_size[node_b];
    }
}

void solve() {
    int n;
    int m;
    cin >> n >> m;

    init_dsu(n);
    for (int i = 1; i <= m; i++) {
        int start_node;
        int end_node;
        long long node_weight;
        cin >> start_node >> end_node >> node_weight;
        ordered_edges.push_back({node_weight, {start_node, end_node}});
    }

    sort(ordered_edges.begin(), ordered_edges.end());

    long long ans = 0;
    for (int i = 0; i < m; i++) {
        int start_node = ordered_edges[i].second.first;
        int end_node = ordered_edges[i].second.second;
        long long node_weight = ordered_edges[i].first;

        if (end_node == 1) {
            continue;
        }

        //cout << " edge : " << start_node << " " << end_node << '\n';
        if ((find_node_ancestor(start_node) != find_node_ancestor(end_node)) && 
                (end_node == find_node_ancestor(end_node))) {
            union_nodes(start_node, end_node);
            //cout << start_node << " " << end_node << " sz = " << component_size[start_node] << '\n';
            ans += node_weight;
        }
    }

    if (component_size[1] == n) {
        cout << "YES" << '\n' << ans;
    } else {
        cout << "NO";
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
    //freopen("test_input.txt", "r", stdin);
    freopen("chinese.in", "r", stdin);
    freopen("chinese.out", "w", stdout);
 
    int test_num = 1;
    while (test_num > 0) {
        test_num--;
        solve();
        //cout << '\n';
    }
 
    return 0;
}