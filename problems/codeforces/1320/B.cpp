// https://codeforces.com/contest/1320/problem/B

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

using edgew = ll;
using graph_t = vv<pair<int, edgew>>;

tuple<int, int, edgew> read_edge(graph_t &wg, bool directed = false, bool unit_weight = false) {
    int a, b;
    cin >> a >> b;
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

pair<vvi, vector<edgew>> shortest_path_dag(const graph_t &graph, int start) {
    vvi spdag(graph.size());
    vector<edgew> dists(graph.size(), numeric_limits<edgew>::max());
    minq<tuple<edgew, int, int>> pq; // dist, node, prev
    pq.push({edgew{}, start, -1});
    vi seen(graph.size());
    while (!pq.empty()) {
        auto [d, u, p] = pq.top();
        pq.pop();
        if (d <= dists[u] && p != -1) spdag[p].pb(u);
        if (seen[u]) continue;
        seen[u] = true;
        dists[u] = d;
        for (auto [v, w]: graph[u]) {
            if (!seen[v]) pq.push({d + w, v, u});
        }
    }
    return {spdag, dists};
}

int main() {
    io();
    int n, m;
    cin >> n >> m;
    auto g = read_graph(++n, m, true, true);
    graph_t tg(n);
    F0R(u, n) {
        for (auto [v, w]: g[u]) {
            tg[v].pb({u, w});
        }
    }
    int k;
    cin >> k;
    vi p(k);
    F0R(i, k) cin >> p[i];
    auto [dag, dist] = shortest_path_dag(tg, p.back());
    vi indeg(n);
    F0R(u, n) {
        for (int v: dag[u]) {
            indeg[v]++;
        }
    }
    vi maxdp(k), mindp(k);
    R0F(i, k - 1) {
        bool disconnected = find(all(dag[p[i + 1]]), p[i]) == dag[p[i + 1]].end();
        maxdp[i] = maxdp[i + 1] + (disconnected ? 1 : (indeg[p[i]] > 1));
        mindp[i] = mindp[i+1] + disconnected;
    }
    cout << mindp[0] << ' ' << maxdp[0] << '\n';
}