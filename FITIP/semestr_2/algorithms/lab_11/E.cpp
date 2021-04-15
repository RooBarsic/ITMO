# include <iostream>
# include <vector>

#define MAX_NODES_NUM 270

using namespace std;

vector<int> nodes_list[MAX_NODES_NUM];
long long edges[MAX_NODES_NUM * MAX_NODES_NUM][3];
long long dist[MAX_NODES_NUM];
int color[MAX_NODES_NUM];
int pred[MAX_NODES_NUM];
long long INF = 30000000;

int relax(int m, int color_mark) {
    int last_relaxed_node = -1;

    for (int i = 1; i <= m; i++) {
        if (dist[edges[i][1]] > dist[edges[i][0]] + edges[i][2]) {
            dist[edges[i][1]] = max(-INF, dist[edges[i][0]] + edges[i][2]);
            last_relaxed_node = edges[i][1];
            pred[edges[i][1]] = edges[i][0];
        }
    }

    return last_relaxed_node;
}

void ford_bellman(int n, int m) {

    fill (color + 1, color + 1 + n, INF);

    color[1] = 1;
    dist[1] = 0;


    bool flag = 1;
    int steps = 0;
    while (flag && steps < n) {
        int last_relaxed_node = relax(m, 1);
        steps++;

        if (last_relaxed_node == -1) {
            flag = 0;
        }
    }

    int last_relaxed_node = relax(m, 1);

    if (last_relaxed_node != -1) {
        int y = last_relaxed_node;
        for (int i = 1; i <= n; i++) {
            y = pred[y];
        }

        int cur_node = y;
        vector<int> nodes_in_cycle;
        nodes_in_cycle.push_back(y);
        do {
            cur_node = pred[cur_node];
            nodes_in_cycle.push_back(cur_node);
        } while (cur_node != y);

        int l = 0;
        int r = int(nodes_in_cycle.size()) - 1;
        while (l < r) {
            swap(nodes_in_cycle[l], nodes_in_cycle[r]);
            l++;
            r--;
        }

        cout << "YES" << '\n';
        cout << nodes_in_cycle.size() << '\n';
        for (int node : nodes_in_cycle) {
            cout << node << " ";
        }
    }
    else {
        cout << "NO";
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
     
    //freopen("intput.txt", "r", stdin);
    freopen("negcycle.in", "r", stdin);
    freopen("negcycle.out", "w", stdout);


    int n, m;
    cin >> n;
    m = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            long long x;
            cin >> x;
            if (x != 1000000000) {
                m++;
                edges[m][0] = i;
                edges[m][1] = j;
                edges[m][2] = x;
            }
        }
    }

    ford_bellman(n, m);
    return 0;
}


