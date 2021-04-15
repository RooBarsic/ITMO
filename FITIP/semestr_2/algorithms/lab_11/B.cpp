#include <iostream>
#include <vector>
#include <set>

#define NODES_MAX_NUM 210

using namespace std;

vector<pair<int, int>> nodes_list[NODES_MAX_NUM];
int dist[NODES_MAX_NUM][NODES_MAX_NUM];

void digstra(int n, int s) {
    set<pair<int, int>> nodes_sorted_by_dist;

    fill(dist[s] + 1, dist[s] + 1 + n, -1);
    dist[s][s] = 0;
    nodes_sorted_by_dist.insert({0, s});

    while (!nodes_sorted_by_dist.empty()) {
        int cur_node = nodes_sorted_by_dist.begin()->second;
        int cur_node_dist = nodes_sorted_by_dist.begin()->first;

        nodes_sorted_by_dist.erase(nodes_sorted_by_dist.begin());

        if (cur_node_dist != dist[s][cur_node]) {
            continue;
        }

        for (pair<int, int> node : nodes_list[cur_node]) {
            int node_id = node.first;
            int edge_weight = node.second;

            if ((dist[s][node_id] == -1) || (dist[s][node_id] > dist[s][cur_node] + edge_weight)) {
                dist[s][node_id] = dist[s][cur_node] + edge_weight;
                nodes_sorted_by_dist.insert({dist[s][node_id], node_id});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
     
    //freopen("intput.txt", "r", stdin);
    freopen("pathsg.in", "r", stdin);
    freopen("pathsg.out", "w", stdout);


    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int edge_node_a, edge_node_b, edge_weight;
        cin >> edge_node_a >> edge_node_b >> edge_weight;

        nodes_list[edge_node_a].push_back({edge_node_b, edge_weight});
    }

    for (int i = 1; i <= n; i++) {
        digstra(n, i);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << dist[i][j] << " ";
        }
        cout << '\n';
    }

    return 0;
}