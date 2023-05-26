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

template<typename T> T ceildiv(T p, T q) {
    return (p + q - 1) / q;
}

#define FOR(i, a, b) for (ll i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i,0,a)
#define ROF(i, a, b) for (ll i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i,0,a)

using ll = int;
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

int R, C;

vii dirs{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
vii dirs8{{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

bool inbounds(int r, int c) {
    return 0 <= r && r < R && 0 <= c && c < C;
}

vii adjc(int r, int c, const vii &ds = dirs) {
    vii res;
    for (auto[dr, dc]: ds) {
        int nr = r + dr, nc = c + dc;
        if (inbounds(nr, nc)) res.pb({nr, nc});
    }
    return res;
}

int enc(int r, int c) {
    return r * C + c;
}

ii dec(int idx) {
    return {idx / C, idx % C};
}

ll dfs(ll u, ll c,  const vvi & g, vi & seen) {
    ll res = 0;
    while (seen[u] == -1) {
        seen[u] = c;
        ++res;
        u = g[u][0];
    }
    seen[u] = c;
    return res;
}


int main() {
    io();
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        cin >> R >> C;
        vector<string> grid(R);
        F0R(r, R) cin >> grid[r];
        vvi g(R*C);
        F0R(r, R) {
            F0R(c, C) {
                char cr = grid[r][c];
                if (cr == 'L' && c>0) {
                    g[enc(r, c)].pb(enc(r, c-1));
                } else if (cr == 'R' && c < C-1) {
                    g[enc(r, c)].pb(enc(r, c+1));
                } else if (cr == 'D' && r < R-1) {
                    g[enc(r, c)].pb(enc(r+1, c));
                } else if (cr == 'U' && r > 0) {
                    g[enc(r, c)].pb(enc(r-1, c));
                }
            }
        }
        // find nodes of indegree 0
        vi indeg(R*C);
        vi starts;
        F0R(i, R*C) for (ll v : g[i]) indeg[v]++;
        F0R(i, R*C) if (indeg[i] == 0) starts.pb(i);
        // toposort until only cycles are left
        vi topo;
        queue<ll> q;
        for (ll u: starts) q.push(u);
        while (!q.empty()) {
            ll u = q.front();
            q.pop();
            topo.pb(u);
            for (ll v: g[u]) {
                if (--indeg[v] == 0) q.push(v);
            }
        }
        // calculate size of each cycle
        vi sz, seen(R*C, -1);
        F0R(i, R*C) {
            if (indeg[i] && seen[i] == -1) {
                sz.pb(dfs(i, sz.size(), g, seen));
            }
        }
        // do dp on non-cycles
        vi dp(R*C);
        F0R(i, R*C) dp[i] = seen[i] >= 0 ? sz[seen[i]] : 1;
        R0F(i, topo.size()) {
            for (ll u : g[topo[i]]) dp[topo[i]] = dp[u] + 1;
        }
        auto it = max_element(all(dp));
        ll l = *it;
        auto [r, c] = dec(it - dp.begin());
        cout << r+1 << ' ' << c+1 << ' ' << l << '\n';
    }
}