#include <iostream>
#include <vector>
#include <set>

#define NODES_MAX_NUM 30010

using namespace std;

vector<pair<int, long long>> nodes_list[NODES_MAX_NUM];
long long dist[NODES_MAX_NUM];

void digstra(int n, int s) {
    set<pair<long long, int>> nodes_sorted_by_dist;

    fill(dist + 1, dist + 1 + n, -1);
    dist[s] = 0;
    nodes_sorted_by_dist.insert({0, s});

    while (!nodes_sorted_by_dist.empty()) {
        int cur_node = nodes_sorted_by_dist.begin()->second;
        long long cur_node_dist = nodes_sorted_by_dist.begin()->first;

        nodes_sorted_by_dist.erase(nodes_sorted_by_dist.begin());

        if (cur_node_dist != dist[cur_node]) {
            continue;
        }

        for (pair<int, long long> node : nodes_list[cur_node]) {
            int node_id = node.first;
            long long edge_weight = node.second;

            if ((dist[node_id] == -1) || (dist[node_id] > dist[cur_node] + edge_weight)) {
                dist[node_id] = dist[cur_node] + edge_weight;
                nodes_sorted_by_dist.insert({dist[node_id], node_id});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
     
    // freopen("intput.txt", "r", stdin);
    freopen("pathbgep.in", "r", stdin);
    freopen("pathbgep.out", "w", stdout);


    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        long long edge_node_a, edge_node_b, edge_weight;
        cin >> edge_node_a >> edge_node_b >> edge_weight;

        nodes_list[edge_node_a].push_back({edge_node_b, edge_weight});
        nodes_list[edge_node_b].push_back({edge_node_a, edge_weight});
    }

    digstra(n, 1);

    for (int j = 1; j <= n; j++) {
        cout << dist[j] << " ";
    }

    return 0;
}