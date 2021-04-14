#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>

using namespace std;
 
#define MAX_NODES_NUMBER 5010

vector<pair<int, pair<int, int>>> edges; // {weight, {start_node, finish_node}}
int node_coordinates[MAX_NODES_NUMBER][2];
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

int get_nodes_quadratic_distance(int x1, int y1, int x2, int y2) {
    return ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2));
}

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> node_coordinates[i][0] >> node_coordinates[i][1];
    }

    init_dsu(n);
    edges.clear();

    for (int i = 1; i <= n; i++) {
        int node_i_x = node_coordinates[i][0];
        int node_i_y = node_coordinates[i][1];
        for (int j = i + 1; j <= n; j++) {
            int node_j_x = node_coordinates[j][0];
            int node_j_y = node_coordinates[j][1];
            int nodes_quadratic_distance = get_nodes_quadratic_distance(node_i_x, node_i_y, node_j_x, node_j_y);
            edges.push_back({nodes_quadratic_distance, {i, j}});
        }
    }

    sort(edges.begin(), edges.end());

    double ans = 0.;
    int edges_num = int(edges.size());   
    for (int i = 0; i < edges_num; i++) {
        int node_a = edges[i].second.first;
        int node_b = edges[i].second.second;

        if (find_node_ancestor(node_a) != find_node_ancestor(node_b)) {
            union_nodes(node_a, node_b);

            double node_ab_distance = sqrt(edges[i].first * 1.);
            ans += node_ab_distance;
        }
    }

    cout << fixed << setprecision(6) << ans;
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
        cout << '\n';
    }
 
    return 0;
}