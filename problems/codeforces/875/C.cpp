#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
template<typename K> using hset = gp_hash_table<K, null_type>;
template<typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back

template<typename T>
void smin(T &x, T y) {
    x = min(x, y);
}

template<typename T>
void smax(T &x, T y) {
    x = max(x, y);
}

template<typename T>
T c2(T x) {
    return x * (x - 1) / 2;
}

template<typename T>
T sq(T x) {
    return x * x;
}

template<typename T>
T ceildiv(T p, T q) {
    return (p + q - 1) / q;
}

#define FOR(i, a, b) for (ll i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i,0,a)
#define ROF(i, a, b) for (ll i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i,0,a)

using ll = int;
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

struct scc {

    vvi adj, r_adj;
    vi c, v, ord;

    scc(vvi _adj) : adj(_adj) {}

    void dfs(ll i) {
        v[i] = 1;
        for (ll j: adj[i])
            if (!v[j]) dfs(j);
        ord.push_back(i);
    }

    void partition(ll i, ll t) {
        v[i] = 1, c[i] = t;
        for (ll j: r_adj[i])
            if (!v[j]) partition(j, t);
    }

    // returns a component vector c s.t. c[i] == c[j] iff i and j
    // are in the same strongly connected component, runs in O(E).
    vi components() {
        ll n = adj.size(), t = 0;
        v.assign(n, 0), r_adj.resize(n);
        F0R(i, n) {
            for (ll j: adj[i]) r_adj[j].push_back(i);
            if (!v[i]) dfs(i);
        }
        v.assign(n, 0), c.assign(n, 0);
        R0F(i, n)if (!v[ord[i]]) partition(ord[i], t++);
        return c;
    }
};

struct twosat {
    vvi g;
    ll n;

    explicit twosat(ll n) : g(2 * n), n(n) {}

    struct term {
        ll var;
        bool negate = false;
    };

    void add_or(const term &a, const term &b) {
        add_impl({a.var, !a.negate}, b);
    }

    void set(const term&a) {
        add_single_impl({a.var, !a.negate}, a);
    }

    void add_impl(const term &a, const term &b) {
        add_single_impl(a, b);
        add_single_impl({b.var, !b.negate}, {a.var, !a.negate});
    }

    pair<bool, vi> solve() {
        scc SCC(g);
        SCC.components();
        vi ord_inv(2*n);
        F0R(i, 2*n) ord_inv[SCC.ord[i]] = i;
        vi res(n);
        F0R(i, n) {
            if (SCC.c[i] == SCC.c[i+n]) return {false, {}};
            res[i] = ord_inv[i] < ord_inv[i+n];
        }
        return {true, res};
    }

private:
    void add_single_impl(const term &a, const term &b) {
        g[a.var + n * a.negate].pb(b.var + n * b.negate);
    }
};

int main() {
    io();
    ll n, m;
    cin >> n >> m;
    vvi s(n);
    F0R(i, n) {
        ll l;
        cin >> l;
        s[i] = vi(l);
        F0R(j, l) cin >> s[i][j];
    }
    twosat SAT(m+1);
    F0R(i, n - 1) {
        bool prefix = true;
        ll s0 = s[i].size(), s1 = s[i+1].size();
        F0R(j, min(s0, s1)) {
            ll d = s[i][j] - s[i+1][j];
            if (d == 0) continue;
            else if (d > 0) {
                SAT.set({s[i][j]});
                SAT.set({s[i+1][j], true});
            } else {
                SAT.add_impl({s[i+1][j]}, {s[i][j]});
            }
            prefix = false;
            break;
        }
        if (prefix && s0 > s1) {
            cout << "No\n";
            return 0;
        }
    }
    auto [poss, ans] = SAT.solve();
    if (poss) {
        cout << "Yes\n";
        vi vars;
        FOR(i, 1, m+1) if (ans[i]) vars.pb(i);
        cout << vars.size() << '\n';
        for (ll i : vars) cout << i << ' ';
        cout << '\n';
    } else {
        cout << "No\n";
    }
}