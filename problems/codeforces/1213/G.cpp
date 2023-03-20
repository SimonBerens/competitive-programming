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

template<typename T>
vi sort_indices(const vector<T> &v) {
    int s = v.size();
    vi idxs(s);
    iota(all(idxs), 0);
    sort(all(idxs), [&](int i, int j) -> bool { return v[i] < v[j]; });
    return idxs;
}

template<typename T>
vi sort_indices(const vector<T> &v, function<bool(const T &, const T &)> comp) {
    int s = v.size();
    vi idxs(s);
    iota(all(idxs), 0);
    sort(all(idxs), [&](int i, int j) -> bool { return comp(v[i], v[j]); });
    return idxs;
}

struct dsu {

    vector<ll> p, sz;
    ll ans;

    explicit dsu(int n) : p(n), sz(n, 1), ans(0) {
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
            ans += c2(sz[a] + sz[b]) - c2(sz[a]) - c2(sz[b]);
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


int main() {
    io();
    int n, m;
    cin >> n >> m;
    vector<array<int, 3>> edges(n-1);
    F0R(i, n-1) {
        auto &[w, u, v] = edges[i];
        cin >> u >> v >> w;
    }
    sort(all(edges));
    vi q(m);
    F0R(i, m) {
        cin >> q[i];
    }
    auto idxs = sort_indices(q);
    vll res(m);
    dsu D(n+1);
    int edge_i = 0;
    F0R(z, m) {
        int i = idxs[z];
        while (edge_i < n-1 && q[i] >= edges[edge_i][0]) {
            D.unite(edges[edge_i][1], edges[edge_i][2]);
            edge_i++;
        }
        res[i] = D.ans;
    }
    F0R(i, m) {
        cout << res[i] << ' ';
    }
    cout << '\n';
}