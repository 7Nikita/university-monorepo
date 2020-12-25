#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <set>
#include <queue>
#include <deque>

#define files files1;files2
#define files1 freopen("input.txt", "r", stdin)
#define files2 freopen("output.txt", "w", stdout)

const int inf = 2e9;
const int mod = 1e9 + 7;
const int maxn = 666;
const long long llinf = 2e18 + 5;

using namespace std;

struct Edge {
    int to;
    int from;
    int cap;
    int flow;
    int cost;

    Edge(int from, int to, int flow, int cap, int cost)
            : from(from), to(to), flow(flow), cap(cap), cost(cost) {}
};

int dist[maxn];
int path[maxn];
vector<int> g[maxn];
vector<Edge> e;

deque<int> sq;

void spfa(int s, int t, int N) {
    fill(dist, dist + N, inf);
    vector<char> inQ(N, '0');
    dist[s] = 0;
    sq.push_back(s);
    inQ[s] = '1';
    while (!sq.empty()) {
        int v = sq.front();
        sq.pop_front();
        inQ[v] = '0';
        for (int i = 0; i < g[v].size(); ++i) {
            int idx = g[v][i];
            if (e[idx].flow >= e[idx].cap) {
                continue;
            }
            int to = e[idx].to;
            int w = e[idx].cost;
            if (dist[to] > dist[v] + w) {
                dist[to] = dist[v] + w;
                path[to] = idx;
                if (inQ[to] == '0') {
                    to < sq.front() ? sq.push_front(to) : sq.push_back(to);
                    inQ[to] = '1';
                }
            }
        }
    }
}

int minCost(int s, int t, int N) {
    int ans = 0;

    while (true) {
        spfa(s, t, N);

        if (dist[t] == inf) {
            return ans;
        }

        int push = inf;
        int cur = t;
        while (cur != s) {
            Edge prev = e[path[cur]];
            int canPush = prev.cap - prev.flow;
            push = min(push, canPush);
            cur = prev.from;
        }

        cur = t;
        while (cur != s) {
            Edge prev = e[path[cur]];
            e[path[cur]].flow += push;
            e[path[cur] ^ 1].flow -= push;
            ans += push * prev.cost;
            cur = prev.from;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    files;

    int n, m;
    cin >> n >> m;

    const int s = 0;
    const int t = n + m + 1;
    const int N = n + m + 2;

    e.reserve(N * (N - 1) / 2);
    vector<int> towerCaps(n), plantCaps(m);

    for (int i = 1; i <= n; ++i) {
        int towerCap;
        cin >> towerCap;
        g[s].push_back(e.size());
        g[i].push_back(e.size() + 1);
        towerCaps[i - 1] = towerCap;

        e.emplace_back(s, i, 0, towerCap, 0);
        e.emplace_back(i, s, towerCap, towerCap, 0);
    }

    for (int i = 1; i <= m; ++i) {
        int plantCap;
        cin >> plantCap;
        plantCaps[i - 1] = plantCap;

        int from = n + i;
        g[from].push_back(e.size());
        g[t].push_back(e.size() + 1);

        e.emplace_back(from, t, 0, plantCap, 0);
        e.emplace_back(t, from, plantCap, plantCap, 0);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int cost;
            cin >> cost;

            int to = n + j;
            g[i].push_back(e.size());
            g[to].push_back(e.size() + 1);

            int capacity = min(towerCaps[i - 1], plantCaps[j - 1]);

            e.emplace_back(i, to, 0, capacity, cost);
            e.emplace_back(to, i, capacity, capacity, -cost);
        }
    }

    cout << minCost(s, t, N);

    return 0;
}