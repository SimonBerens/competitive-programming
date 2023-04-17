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

template<typename T> T c2(T x) {
    return x * (x - 1) / 2;
}

template<typename T> T sq(T x) {
    return x * x;
}

#define FOR(i, a, b) for (ll i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i,0,a)
#define ROF(i, a, b) for (ll i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i,0,a)

using ll = long long;
using ld = long double;

template<typename T>
using vv = vector<vector<T>>;

using vi = vector<ll>;
using ii = array<ll, 2>;
using vii = vector<ii>;
using vvi = vv<ll>;

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


bool hamiltonian_path(const vvi& g, ll S, ll T) {
    // dp[nodes][u] = dp[nodes\u][v] & E(u, v)
    // O(2^n) * n

}

int main() {
    io();
    ll n, m;
    cin >> n >> m;
    vvi g(n, vi(m));
    F0R(i, n) {
        F0R(j, m) {
            cin >> g[i][j];
        }
    }
    vvi c(n, vi(n, M));
    auto tc = c;
    F0R(r1, n) {
        F0R(r2, n) {
            F0R(i, m) {
                smin(c[r1][r2], abs(g[r1][i] - g[r2][i]));
                if (i < m-1) smin(tc[r1][r2], abs(g[r2][i] - g[r1][i+1]));
            }
        }
    }
    ll res = 0;
    ll B = 1 << n;
    F0R(start, n) {
        vvi dp(B, vi(n));
        dp[1<<start][start] = M;
        F0R(s, B) {
            if (!(s&(1<<start))) continue;
            F0R(u, n) {
                if (!(s & (1<<u))) continue;
                F0R(v, n) {
                    ll ns = s^(1<<v);
                    if (ns<s) continue;
                    smax(dp[ns][v], min(dp[s][u], c[u][v]));
                }
            }
        }
        F0R(i, n) {
            smax(res, min(dp.back()[i], tc[start][i]));
        }
    }
    cout << res << '\n';
}