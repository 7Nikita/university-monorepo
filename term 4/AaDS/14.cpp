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

#define f first
#define s second
#define endl '\n'
#define pb push_back
#define mp make_pair
#define ll long long
#define ld long double
#define files files1;files2
#define sz(c) int((c).size())
#define all(x) (x).begin(), (x).end()
#define rep(i,a,n) for(int i=a;i<n;i++)
#define per(i,a,n) for(int i=n-1;i>=a;i--)
#define fast_io ios_base::sync_with_stdio(0);
#define files1 freopen("input.txt", "r", stdin)
#define files2 freopen("output.txt", "w", stdout)

const int inf = 2e9;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 500;
const long long llinf = 2e18 + 5;

using namespace std;

int n;
ll g[101][101];

void matrix_prod(ll a[][101], ll b[][101]){
    ll tmp_a[101][101], tmp_b[101][101];
    rep(i, 0, n){
        rep(j, 0, n){
            tmp_a[i][j] = a[i][j];
            tmp_b[i][j] = b[i][j];
        }
    }
    rep(i, 0, n){
        rep(j, 0, n){
            a[i][j] = 0;
            rep(k, 0, n)
                a[i][j] += (tmp_a[i][k] * tmp_b[k][j]) % mod;
            a[i][j] %= mod;
        }
    }
}

void bin_pow(int deg){
    if (deg == 1) 
        return;
    if (deg % 2){
        ll tmp[101][101];
        rep(i, 0, n) rep(j, 0, n) tmp[i][j] = g[i][j];
        bin_pow(deg - 1);
        matrix_prod(g, tmp);
    } else {
        bin_pow(deg / 2);
        matrix_prod(g, g);
    }
}

int main(){
    files;
    int m, u, v, l;
    cin >> n >> m;
    cin >> u >> v >> l;
    if (l == 0){
        cout << (u == v ? 1 : 0);
        return 0;
    }
    while(m--){
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        ++g[a][b];
        ++g[b][a];
    }
    bin_pow(l);
    cout << g[u - 1][v - 1];
    return 0;
}