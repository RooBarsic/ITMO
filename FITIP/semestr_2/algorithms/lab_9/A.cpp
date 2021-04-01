#include <iostream>
#include <vector>

#define MAX_NODES_NUMBER 100010

using namespace std;




vector<int> original_graph[MAX_NODES_NUMBER];
int color[MAX_NODES_NUMBER];
vector<int> sorted_nodes_ids;

int way(int node) {
    color[node] = 1;

    for (int next_node : original_graph[node]) {
        if (color[next_node] == 0) {
            int node_proseeding_result = way(next_node);
            if (!node_proseeding_result) {
                return 0;
            }
        } else if (color[next_node] == 1) {
            return 0;
        }
    }
    
    color[node] = 2;
    sorted_nodes_ids.push_back(node);
    return 1;
}

int main() {
    //freopen("test_input.txt", "r", stdin);
    freopen("topsort.in", "r", stdin);
    freopen("topsort.out", "w", stdout);
    
    int n;
    int m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x;
        int y;
        cin >> x >> y;
        original_graph[x].push_back(y);
    }

    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            int node_proseeding_result = way(i);
            if (!node_proseeding_result) {
                cout << "-1";
                return 0;
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        cout << sorted_nodes_ids[i] << " ";
    }

    return 0;
}