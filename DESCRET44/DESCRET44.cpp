#include <iostream>
#include <vector>
#include <climits>
#include <cstring>
#include <algorithm>
#include <Windows.h>

using namespace std;

const int MAX = 100;
int capacity[MAX][MAX];
int flow[MAX][MAX];
bool visited[MAX];
vector<int> adj[MAX];
int n;

int dfs(int u, int t, int minCap, vector<int>& path) {
    if (u == t) {
        path.push_back(t);
        return minCap;
    }
    visited[u] = true;
    path.push_back(u);

    for (int v : adj[u]) {
        int residual = capacity[u][v] - flow[u][v];
        if (!visited[v] && residual > 0) {
            int pushed = dfs(v, t, min(minCap, residual), path);
            if (pushed > 0) {
                flow[u][v] += pushed;
                flow[v][u] -= pushed;
                return pushed;
            }
        }
    }

    path.pop_back();
    return 0;
}

void addEdge(int u, int v, int c) {
    capacity[u][v] = c;
    adj[u].push_back(v);
    adj[v].push_back(u); // ← ключова зміна для зворотного пошуку шляху
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int e;
    cout << "Введіть кількість вершин у графі: ";
    cin >> n;
    cout << "Введіть кількість ребер: ";
    cin >> e;

    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));

    cout << "Введіть ребра у форматі: from to capacity\n";
    for (int i = 0; i < e; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        addEdge(u, v, c);
    }

    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    int s, t;
    cout << "Введіть початкову та кінцеву вершину: ";
    cin >> s >> t;

    int maxFlow = 0;
    int count = 1;

    while (true) {
        memset(visited, false, sizeof(visited));
        vector<int> path;
        int pushed = dfs(s, t, INT_MAX, path);
        if (pushed == 0) break;

        cout << count++ << ". (";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i + 1 < path.size()) cout << ",";
        }
        cout << ") = " << pushed << "\n";

        maxFlow += pushed;
    }

    cout << "\nМаксимальний потік: " << maxFlow << "\n";

    return 0;
}
