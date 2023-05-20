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

template<typename T, const pair<T, int>&(*assoc_op)(const pair<T, int>&, const pair<T, int>&)=min<>>
struct sparse_table {
    vi logs;
    using rt = pair<T, int>; // value, index
    vv<rt> x;

    void build(const vector<T> &v) {
        logs.assign(v.size() + 1, 0);
        FOR(i, 2, v.size() + 1) logs[i] = logs[i / 2] + 1;
        x.eb();
        F0R(i, v.size()) x.back().eb(v[i], i);
        for (int sz = 2; sz <= v.size(); sz *= 2) {
            x.eb();
            const auto &prev = x[x.size() - 2];
            F0R(i, v.size() - sz + 1) {
                int j = min<int>(i + sz / 2, prev.size() - 1);
                x.back().pb(assoc_op(prev[i], prev[j]));
            }
        }
    }

    explicit sparse_table(int est_sz) {
        logs.reserve(est_sz + 1);
    }

    explicit sparse_table(const vector<T> &v) : sparse_table(v.size()) {
        build(v);
    }

    // l, r inclusive
    rt query(int l, int r) {
        int logsz = logs[r - l + 1];
        const auto &xx = x[logsz];
        return assoc_op(xx[l], xx[r - (1 << logsz) + 1]);
    }
};

template<typename IN>
IN fst_true(function<bool(IN)> predicate, IN low, IN high) {
    while (low < high) {
        IN middle = low + (high - low) / 2;
        if (predicate(middle))
            high = middle;
        else low = middle + 1;
    }
    return low;
}

template<typename IN>
IN lst_true(function<bool(IN)> predicate, IN low, IN high) {
    return fst_true<IN>([&](IN x) -> bool {return !predicate(x); }, low, high)-1;
}

template<typename IN>
IN flt_bin(function<bool(IN)> predicate, IN low, IN high, IN tol) {
    while (fabs(high - low) > tol) {
        IN middle = (low + high) / 2;
        if (predicate(middle))
            high = middle;
        else low = middle;
    }
    return low;
}

constexpr unsigned floorlog2(unsigned x)
{
    return x == 1 ? 0 : 1+floorlog2(x >> 1);
}

constexpr unsigned ceillog2(unsigned x)
{
    return x == 1 ? 0 : floorlog2(x - 1) + 1;
}

template<int N, typename T = int>
struct segtree {

    constexpr static T max_T = numeric_limits<T>::max();
    constexpr static T min_T = numeric_limits<T>::min();
    constexpr static int H = ceillog2(N), _N = 1<<H;

    struct node { T s, l, r; } t[2*_N];
    node merge(node x, node y) {
        return {x.s+y.s, std::min(x.l, y.l), std::max(x.r, y.r)};
    }

    T u[2*_N]; bool f[2*_N]; int a[2*_N], b[2*_N];
    segtree() {
        fill(t, t+2*_N, node({0, 0, 0}));
        fill(f, f+2*_N, 0), fill(u, u+2*_N, 0);
        iota(a+_N, a+2*_N, 0), iota(b+_N, b+2*_N, 0);
        for (int i = _N-1; i > 0; i--)
            a[i] = a[2*i], b[i] = b[2*i+1];
    }

    void apply(int i, T x, bool ins) {
        if (ins) u[i] = x, f[i] = 1;
        else u[i] += x;
    }

    void push(int i) {
        if (!f[i] && !u[i]) return;
        if (f[i]) t[i] = {0, 0, 0};
        t[i].s += u[i]*(b[i]-a[i]+1), t[i].l += u[i], t[i].r += u[i];
        if (i < _N) apply(2*i, u[i], f[i]), apply(2*i+1, u[i], f[i]);
        u[i] = f[i] = 0;
    }

    void _upd(int l, int r, T x, bool ins, int i = 1) {
        if (l <= a[i] && r >= b[i]) apply(i, x, ins);
        push(i);
        if (l > b[i] || r < a[i] || (l <= a[i] && r >= b[i])) return;
        _upd(l, r, x, ins, 2*i), _upd(l, r, x, ins, 2*i+1);
        t[i] = merge(t[2*i], t[2*i+1]);
    }

    node _qry(int l, int r, int i = 1) {
        push(i);
        if (l <= a[i] && r >= b[i]) return t[i];
        if (l > b[i] || r < a[i]) return {0, max_T, min_T};
        return merge(_qry(l, r, 2*i), _qry(l, r, 2*i+1));
    }

    T get(int i) {
        for (int x = H; x >= 0; x--) push((_N+i)>>x);
        return t[_N+i].s;
    }

    void set(int l, int r, T x) { _upd(l, r, x, 1); }
    void add(int l, int r, T x) { _upd(l, r, x, 0); }
    void set(int i, T x) { set(i, i, x); }
    void add(int i, T x) { add(i, i, x); }
    T sum(int l, int r) { return _qry(l, r).s; }
    T min(int l, int r) { return _qry(l, r).l; }
    T max(int l, int r) { return _qry(l, r).r; }
};


int main() {
    io();
    ll n, s, l;
    cin >> n >> s >> l;
    vi a(n);
    F0R(i, n) cin >> a[i];
    sparse_table<ll> minRMQ(a);
    sparse_table<ll, max<>> maxRMQ(a);
    constexpr int MX = 1e5 + 5;
    segtree<MX, ll> S;
    S.set(1, MX-1, infll);
    FOR(i, l-1, n) {
        ll maxj = i - l+1;
        ll j = fst_true<ll>([&](ll j) -> bool {
            ll diff = maxRMQ.query(j, i).first - minRMQ.query(j, i).first;
            return diff <= s;
        }, 0, maxj+1);
        if (j<=maxj) {
            S.set(i+1, S.min(j, maxj)+1);
        }
    }
    ll res = S.get(n);
    cout << (res >= infll ? -1 : res) << '\n';
}