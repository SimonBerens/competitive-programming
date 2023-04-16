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

ii read_edge(vvi &graph, bool directed=false) {
    int a, b;
    cin >> a >> b;
    graph[a].pb(b);
    if (!directed) graph[b].pb(a);
    return {a, b};
}

vvi read_graph(int V, int E, bool directed=false) {
    vvi g(V);
    F0R(i, E) read_edge(g, directed);
    return g;
}

ll n;
vvi g;

vi find_cycle() {
    queue<ll> q;
    vi deg(n + 1), sz(n+1, 1), seen(n+1);
    FOR(u, 1, n+1) {
        ll i = g[u].size();
        deg[u] = i;
        if (i == 1) {
            q.push(u);
        }
    }
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        seen[u] = true;
        for (ll v: g[u]) {
            if (seen[v]) continue;
            if (--deg[v] <= 1) {
                q.push(v);
            }
            sz[v] += sz[u];
        }
    }
    vi res;
    FOR(u, 1, n+1) {
        if (deg[u] == 2) {
            res.pb(sz[u]);
        }
    }
    return res;
}

int main() {
    io();
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        cin >> n;
        g = read_graph(n+1, n);
        auto sizes = find_cycle();
        ll res = 0;
        for (ll s : sizes) {
            res += c2(s) + (n - s) * s;
        }
        cout << res << '\n';
    }
}