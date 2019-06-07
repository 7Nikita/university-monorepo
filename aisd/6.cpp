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

int tree[4 * maxn];

bool cmp(pair< int, pair<int, int> > a, pair<int, pair <int, int> > b){
    return a.f > b.f;
}

void build_tree(int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = -1;
        return;
    }
    int tm = (tl + tr) / 2;
    build_tree((v << 1), tl, tm);
    build_tree((v << 1 | 1), tm + 1, tr);
    tree[v] = -1;
}

void update (int v, int tl, int tr, int l, int r, int val) {
    if (l > r || tree[v] != -1)
        return;
    if (tl == l && tr == r)
        tree[v] = val;
    else {
        int tm = (tl + tr) / 2;
        update((v << 1), tl, tm, l, min(tm, r), val);
        update((v << 1 | 1), tm + 1, tr, max(tm + 1, l), r, val);
    }
}

int get(int v, int tl, int tr, int pos) {
    if (tl == tr)
        return tree[v];
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
        int ans = get((v << 1), tl, tm, pos);
        if (ans == -1) 
            return tree[v];
        return ans;
    } else {
        int ans = get((v << 1 | 1), tm + 1, tr, pos);
        if (ans == -1) 
            return tree[v];
        return ans;
    }
}

int main(){
    files;
    int n, m;
    cin >> n >> m;
    vector< pair < int,  pair <int, int> > > x;
    while(m--){
        int l, r, v;
        cin >> l >> r >> v;
        x.pb({v, {l, r}});
    }
    sort(x.begin(), x.end(), cmp);
    build_tree(1, 1, n);
    for(auto i: x){
        update(1, 1, n, i.s.f, i.s.s, i.f);
    }
    rep(i, 1, n + 1){
        int ans = get(1, 1, n, i);
        cout << (ans == -1 ? mod : ans) << " ";
    }
    return 0;
}