// https://codeforces.com/contest/1336/problem/A

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

ii read_edge(vvi &graph, bool directed = false) {
    int a, b;
    cin >> a >> b;
    graph[a].pb(b);
    if (!directed) graph[b].pb(a);
    return {a, b};
}

vvi read_graph(int V, int E, bool directed = false) {
    vvi g(V);
    F0R(i, E) read_edge(g, directed);
    return g;
}

void root(int u, int p, vvi &tree, vi &par, const vvi &graph) {
    tree[p].pb(u);
    par[u] = p;
    for (int v: graph[u]) if (v != p) root(v, u, tree, par, graph);
}

pair<vvi, vi> read_tree(int V, int offset = 1, int root_u = 1) {
    auto graph = read_graph(V + offset, V - 1);
    vi par(V + offset);
    vvi tree(V + offset);
    for (int u: graph[root_u]) root(u, root_u, tree, par, graph);
    return {tree, par};
}

vi d, p, sz, delta;
vvi t;

void cd(int u, int dis) {
    d[u] = dis;
    for (int v: t[u]) {
        cd(v, dis + 1);
    }
}

int csz(int u) {
    int res = 1;
    for (int v: t[u]) {
        res += csz(v);
    }
    return sz[u] = res;
}

int main() {
    io();
    int n, k;
    cin >> n >> k;
    auto [_t, _p] = read_tree(n);
    t = _t;
    p = _p;
    d.assign(n+1, 0);
    sz.assign(n+1, 0);
    delta.assign(n+1, 0);
    cd(1, 0);
    csz(1);
    F0R(i, n+1) {
        delta[i] = sz[i] - 1 - d[i];
    }
    sort(delta.begin()+1, delta.end());
    ll res = 0;
    ROF(i, k+1, n+1) {
        res += delta[i];
    }
    cout << res << '\n';
}