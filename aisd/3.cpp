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
    bool flag = true, mm;
    ll ans = 1;
    int n, k;
    cin >> n >> k;
    vector<ll> x;
    rep(i, 0, n){
        ll foo;
        cin >> foo;
        x.pb(foo);
    }
    sort(all(x));
    // rep(i,0,n){
    //     cout << x[i] << " ";
    // }
    int start = 0, finish = sz(x) - 1;
    if (k % 2){
        ans *= x[finish];
        ans %= mod;
        if (ans < 0) { 
            ans += mod; 
            flag = false; 
        }
        --finish;
    }
    k = k >> 1;
    while(k > 0){
        ll x1 = x[start] * x[start + 1];
        ll x2 = x[finish] * x[finish - 1];
        if (x1 > x2){
            mm = true;
        }
        else {
            mm = false;
        }
        x1 %= mod;
        x2 %= mod;
        if(x1 < 0){
            x1 += mod;
        }
        if(x2 < 0){
            x2 += mod;
        }
        //cout << max(x1, x2) << endl;
        if((flag + mm) % 2 == 0){
            ans *= x1;
            start += 2;
        }
        else {
            ans *= x2;
            finish -= 2;
        }
        ans %= mod;
        if(ans < 0){
            ans += mod;
        }
        k --;
    }
    cout << ans;
    return 0;
}