#include <iostream>
#include <utility>
#include <set>
#include <vector>
#include <cstdio>
#include <algorithm>

#define files files1;files2
#define files1 freopen("input.txt", "r", stdin)
#define files2 freopen("output.txt", "w", stdout)

const int inf = 2e9;
const int mod = 1e9 + 7;
const int maxn = 2 * 1e5;
const long long llinf = 2e18 + 5;

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    //files;

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a - 1].push_back(make_pair(b - 1, -c));
    }

    const int start = 0;
    const int finish = n - 1;
    vector<long long> dist(n, llinf);

    auto cmp = [&](const int a, const int b) {
        return make_pair(dist[a], a) < make_pair(dist[b], b);
    };

    dist[start] = 0;
    set<int, decltype(cmp)> q(cmp);
    q.insert(start);

    while (!q.empty()) {
        int v = *q.begin();
        if (dist[v] == llinf) break;
        q.erase(q.begin());
        for (const auto& [to, w]: g[v]) {
            if (dist[to] > dist[v] + w) {
                q.erase(to);
                dist[to] = dist[v] + w;
                q.insert(to);
            }
        }
    }

    cout << -dist[finish];

    return 0;
}