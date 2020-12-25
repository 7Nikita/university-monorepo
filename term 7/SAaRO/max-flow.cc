#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>

#define files files1;files2
#define files1 freopen("flow.in", "r", stdin)
#define files2 freopen("flow.out", "w", stdout)

const int inf = 2e9;
const int mod = 1e9 + 7;
const int maxn = 1e4;
const long long llinf = 2e18 + 5;

using namespace std;

struct Edge {
    int to;
    long long cap;
    long long flow;

    Edge(int to, long long cap) {
        this->to = to;
        this->cap = cap;
        flow = 0;
    }
};

long long d[maxn];
vector<int> g[maxn];
vector<Edge> e;

bool bfs(int s, int t, int n) {
    queue<int> q;
    fill(d, d + n, llinf);
    d[s] = 0;
    q.push(s);
    while(!q.empty() && d[t] == llinf) {
        int v = q.front();
        q.pop();
        for (const auto& i: g[v]) {
            int to = e[i].to;
            if (e[i].cap > e[i].flow && d[to] > d[v] + 1) {
                d[to] = d[v] + 1;
                q.push(to);
            }
        }
    }
    return d[t] != llinf;
}

long long dfs(int v, int t, long long flow) {
    if (flow == 0 || v == t) {
        return flow;
    }
    for (auto idx = 0; idx < g[v].size(); ++idx) {
        int i = g[v][idx];
        int to = e[i].to;
        if (d[to] != d[v] + 1) {
            continue;
        }
        long long push = dfs(to, t, min(flow, e[i].cap - e[i].flow));
        if (push != 0) {
            e[i].flow += push;
            e[i ^ 1].flow -= push;
            return push;
        }
    }
    return 0;
}

long long dinic(int s, int t, int n) {
    long long flow = 0;
    while(bfs(s, t, n)) {
        long long push = 0;
        do {
            push = dfs(s, t, llinf);
            flow += push;
        } while(push != 0);
    }
    return flow;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    files;

    int m, n;
    cin >> m >> n;

    int s, t;
    cin >> s >> t;
    --s;
    --t;

    for (int i = 0; i < n; ++i) {
        int v, u, w;
        cin >> v >> u >> w;
        --v;
        --u;
        g[v].push_back(e.size());
        g[u].push_back(e.size() + 1);
        e.emplace_back(u, w);
        e.emplace_back(v, 0);
    }

    cout << dinic(s, t, m) << endl;

    for (int i = 0; i < e.size(); i += 2) {
        cout << e[i].flow << endl;
    }

    return 0;
}