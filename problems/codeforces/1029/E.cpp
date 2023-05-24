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

void root(int u, int p, vvi & tree, vi& par, const vvi & graph) {
    tree[p].pb(u);
    par[u] = p;
    for (int v : graph[u]) if (v != p) root(v, u, tree, par, graph);
}

pair<vvi, vi> read_tree(int V, int offset=1, int root_u=1) {
    auto graph = read_graph(V+offset, V-1);
    vi par(V+offset);
    vvi tree(V+offset);
    for (int u : graph[root_u]) root(u, root_u, tree, par, graph);
    return {tree, par};
}

vvi t;
vi p, dist;

void dfs(ll u, ll p, ll d) {
    dist[u] = d;
    for (ll v : t[u]) {
        if (v != p) {
            dfs(v, u, d+1);
        }
    }
}

int main() {
    io();
    ll n;
    cin >> n;
    tie(t, p) = read_tree(n);
    dist = vi(n+1);
    dfs(1, 0, 0);
    set<ii, greater<>> s;
    FOR(i, 1, n+1) {
        if (dist[i] > 2) {
            s.insert({dist[i], i});
        }
    }
    ll res = 0;
    while (!s.empty()) {
        auto [_, u] = *s.begin();
        u = p[u];
        s.erase({dist[u], u});
        s.erase({dist[p[u]], p[u]});
        for (ll v: t[u]) {
            s.erase({dist[v], v});
        }
        res++;
    }
    cout << res << '\n';
}