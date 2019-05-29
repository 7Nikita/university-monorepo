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
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    int field[101][101];
    rep(i, 0, 101) rep(j, 0, 101) field[i][j] = -2;
    int used[2][10000];
    rep(i, 0, 2) rep(j, 0, 10000) used[i][j] = 1;
    rep(i, 0, 101)
        rep(j, 0, 101)
            if ( i <= n && j <= m && (i != 0  && j != 0))
                field[i][j] = -1;
    field[1][1] = 0;
    int i = 0, j = 1;
    // int dz[] = {}
    // int dx[] = {};
    // int dy[] = {};
    while (field[x][y] == -1 && i != j) {
        int kek = (field[used[0][i]][used[1][i]]) + 1;

        if (used[0][i] - 2 > 0 && field[used[0][i] - 2][used[1][i] + 1] == -1) {
            field[used[0][i] - 2][used[1][i] + 1] = kek ;
            used[0][j] = used[0][i] - 2;
            used[1][j] = used[1][i] + 1;
            j++;
        }
        if ((used[0][i] - 2 > 0 && used[1][i] - 1 > 0) && (field[used[0][i] - 2][used[1][i] - 1] == -1)) {
            field[used[0][i] - 2][used[1][i] - 1] = kek;
            used[0][j] = used[0][i]-2;
            used[1][j] = used[1][i]+1;
            j++;
        }
        if (field[used[0][i] + 2][used[1][i] + 1] == -1) {
            field[used[0][i] + 2][used[1][i] + 1] = kek;
            used[0][j] = used[0][i]+2;
            used[1][j] = used[1][i]+1;
            j++;
        }
        if ( used[1][i] - 1 > 0 && field[used[0][i] + 2][used[1][i] - 1] == -1) {
            field[used[0][i] + 2][used[1][i] - 1] = kek;
            used[0][j] = used[0][i]+2;
            used[1][j] = used[1][i]-1;
            j++;
        }
        if (used[0][i] - 1 > 0  && field[used[0][i] - 1][used[1][i] + 2] == -1) {
            field[used[0][i] - 1][used[1][i] + 2] = kek;
            used[0][j] = used[0][i]-1;
            used[1][j] = used[1][i]+2;
            j++;
        }
        if ((used[0][i] - 1 > 0 && used[1][i] - 2 > 0) && field[used[0][i] - 1][used[1][i] - 2] == -1) {
            field[used[0][i] - 1][used[1][i] - 2] = kek;
            used[0][j] = used[0][i]-1;
            used[1][j] = used[1][i]-2;
            j++;
        }
        if (field[used[0][i] + 1][used[1][i] + 2] == -1) {
            field[used[0][i] + 1][used[1][i] + 2] = kek;
            used[0][j] = used[0][i]+1;
            used[1][j] = used[1][i]+2;
            j++;
        }
        if (used[1][i] - 2 > 0 && field[used[0][i] + 1][used[1][i] - 2] == -1) {
            field[used[0][i] + 1][used[1][i] - 2] = kek;
            used[0][j] = used[0][i]+1;
            used[1][j] = used[1][i]-2;
            j++;
        }
        i++;
    }
    
    if (field[x][y] == -1)
        return cout << "NEVAR", 0;

    cout << field[x][y];
    return 0;
}