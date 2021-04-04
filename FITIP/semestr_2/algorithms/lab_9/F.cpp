#include <iostream>
#include <vector>

#define MAX_NODES_NUMBER 100010

using namespace std;

vector<int> nodes_list[MAX_NODES_NUMBER];
int winer_for_node[MAX_NODES_NUMBER];

int emulate_game(int node) {
    if (winer_for_node[node] == 0) {
        winer_for_node[node] = 2;
        for (int next_node : nodes_list[node]) {
            if (emulate_game(next_node) == 2) {
                winer_for_node[node] = 1;
                break;
            }
        }
    }

    return winer_for_node[node];
}

int main() {
    //freopen("test_input.txt", "r", stdin);
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);

    int n;
    int m;
    int s;
    cin >> n >> m >> s;
    for (int i = 1; i <= m; i++) {
        int x;
        int y;
        cin >> x >> y;
        nodes_list[x].push_back(y);
    }

    if (emulate_game(s) == 1) {
        cout << "First player wins";
    } else {
        cout << "Second player wins";
    }
}