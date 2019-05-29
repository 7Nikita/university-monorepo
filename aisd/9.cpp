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
#define fast_io ios_base::sync_with_stdio(0);
#define files1 freopen("input.txt", "r", stdin)
#define files2 freopen("output.txt", "w", stdout)

const int inf = 2e9;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 500;
const long long llinf = 2e18 + 5;

using namespace std;

char change(char x){
    return x < 97 ? 97 + (int)x - 'A' : 65 + (int)x - 'a';
} 

int main(){
    files;
    
    string s;
    cin >> s;
    int flag[sz(s)];
    memset(flag, 0, sizeof(flag));
    
    int n;
    cin >> n;
    while(n--){
        int l, r;
        cin >> l >> r;
        if (l > r) 
            swap(l, r);
        ++flag[l - 1];
        ++flag[r];
    }

    int cnt = 0;

    for (int i = 0; i < sz(s); i++){
        cnt += flag[i];
        cout << (cnt % 2 ? change(s[i]) : s[i]);
    }
    return 0;
}