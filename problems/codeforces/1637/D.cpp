#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
template<typename K> using hset = gp_hash_table<K, null_type>;
template<typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back

template<typename T> void smin(T &x, T y) {
    x = min(x, y);
}

template<typename T> void smax(T &x, T y) {
    x = max(x, y);
}

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i,0,a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i,0,a)

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

int MS = 10001;

int main() {
    io();
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        int n;
        cin >> n;
        vi a(n), b(n);
        F0R(i, n) {
            cin >> a[i];
        }
        F0R(i, n) {
            cin >> b[i];
        }
        int tsum = 0;
        ll fixed = 0;
        F0R(i, n) {
            tsum += a[i] + b[i];
            fixed += a[i] * a[i] + b[i] * b[i];
        }
        fixed *= n - 2;
        // dp[i][S] = dp[i-1][S-a[i]] || dp[i-1][S-b[i]]
        vvi dp(n+1, vi(MS));
        dp[0][0] = 1;
        F0R(i, n) {
            F0R(S, MS) {
                if (S >= a[i]) dp[i+1][S] |= dp[i][S-a[i]];
                if (S >= b[i]) dp[i+1][S] |= dp[i][S-b[i]];
            }
        }
        ll res = infll;
        F0R(s, MS) {
            ll S = s;
            if (dp.back()[S]) {
                smin(res, S * S + (tsum - S) * (tsum - S) + fixed);
            }
        }
        cout << res << '\n';
    }
}