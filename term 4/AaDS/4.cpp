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
const int mod = 1e9 + 7;
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

int main(){
    files;
    
    int n, m, pos_x, pos_y;
    cin >> n >> m >> pos_x >> pos_y;
    
    int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    pii cur_pos = {0, 0};
    bool used[101][101];
    int field[101][101];
    
    rep(i, 0, 101){
        memset(used[i], 0, sizeof(used[i]));
        memset(field[i], 0, sizeof(field[i]));
    }

    queue < pii > q;
    used[cur_pos.f][cur_pos.s] = true;
    field[cur_pos.f][cur_pos.s] = 0;
    q.push(cur_pos);

    while(!q.empty()){
        pii tmp = q.front();
        //cout << tmp.f << " " << tmp.s << endl;
        q.pop();
        rep(i, 0, 8){
            if (tmp.f + dx[i] >= 0 && 
                tmp.f + dx[i] < n &&
                tmp.s + dy[i] >= 0 && 
                tmp.s < m){
                if(!used[tmp.f + dx[i]][tmp.s + dy[i]]){
                    used[tmp.f + dx[i]][tmp.s + dy[i]] = true;
                    q.push({tmp.f + dx[i], tmp.s + dy[i]});
                    field[tmp.f + dx[i]][tmp.s + dy[i]] = field[tmp.f][tmp.s] + 1;
                }
            }
        }
    }
     
    if (used[pos_x - 1][pos_y - 1]) 
        return cout << field[pos_x - 1][pos_y - 1], 0;
    cout << "NEVAR";

    return 0;
}