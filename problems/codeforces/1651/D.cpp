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

set<ii> p, seen;
map<ii, ll> c, im;
map<ll, set<ii>> b;

void dfs(ll x, ll y, ll ci) {
    seen.insert({x, y});
    c[{x, y}] = ci;
    for (auto [nx,ny] : adjc(x, y)) {
        if (p.count({nx, ny}) == 1) {
            if (seen.count({nx, ny}) == 0) {
                dfs(nx, ny, ci);
            }
        } else {
            b[ci].insert({nx, ny});
        }
    }
}

int main() {
    io();
    ll n;
    cin >> n;
    F0R(i, n) {
        ll x, y;
        cin >> x >> y;
        p.insert({x, y});
        im[{x, y}] = i;
    }
    ll ci = 0;
    for (auto [x, y] : p) {
        if (seen.count({x, y}) == 0) {
            dfs(x, y, ci++);
        }
    }
    vii res(n);
    F0R(cj, ci) {
        queue<array<ll, 4>> q; // x, y, ox, oy
        set<ii> qseen;
        for (auto [x, y] : b[cj]) {
            q.push({x, y, x, y});
            qseen.insert({x, y});
        }
        while (!q.empty()) {
            auto [x, y, ox, oy] = q.front();
            q.pop();
            for (auto [nx, ny] : adjc(x, y)) {
                if (p.count({nx, ny}) == 1 && qseen.count({nx, ny}) == 0 && c[{nx, ny}] == cj) {
                    qseen.insert({nx, ny});
                    q.push({nx, ny, ox, oy});
                    res[im[{nx, ny}]] = {ox, oy};
                }
            }
        }
    }
    for (auto [x, y] : res) {
        cout << x << ' ' << y << '\n';
    }
}