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

int main(){
    files;
    
    int n, m, s, f;
    vector < vector < pair <int, int> > > g(maxn);
    vector <bool> used(maxn);
    vector <ll> w(maxn, llinf);
    cin >> n >> m;
    rep(i, 0, m){
        int a, b, c;
        cin >> a >> b >> c;
        g[a].pb({b, c});
        g[b].pb({a, c});
    }
    cin >> s >> f;

    w[s] = 0;
    set< pair < ll, int> > q;
    q.insert({w[s], s});

    while(!q.empty()){
        int v = q.begin()->s;
        q.erase(q.begin());
        for(auto i = g[v].begin(); i != g[v].end(); i++){
            ll to = i->f, foo = i->s;
            if (w[to] > w[v] + foo){
                q.erase({w[to], to});
                w[to] = w[v] + foo;
                q.insert({w[to], to});
            }
        }
    }
    cout << w[f];
    
    return 0;
}