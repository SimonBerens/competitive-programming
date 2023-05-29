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


template <typename T>
struct segtree {
    constexpr static T max_T = numeric_limits<T>::max();
    constexpr static T min_T = numeric_limits<T>::min();

    int n;

    struct node {
        T s=0, _min=max_T, _max=min_T;
    };

    vector<node> t;

    node apply(const node & l, const node & r) {
        return {l.s+r.s, std::min(l._min, r._min), std::max(r._max, r._max)};
    }

    explicit segtree(const vi & v) : n(v.size()), t(2 * n) {
        F0R(i, n) t[i+n] = {v[i], v[i], v[i]};
        R0F(i, n) t[i] = apply(t[i<<1], t[i<<1|1]);
    }
    explicit segtree(ll n) : segtree(vi(n)) {}

    void set(ll p, T value) {  // set value at position p
        for (t[p += n] = {value, value, value}; p > 1; p >>= 1) t[p>>1] = apply(t[p], t[p^1]);
    }

    node query(ll l, ll r) { // l, r inclusive
        ++r;
        node res;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = apply(res, t[l++]);
            if (r&1) res = apply(res, t[--r]);
        }
        return res;
    }

    T sum(ll l, ll r) { return query(l, r).s; }
    T min(ll l, ll r) { return query(l, r)._min; }
    T max(ll l, ll r) { return query(l, r)._max; }
};

int main() {
    io();
    ll n, k;
    cin >> n >> k;
    vi p(n), ip(n+1);
    F0R(i, n) cin >> p[i];
    F0R(i, n) ip[p[i]] = i;
    set<ll> b;
    F0R(i, k) {
        ll x;
        cin >> x;
        b.insert(x);
    }
    stack<ii> s;
    s.push({0, n - 1});
    segtree<ll> m(p), d(n);
    F0R(i, n) m.set(i, p[i]);
    ll w = 0;
    while (!s.empty()) {
        auto [l, r] = s.top();
        s.pop();
        if (!(0 <= l && l <= r && r < n)) continue;
        ll v = m.min(l, r);
        if (v == infll) continue;
        ll i = ip[v];
        if (b.count(v) == 0) {
            w += r-l+1 - d.sum(l, r);
            d.set(i, 1);
            m.set(i, infll);
            s.push({l, r});
        } else {
            s.push({l, i - 1});
            s.push({i + 1, r});
        }
    }
    cout << w << '\n';
}