// https://codeforces.com/contest/1204/problem/C

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
template<typename K> using hset = gp_hash_table<K, null_type>;
template<typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back
#define smax(x, y) (x = max(x, y))
#define smin(x, y) (x = min(x, y))

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i,0,a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i,0,a)

template<typename T, unsigned long N>
istream &operator>>(istream &in, array<T, N> &arr) {
    F0R(i, N) in >> arr[i];
    return in;
}

using ll = long long;
using ld = long double;

template<typename T>
using vv = vector<vector<T>>;

using vi = vector<int>;
using ii = array<int, 2>;
using vii = vector<ii>;
using vvi = vv<int>;

using vll = vector<ll>;
using l2 = array<ll, 2>;
using vl2 = vector<l2>;
using vvll = vv<ll>;

template<typename T>
using minq = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using maxq = priority_queue<T>;

template<typename T>
using oset = tree<T, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

const ll M = 1000000007;
const ll infll = M * M;

void io() {
    ios::sync_with_stdio(0);
    cin.tie(0);
}

void io(string name) {
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
    io();
}

int main() {
    io();
    int n;
    cin >> n;
    vvi g(n, vi(n));
    F0R(r, n) {
        F0R(c, n) {
            char x;
            cin >> x;
            g[r][c] = x - '0';
        }
    }
    vvi d =g;
    F0R(r, n) {
        F0R(c, n) {
            if (r != c && d[r][c] == 0) d[r][c] = M;
        }
    }
    F0R(k, n) {
        F0R(i, n) {
            F0R(j, n) {
                smin(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    int m;
    cin >> m;
    vi p(m);
    F0R(i, m) cin >> p[i];
    vi dp(m, M), r(m);
    dp[0] = 1;
    r[0] = -1;
    FOR(i, 1, m) {
        R0F(j, i) {
            if (d[p[j]-1][p[i]-1] != i - j) break;
            if (dp[i] > dp[j] + 1) {
                dp[i] = dp[j] + 1;
                r[i] = j;
            }
        }
    }
    cout << dp.back() << '\n';
    vi ans;
    for (int i = m - 1; i != -1; i = r[i]) {
        ans.pb(p[i]);
    }
    reverse(all(ans));
    for (int x: ans) {
        cout << x << ' ';
    }

}