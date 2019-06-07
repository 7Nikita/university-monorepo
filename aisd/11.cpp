#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <stack>
#include <deque>
#include <utility>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <iterator>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <complex>
#include <unordered_set>

#define f first
#define s second
#define endl '\n'
#define pb push_back
#define mp make_pair
#define files files1;files2
#define sz(c) int((c).size())
#define all(x) (x).begin(), (x).end()
#define rep(i,a,n) for(int i=a;i<n;i++)
#define per(i,a,n) for(int i=n-1;i>=a;i--)
#define fast_io ios_base::sync_with_stdio(0);
#define files1 freopen("input.txt", "r", stdin)
#define files2 freopen("output.txt", "w", stdout)

using namespace std;


typedef long long ll;
typedef long double ld;
typedef pair <ll, ll> pll;
typedef pair <int, int> pii;

const int inf = 2e9;
const int mod = 1e7 + 7;
const int maxn = 1e5 + 500;
const long long llinf = 2e18 + 5;

template<typename T>
void amax(T& x, T y) {
    x = max(x, y);
}
  
template<typename T>
void amin(T& x, T y) {
    x = min(x, y);
}

struct Triplet {
    int f;
    int s;
    int t;
    Triplet(int f, int s, int t){
        this->f = f;
        this->s = s;
        this->t = t;
    }
};

vector<pii> g[maxn];
vector<Triplet> d;
vector<bool> used(maxn);
vector<int> cnt(maxn);

void dfs(int v){
    used[v] = 1;
    cnt[v] = 1;
    for (auto& e: g[v]){
        if (!used[e.f]){
            d.pb({v, e.f, e.s});
            dfs(e.f);
            cnt[v] += cnt[e.f];
        }
    }
}

int main(){
    files;
    int n;
    scanf("%d", &n);
    rep(i, 0, n - 1){
        int a;
        int b;
        int c;
        scanf("%d%d%d", &a, &b, &c);
        --a;
        --b;
        g[a].pb({b, c});
        g[b].pb({a, c});
    }
    dfs(0);
    ll ans = 0;
    for (auto& e: d){
        ans += e.t * 1ll * (n - cnt[e.s]) * 1ll * cnt[e.s] * 2;
        ans %= mod;
    }
    printf("%lld", ans);
    return 0;
}