// https://codeforces.com/contest/1385/problem/E

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

// returns the lexicographically minimal topological ordering of the graphs vertices
// the second return value is if there is a cycle
pair<vi, bool> toposort(const vvi& graph) {
    int sz = graph.size();
    minq<int> pq;
    vi indeg(sz);
    F0R(i, sz) for (int j : graph[i]) ++indeg[j];
    F0R(i, sz) if (indeg[i] == 0) pq.push(i);
    vi out;
    while (!pq.empty()) {
        int u = pq.top(); pq.pop();
        out.pb(u);
        for (int v : graph[u]) if (--indeg[v] == 0) pq.push(v);
    }
    return {out, out.size() != sz};
}

int main() {
    io();
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        int n, m;
        cin >> n >> m;
        g = vvi(n+1);
        vii ud;
        F0R(_, m) {
            int ti, xi, yi;
            cin >> ti >> xi >> yi;
            if (ti) {
                g[xi].pb(yi);
            } else {
                ud.pb({xi, yi});
            }
        }
        auto [topo, cyc] = toposort(g);
        if (cyc) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        vi inv(n+1);
        F0R(i, n+1) inv[topo[i]] = i;
        for (auto [u, v] : ud) {
            if (inv[u] < inv[v]) {
                cout << u << ' ' << v << '\n';
            } else {
                cout << v << ' ' << u << '\n';
            }
        }
        F0R(u, n+1) {
            for (int v : g[u]) {
                cout << u << ' ' << v << '\n';
            }
        }
    }
}