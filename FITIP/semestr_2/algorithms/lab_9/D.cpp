#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_NODES_NUM 20100

using namespace std;

vector<int> nodes_list[MAX_NODES_NUM];
vector<int> reversed_nodes_list[MAX_NODES_NUM];
vector<int> topsorted_nodes;
int component_by_node[MAX_NODES_NUM];
int node_color[MAX_NODES_NUM];


void top_sort(int node) {
    node_color[node] = 1;
    for (int next_node : nodes_list[node]) {
        if (node_color[next_node] == 0) {
            top_sort(next_node);
        }
    }

    topsorted_nodes.push_back(node);
}

void highlight_component(int node, int component_id) {
    component_by_node[node] = component_id;

    for (int next_node : reversed_nodes_list[node]) {
        if (component_by_node[next_node] == 0) {
            highlight_component(next_node, component_id);
        }
    }
}

int main() {
    //freopen("test_input.txt", "r", stdin);
    freopen("cond.in", "r", stdin);
    freopen("cond.out", "w", stdout);

    int n;
    int m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x;
        int y;
        cin >> x >> y;
        nodes_list[x].push_back(y);
        reversed_nodes_list[y].push_back(x);
    }

    //using topological sorting
    for (int i = 1; i <= n; i++) {
        if (node_color[i] == 0) {
            top_sort(i);
        }
    }
    reverse(topsorted_nodes.begin(), topsorted_nodes.end());

    //highlighting  strongly connected components
    int components_num = 0;
    for (int node : topsorted_nodes) {
        if (component_by_node[node] == 0) {
            components_num++;
            highlight_component(node, components_num);
        }
    }

    cout << components_num << '\n';
    for (int i = 1; i <= n; i++) {
        cout << component_by_node[i] << " ";
    }

}
