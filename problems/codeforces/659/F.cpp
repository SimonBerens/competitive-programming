// https://codeforces.com/contest/659/problem/F

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

vvi g;

int R, C;

vii dirs{{1,  0},
         {-1, 0},
         {0,  1},
         {0,  -1}};
vii dirs8{{-1, 0},
          {-1, 1},
          {0,  1},
          {1,  1},
          {1,  0},
          {1,  -1},
          {0,  -1},
          {-1, -1}};

bool inbounds(int r, int c) {
    return 0 <= r && r < R && 0 <= c && c < C;
}

vii adjc(int r, int c, const vii &ds = dirs) {
    vii res;
    for (auto [dr, dc]: ds) {
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

struct dsu {

    vector<int> p, sz;

    explicit dsu(int n) : p(n), sz(n, 1) {
        iota(p.begin(), p.end(), 0);
    }

    int rep(int x) {
        while (x != p[x]) x = p[x] = p[p[x]];
        return x;
    }

    // returns true if a and b are in the same set, and then unites them.
    bool unite(int a, int b) {
        a = rep(a), b = rep(b);
        if (sz[a] < sz[b]) swap(a, b);
        if (a != b) {
            p[b] = a;
            sz[a] += sz[b];
        }
        return a == b;
    }

    // returns true if a and b are in the same set.
    bool query(int a, int b) {
        return rep(a) == rep(b);
    }

    // returns the size of the set containing x
    ll size(int x) {
        return sz[rep(x)];
    }
};

vvi seen;

int dfs(int r, int c, int v, int cnt) {
    if (cnt == 0) return 0;
    seen[r][c] = 1;
    int res = 1;
    for (auto [nr, nc] : adjc(r, c)) {
        if (!seen[nr][nc] && g[nr][nc] >= v) res += dfs(nr, nc, v, cnt - res);
    }
    return res;
}


int main() {
    io();
    ll k;
    cin >> R >> C >> k;
    seen = g = vvi(R, vi(C));
    maxq<array<int, 3>> pq;
    F0R(r, R) {
        F0R(c, C) {
            cin >> g[r][c];
            pq.push({g[r][c], r, c});
        }
    }
    dsu D(R * C);
    while (!pq.empty()) {
        auto [v,r,c] = pq.top();
        pq.pop();
        for (auto [nr, nc]: adjc(r, c)) {
            if (v <= g[nr][nc]) D.unite(enc(r, c), enc(nr, nc));
        }
        if (k % v == 0 && D.size(enc(r, c)) >= k / v) {
            dfs(r, c, v, k / v);
            cout << "YES\n";
            F0R(i, R) {
                F0R(j, C) {
                    cout << seen[i][j] * v << ' ';
                }
                cout << '\n';
            }
            return 0;
        }
    }
    cout << "NO\n";
}