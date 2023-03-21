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

ii read_edge(vector<set<ll>> &graph, bool directed=false) {
    int a, b;
    cin >> a >> b;
    graph[a].insert(b);
    if (!directed) graph[b].insert(a);
    return {a, b};
}

vector<set<ll>> read_graph(int V, int E, bool directed=false) {
    vector<set<ll>> g(V);
    F0R(i, E) read_edge(g, directed);
    return g;
}

vector<set<ll>> g;
set<ll> remaining;

void dfs(ll u) {
    remaining.erase(u);
    ll v = -1;
    while (true) {
        auto vit = remaining.upper_bound(v);
        if (vit == remaining.end()) {
            break;
        }
        v = *vit;
        if (g[u].count(v) == 0) {
            dfs(v);
        }
    }
}

int main() {
    io();
    ll n, m;
    cin >> n >> m;
    ll V = n+1;
    g = read_graph(V, m);
    FOR(i, 1, V) {
        remaining.insert(i);
    }
    ll ccnt = 0;
    FOR(u, 1, V) {
        if (remaining.count(u) == 1) {
            ++ccnt;
            dfs(u);
        }
    }
    cout << ccnt -1 << '\n';
}