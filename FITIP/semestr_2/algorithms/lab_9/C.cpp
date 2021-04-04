#include <iostream>
#include <vector>

#define MAX_NODES_NUMBER 100010

using namespace std;

vector<int> nodes_list[MAX_NODES_NUMBER];
int color[MAX_NODES_NUMBER];
bool stop_flag = false;

void paint_component(int node, int node_mark) {
    color[node] = node_mark;
    int new_mark = (node_mark % 2) + 1;
    for (int next_node : nodes_list[node]) {
        if (color[next_node] == 0) {
            paint_component(next_node, new_mark);
        }
        else if (color[next_node] != new_mark) {
            stop_flag = true;
            return ;
        }
        if (stop_flag) {
            return ;
        }
    }
}

int main() {
    //freopen("test_input.txt", "r", stdin);
    freopen("bipartite.in", "r", stdin);
    freopen("bipartite.out", "w", stdout);

    int n;
    int m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x;
        int y;
        cin >> x >> y;
        nodes_list[x].push_back(y);
        nodes_list[y].push_back(x);
    }

    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            paint_component(i, 1);
        }
    }

    if (stop_flag) {
        cout << "NO";
    }
    else {
        cout << "YES";
    }

    return 0;
}