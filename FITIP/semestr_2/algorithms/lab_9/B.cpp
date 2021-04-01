#include <iostream>
#include <vector>

#define MAX_NODES_NUMBER 100100

using namespace std;

vector<int> cycle_nodes;
vector<int> next_nodes_by_node[MAX_NODES_NUMBER];
int color[MAX_NODES_NUMBER];
int next_node[MAX_NODES_NUMBER];
bool cycle_is_found = false;

void dfs(int node) {
    if (color[node] == 1) {
        cycle_is_found = true;
        int cur_node = node;
        do {
            cycle_nodes.push_back(cur_node);
            cur_node = next_node[cur_node];
        } while (cur_node != node);
        return ;
    }

    color[node] = 1;

    for (int cur_node : next_nodes_by_node[node]) {
        if (color[cur_node] != 2) {
            next_node[node] = cur_node;
            dfs(cur_node);
            if (cycle_is_found) {
                return ;
            }
        }
    }

    color[node] = 2;
}

int main() {
    //freopen("test_input.txt", "r", stdin);
    freopen("cycle.in", "r", stdin);
    freopen("cycle.out", "w", stdout);

    int n;
    int m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x;
        int y;
        cin >> x >> y;
        next_nodes_by_node[x].push_back(y);
    }

    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            dfs(i);
            if (cycle_is_found) {
                break;
            }
        }
    }

    if (cycle_is_found) {
        cout << "YES" << '\n';
        for (int node : cycle_nodes) {
            cout << node << " ";
        }
    } else {
        cout << "NO";
    }

    return 0;
}