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

vector<int> x;
vector<int>tmp;


ll msort(int l, int m, int r){
    int k = l;
    int i = l;
    int j = m + 1;

    ll ans = 0;

    while(i <= m && j <= r){
        if (x[i] <= x[j])
            tmp[k++] = x[i++];
        else{
            tmp[k++] = x[j++];
            ans += m - i + 1;
        }
    }

    while(i <= m)
        tmp[k++] = x[i++];

    for (int i = l; i <= r; i++)
        x[i] = tmp[i];

    return ans;
}

ll solve(int l, int r) {

    if (l == r)
        return 0;

    int m = (r - l) / 2 + l;
    ll ans = 0;

    ans += solve(l, m);
    ans += solve(m + 1, r);
    ans += msort(l, m, r);

    return ans;
} 

int main(){
    files;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        int foo;
        cin >> foo;
        x.pb(foo);
        tmp.pb(foo);
    }
    cout << solve(0, sz(x) - 1);
    return 0;
}