#include <iostream>
#include <vector>
#include <set>
 
#define MAX_NODES_NUM 2010
 
using namespace std;
 
vector<pair<int,long long>> nodes_list[MAX_NODES_NUM];
long long dist[MAX_NODES_NUM];
 
void digstra(int n, int s) {
    fill(dist + 1, dist + 1 + n, -1);
 
    set<pair<long long,int>> nodes_order;
 
    dist[s] = 0;
    nodes_order.insert({0, s});
 
    while (nodes_order.size() > 0) {
        int cur_node = nodes_order.begin()->second;
        nodes_order.erase(nodes_order.begin());
 
        for (pair<long long, int> node : nodes_list[cur_node]) {
            int node_id = node.first;
            long long node_weight = node.second;
            if (dist[node_id] == -1) {
                dist[node_id] = dist[cur_node] + node_weight;
                nodes_order.insert({dist[node_id], node_id});
            }
            else if (dist[node_id] > dist[cur_node] + node_weight) {
                nodes_order.erase(nodes_order.find({dist[node_id], node_id}));
                dist[node_id] = dist[cur_node] + node_weight;
                nodes_order.insert({dist[node_id], node_id});
            }
        }
    }
}
 
void solve() {
    int n, s, f;
 
    cin >> n >> s >> f;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            long long edge_weight;
            cin >> edge_weight;
            if (edge_weight >= 0) {
                nodes_list[i].push_back({j, edge_weight});
            }
        }
    }
 
    digstra(n, s);
 
    if (dist[f] >= 0) {
        cout << dist[f];
    }
    else {
        cout << "-1";
    }
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
     
    //freopen("intput.txt", "r", stdin);
    freopen("pathmgep.in", "r", stdin);
    freopen("pathmgep.out", "w", stdout);
 
    int k = 1;
    while (k > 0) {
        solve();
        k--;
    }
 
    return 0;
}