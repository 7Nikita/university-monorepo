#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int maxn = 17;
const int inf = 2e9;

vector<vector<int>> g(maxn, vector<int>(maxn, inf));
vector<vector<vector<int>>> dp(1 << maxn, vector<vector<int>>(maxn, vector<int>(maxn + 1, inf)));

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    unordered_map<string, int> strToInt;
    for (int i = 0; i < n; ++i) {
        string city;
        cin >> city;
        strToInt[city] = i;
    }

    for (int i = 0; i < m; ++i) {
        string a, b;
        int w;
        cin >> a >> b >> w;

        int c1 = strToInt[a];
        int c2 = strToInt[b];

        g[c1][c2] = w;
        g[c2][c1] = w;
    }

    for (int i = 0; i < n; ++i) {
        int cur_mask = 1 << i;
        dp[cur_mask][i][k] = 0;
    }

    for (int kk = k; kk >= 0; --kk) {
        for (int mask = 1; mask < (1 << n); ++mask) {
            for (int i = 0; i < n; ++i) {
                if (dp[mask][i][kk] == inf) { continue; }
                for (int j = 0; j < n; ++j) {
                    if ((mask & (1 << j)) == 0) {
                        int cost = g[i][j];
                        int mask_j = mask ^ (1 << j);
                        dp[mask_j][j][kk] = min(dp[mask_j][j][kk], dp[mask][i][kk] + cost);
                        if (kk) { dp[mask_j][j][kk - 1] = min(dp[mask_j][j][kk - 1], dp[mask][i][kk]); }
                    }
                }
            }
        }
    }

    int ans = inf;
    int full = (1 << n) - 1;
    for (int i = 0; i < n; ++i) {
        ans = min(ans, *min_element(dp[full][i].begin(), dp[full][i].end()));
    }
    cout << (ans == inf ? -1 : ans);

    return 0;
}