#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
 
#define MAX_NODES_NUMBER 1010
#define MAX_EDGES_NUMBER 10100

int edges[MAX_EDGES_NUMBER][3];
int edge_color[MAX_EDGES_NUMBER];
int node_ancestor[MAX_NODES_NUMBER];
int component_size[MAX_NODES_NUMBER];
int component_color[MAX_NODES_NUMBER];
vector<pair<int, int>> ordered_edges;

void init_dsu(int dsu_size) {

}

int get_node_ancester(int node) {

}

int union_nodes(int node_a, int node_b) {

}

void solve() {
    int n;
    int m;
    cin >> n >> m;
    
    init_dsu(n);
    int edges_size = 0;
    for (int i = 1; i <= m; i++) {
        int start_node;
        int finish_node;
        int edge_weight;
        cin >> start_node >> finish_node >> edge_weight;
        if (finish_node != 1) {
            edges_size++;
            edges[edges_size][0] = start_node;
            edges[edges_size][1] = finish_node;
            edges[edges_size][2] = edge_weight;

            ordered_edges.push_back({edge_weight, edges_size});
        }
    }

    sort(ordered_edges.begin(), ordered_edges.end());

    int flag = 1;
    long long ans = 0;
    while (flag > 0) {
        for (int i = 0; i < edges_size; i++) {
            int edge_id = ordered_edges[i].second;
            if (edge_color[edge_id] == 0) {
                int start_node = edges[edge_id][0];
                int finish_node = edges[edge_id][1];

                if (get_node_ancester(start))
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
    freopen("test_input.txt", "r", stdin);
    //freopen("chinese.in", "r", stdin);
    //freopen("chinese.out", "w", stdout);
 
    int test_num = 1;
    while (test_num > 0) {
        test_num--;
        solve();
        //cout << '\n';
    }
 
    return 0;
}