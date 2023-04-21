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
    int size(int x) {
        return sz[rep(x)];
    }
};
ll n, m;
vi path, x, seen;
vvi g;

bool dfs(ll u) {
    seen[u] = true;
    path.pb(u);
    ll cnt = 1;
    for (ll v: g[u]) {
        if (seen[v]) continue;
        if (dfs(v)) {
           path.pb(u);
           cnt++;
           path.pb(v);
        }
        path.pb(u);
        cnt++;
    }
    return (cnt % 2) != x[u];
}

int main() {
    io();
    cin >> n >> m;
    g = vvi(n+1);
    F0R(i, m) {
        ll u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    seen = x = vi(n+1);
    ll root = -1;
    FOR(i, 1, n+1) {
        cin >> x[i];
        if (x[i]) {
            root = i;
        }
    }
    if (root == -1) {
        cout << "0\n";
        return 0;
    }
    if (dfs(root)) {
        path.pop_back();
    }
    FOR(u, 1, n+1) {
        if (x[u] && !seen[u]) {
            cout << "-1\n";
            return 0;
        }
    }
    cout << path.size() << '\n';
    for (ll u: path) {
        cout << u << ' ';
    }
    cout << '\n';
}