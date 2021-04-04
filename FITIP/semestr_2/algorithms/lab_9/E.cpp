#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_NODES_NUM 100100

using namespace std;

vector<int> nodes_list[MAX_NODES_NUM];
vector<int> topsorted_nodes;
bool node_color[MAX_NODES_NUM];

void top_sort(int node) {
    node_color[node] = true;
    for (int next_node : nodes_list[node]) {
        if (!node_color[next_node]) {
            top_sort(next_node);
        }
    }

    topsorted_nodes.push_back(node);
}

int main() {
    //freopen("test_input.txt", "r", stdin);
    freopen("hamiltonian.in", "r", stdin);
    freopen("hamiltonian.out", "w", stdout);

    int n;
    int m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x;
        int y;
        cin >> x >> y;
        nodes_list[x].push_back(y);
    }

    //using topological sorting
    for (int i = 1; i <= n; i++) {
        if (!node_color[i]) {
            top_sort(i);
        }
    }
    reverse(topsorted_nodes.begin(), topsorted_nodes.end());

    //check gamilton path
    bool has_gamiltoh_path = true;
    
    int cur_node = topsorted_nodes[0];
    for (int i = 1; i < n; i++) {
        int next_node = topsorted_nodes[i];

        bool can_go_to_next_node = false;
        for (int node : nodes_list[cur_node]) {
            if (node == next_node) {
                can_go_to_next_node = true;
                break;
            }
        }

        if (!can_go_to_next_node) {
            has_gamiltoh_path = false;
            break;
        }

        cur_node = next_node;
    }

    if (has_gamiltoh_path) {    
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}