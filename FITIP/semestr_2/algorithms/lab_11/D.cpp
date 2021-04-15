# include <iostream>
# include <vector>

#define MAX_NODES_NUM 2100

using namespace std;

vector<int> nodes_list[MAX_NODES_NUM];
long long edges[5100][3];
long long dist[MAX_NODES_NUM];
int color[MAX_NODES_NUM];
int pred[MAX_NODES_NUM];
long long INF = 3000000000000000000;

int relax(int m, int color_mark) {
    int last_relaxed_node = -1;

    for (int i = 1; i <= m; i++) {
        if (dist[edges[i][0]] == INF)
            continue;

        if (dist[edges[i][1]] > dist[edges[i][0]] + edges[i][2]) {
            dist[edges[i][1]] = max(-INF, dist[edges[i][0]] + edges[i][2]);
            last_relaxed_node = edges[i][1];
            pred[edges[i][1]] = edges[i][0];
        }
    }

    return last_relaxed_node;
}

void ford_bellman(int n, int m, int s) {

    fill (dist + 1, dist + 1 + n, INF);

    color[s] = 1;
    dist[s] = 0;


    bool flag = 1;
    int steps =  n * 10;
    while (flag && steps > 0) {
        int last_relaxed_node = relax(m, 1);
        steps--;

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
        do {
            dist[cur_node] = -INF;
            cur_node = pred[cur_node];
        } while (cur_node != y);
    }
    else {
        cout << "NO";
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
     
    //freopen("intput.txt", "r", stdin);
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);


    int n, m, s;
    cin >> n >> m >> s;
    for (int i = 1; i <= n; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    ford_bellman(n, m, s);

    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) {
            cout << "*" << '\n';
        }
        else if (dist[i] == -INF) {
            cout << "-\n";
        }
        else  {
            cout << dist[i] << '\n';
        }
    }
    return 0;
}


