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

vvi t;
vi c;
vector<tuple<ll, vi>> inp;
ll res = 1;

void dfs(ll tu, ll p) {
    auto &[s, U] = inp[tu];
    smax(res, s);
    vi to_color, used_colors;
    for (ll u : U) {
        if (c[u]) {
            used_colors.pb(c[u]);
        } else {
            to_color.pb(u);
        }
    }
    sort(all(used_colors));
    ll color = 1, used_idx = 0;
    for (ll u : to_color) {
        while (used_idx < used_colors.size() && used_colors[used_idx] == color) {
            ++color;
            ++used_idx;
        }
        c[u] = color++;
    }

    for (ll v : t[tu]) {
        if (v != p) {
            dfs(v, tu);
        }
    }

}

int main() {
    io();
    ll n, m;
    cin >> n >> m;
    c = vi(m+1);
    inp.assign(n+1, {});
    FOR(i, 1, n+1) {
        auto &[s, v] = inp[i];
        cin >> s;
        F0R(_, s) {
            ll u;
            cin >> u;
            v.pb(u);
        }
    }
    t = vvi(n+1);
    F0R(_, n-1) {
        ll u, v;
        cin >> u >> v;
        t[u].pb(v);
        t[v].pb(u);
    }
    dfs(1, -1);
    cout << res << '\n';
    FOR(i, 1, m+1) {
        cout << (c[i] ? c[i] : 1) << ' ';
    }
}