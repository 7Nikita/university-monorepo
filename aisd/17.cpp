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

int main(){
    files;
    vector <int> d = {1021, 1031, 1033, 1052651, 1054693, 1065023, 1087388483};
    vector <bool> flag(8);
    int n;
    cin >> n;
    while(n--){
        int foo;
        cin >> foo;
        for (int i = 0; i < 7; i++){
            if (foo == d[i]){
                flag[i] = true;
                break;
            }
        }
    }
    if (flag[0] && flag[1] && flag[2])
        cout << "YES";
    else if (flag[0] && flag[5])
        cout << "YES";
    else if (flag[1] && flag[4])
        cout << "YES";
    else if (flag[2] && flag[3])
        cout << "YES";
    else if (flag[6])
        cout << "YES";
    else 
        cout << "NO";

    return 0;
}