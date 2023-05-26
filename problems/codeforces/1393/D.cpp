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

vector<string> g;

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
        res.pb({nr, nc});
    }
    return res;
}

int enc(int r, int c) {
    return r * C + c;
}

ii dec(int idx) {
    return {idx / R, idx % R};
}

vvi d;


void set_dists(const vii & starts, char color) {
    deque<array<ll, 3>> q; // r, c, l
    for (auto [r, c]: starts) {
        q.push_back({r, c, 1});
        d[r][c] = 1;
    }
    while (!q.empty()) {
        auto [r, c, l] = q.front();
        q.pop_front();
        for (auto [dr, dc] : dirs) {
            ll nr = r+dr, nc = c+dc;
            if (inbounds(nr, nc) && g[nr][nc] == color && d[nr][nc] == 0) {
                d[nr][nc] = l+1;
                q.push_back({nr, nc, l+1});
            }
        }
    }
}

int main() {
    io();
    cin >> R >> C;
    g.assign(R, "");
    F0R(r, R) cin >> g[r];
    d = vvi(R, vi(C));
    vv<ii> edges(26);
    F0R(r, R) {
        F0R(c, C) {
            for (auto [dr, dc]: dirs) {
                if (!inbounds(r+dr, c+dc) || g[r+dr][c+dc] != g[r][c]) {
                    edges[g[r][c]-'a'].pb({r, c});
                }
            }
        }
    }
    F0R(i, 26) {
        set_dists(edges[i], 'a' + i);
    }
    ll res = 0;
    F0R(r, R) F0R(c, C) res += d[r][c];
    cout << res << '\n';
}