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

using edgew = ll;
using graph_t = vv<pair<int, edgew>>;

map<ii, ll> em;
ll edge_cnt = 0;
tuple<int, int, edgew> read_edge(graph_t &wg, bool directed = false, bool unit_weight = false) {
    int a, b;
    cin >> a >> b;
    em[{min(a, b), max(a, b)}] = ++edge_cnt;
    edgew w;
    if (unit_weight) w = 1;
    else cin >> w;
    wg[a].pb({b, w});
    if (!directed) wg[b].pb({a, w});
    return {a, b, w};
}

graph_t read_graph(int V, int m, bool directed = false, bool unit_weight = false) {
    graph_t wg = graph_t(V);
    F0R(i, m) read_edge(wg, directed, unit_weight);
    return wg;
}

pair<vvi, vector<edgew>> shortest_path_dag(const graph_t & graph, int start) {
    vvi spdag(graph.size());
    vector<edgew> dists(graph.size(), numeric_limits<edgew>::max());
    minq<tuple<edgew, int, int>> pq; // dist, node, prev
    pq.push({edgew{}, start, -1});
    vi seen(graph.size());
    while (!pq.empty()) {
        auto [d, u, p] = pq.top(); pq.pop();
        if (d <= dists[u] && p != -1) spdag[p].pb(u);
        if (seen[u]) continue;
        seen[u] = true;
        dists[u] = d;
        for (auto [v, w] : graph[u]) {
            if (!seen[v]) pq.push({d + w, v, u});
        }
    }
    return {spdag, dists};
}


int main() {
    io();
    ll n, m;
    cin >> n >> m;
    auto g = read_graph(n+1, m);
    ll U;
    cin >> U;
    auto [spdag, dists] = shortest_path_dag(g, U);
    vv<ii> gt(n+1);
    FOR(u, 1, n+1) {
        for (ll v : spdag[u]) {
            gt[v].pb({dists[v] - dists[u], u});
        }
    }
    ll cost = 0;
    vi edges;
    FOR(u, 1, n+1) {
        if (u == U) continue;
        auto [w, v] = *min_element(all(gt[u]));
        cost += w;
        edges.pb(em[{min(u, v), max(u, v)}]);
    }
    cout << cost << '\n';
    for (ll i : edges) {
        cout << i << ' ';
    }
    cout << '\n';
}