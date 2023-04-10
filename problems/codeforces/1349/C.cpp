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

vvi g;

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
    return {idx / R, idx % R};
}

int main() {
    io();
    ll t;
    cin >> R >> C >> t;
    g.assign(R, vi(C));
    F0R(r, R) {
        F0R(c, C) {
            char x;
            cin >> x;
            g[r][c] = x - '0';
        }
    }
    deque<array<ll, 3>> q; // l, r, c
    F0R(r, R) {
        F0R(c, C) {
            for (auto [nr, nc] : adjc(r, c)) {
                if (g[r][c] == g[nr][nc]) {
                    q.push_front({0, r, c});
                }
            }
        }
    }
    vvi seen(R, vi(C, -1));
    while (!q.empty()) {
        auto [l, r, c] = q.front();
        q.pop_front();
        if (seen[r][c] != -1) continue;
        seen[r][c] = l;
        for (auto [nr, nc]: adjc(r, c)) {
            if (seen[nr][nc] != -1) continue;
            if (g[r][c] == g[nr][nc]) {
                q.push_front({l, nr, nc});
            } else {
                q.push_back({l+1, nr, nc});
            }
        }
    }
    F0R(_, t) {
        ll r, c, p;
        cin >> r >> c >> p;
        r--;
        c--;
        if (seen[r][c] == -1) {
            cout << g[r][c] << '\n';
        } else {
            cout << (g[r][c] ^ (max(0ll, p - seen[r][c]) % 2)) << '\n';
        }
    }
}