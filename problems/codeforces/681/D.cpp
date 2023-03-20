// https://codeforces.com/contest/681/problem/D

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

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i,0,a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i,0,a)

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
    int n, m;
    cin >> n >> m;
    vvi t(n+1);
    vi P(n+1);
    F0R(i, m) {
        int p, q;
        cin >> p >> q;
        t[p].pb(q);
        P[q] = p;
    }
    vi a(n+1);
    FOR(i,1, n+1) cin >> a[i];
    FOR(i, 1, n+1){
        if (!(a[i] == i || a[i] == a[P[i]])) {
            cout << "-1\n";
            return 0;
        }
    }
    auto [topo, cyc] = toposort(t);
    assert(!cyc);
    vi X;
    FOR(i, 1, n+1) {
        int j = topo[i];
        if (a[j] == j) X.pb(j);
    }
    cout << X.size() << '\n';
    reverse(all(X));
    for (int x : X) cout << x << '\n';
}