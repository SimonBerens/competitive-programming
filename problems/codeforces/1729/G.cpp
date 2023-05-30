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

template<ll M>
struct modint {

    static ll _reduce(ll n) {
        constexpr static ll b = -1ull/M;
        ll r = n-(ll)(__uint128_t(b)*n>>64)*M; return r >= M ? r-M : r;
    }

    static ll _pow(ll n, ll k) {
        ll r = 1;
        for (; k > 0; k >>= 1, n = _reduce(n*n))
            if (k&1) r = _reduce(r*n);
        return r;
    }

    ll v; modint(ll n = 0) : v(_reduce(n)) { v += (M&(0-(v<0))); }

    friend string to_string(const modint n) { return to_string(n.v); }
    friend istream& operator>>(istream& i, modint& n) { return i >> n.v; }
    friend ostream& operator<<(ostream& o, const modint n) { return o << n.v; }
    template<typename T> explicit operator T() { return T(v); }

    friend bool operator==(const modint n, const modint m) { return n.v == m.v; }
    friend bool operator!=(const modint n, const modint m) { return n.v != m.v; }
    friend bool operator<(const modint n, const modint m) { return n.v < m.v; }
    friend bool operator<=(const modint n, const modint m) { return n.v <= m.v; }
    friend bool operator>(const modint n, const modint m) { return n.v > m.v; }
    friend bool operator>=(const modint n, const modint m) { return n.v >= m.v; }

    modint& operator+=(const modint n) { v += n.v; v -= (M&(0-(v>=M))); return *this; }
    modint& operator-=(const modint n) { v -= n.v; v += (M&(0-(v<0))); return *this; }
    modint& operator*=(const modint n) { v = _reduce(v*n.v); return *this; }
    modint& operator/=(const modint n) { v = _reduce(v*_pow(n.v, M-2)); return *this; }
    friend modint operator+(const modint n, const modint m) { return modint(n) += m; }
    friend modint operator-(const modint n, const modint m) { return modint(n) -= m; }
    friend modint operator*(const modint n, const modint m) { return modint(n) *= m; }
    friend modint operator/(const modint n, const modint m) { return modint(n) /= m; }
    modint& operator++() { return *this += 1; }
    modint& operator--() { return *this -= 1; }
    modint operator++(int) { modint t = *this; return *this += 1, t; }
    modint operator--(int) { modint t = *this; return *this -= 1, t; }
    modint operator+() { return *this; }
    modint operator-() { return modint(0) -= *this; }

    // O(logk) modular exponentiation
    modint pow(const ll k) const {
        return k < 0 ? _pow(v, M-1-(-k%(M-1))) : _pow(v, k);
    }
    modint inv() const { return _pow(v, M-2); }
};

using mi = modint<M>;
using mm = array<mi, 2>;
using vmi = vector<mi>;
using vmm = vector<mm>;
using vvmi = vv<mi>;


template <typename T = mi>
vector<T> p_fact(int n) {
    vector<T> res{1};
    FOR(i, 1, n+1) res.pb(res.back() * i);
    return res;
}

template <typename T = mi>
vector<T> p_fact_inv(int n) {
    vector<T> res{1};
    FOR(i, 1, n+1) res.pb(res.back() * T(i).inv());
    return res;
}

template <typename T = mi>
T C(int n, int k) {
    static auto f = p_fact<T>(1e6);
    static auto fi = p_fact_inv<T>(1e6);
    return k > n ? 0 : f[n] * fi[k] * fi[n-k];
}

template <typename T = mi>
T stars_bars(int n, int k) {
    return C<T>(k + n-1, n-1);
}


int main() {
    io();
    int q;
    cin >> q;
    vmi fi{1};
    FOR(i, 1, 501) fi.pb(fi.back() * mi(i).inv());
    for (int test_no = 0; test_no < q; ++test_no) {
        string s, t;
        cin >> s >> t;
        ll sn = s.size(), tn = t.size();
        vi yes(sn);
        F0R(i, sn) {
            bool found = true;
            F0R(j, tn) {
                if (i+j >= sn || s[i+j] != t[j]) {
                    found = false;
                    break;
                }
            }
            if (found) yes[i] = true;
        }
        vvi mdp(sn, vi(sn, infll));
        R0F(l, sn) {
            FOR(r, l, sn) {
                bool none = true;
                FOR(k, l, r+2-tn) {
                    if (!yes[k]) continue;
                    none = false;
                    ll res = 1;
                    if (k-1 >= l) res += mdp[l][k-1];
                    if (k+tn <= r) res += mdp[k+tn][r];
                    smin(mdp[l][r], res);
                }
                if (none) mdp[l][r] = 0;
            }
        }
        vvmi cdp(sn, vmi(sn));
        R0F(l, sn) {
            FOR(r, l, sn) {
                if (mdp[l][r] == 0) {
                    cdp[l][r] = 1;
                    continue;
                }
                FOR(k, l, r+2-tn) {
                    if (!yes[k]) continue;
                    ll mres = 1, lc = 0, rc = 0;
                    mi cres(1);
                    if (k-1 >= l) {
                        mres += lc = mdp[l][k - 1];
                        cres *= cdp[l][k-1];
                    }
                    if (k+tn <= r) {
                        mres += rc = mdp[k + tn][r];
                        cres *= cdp[k+tn][r];
                    }
                    if (mres == mdp[l][r]) {
                        cdp[l][r] += cres * C(lc + rc, lc);
                    }
                }
            }
        }
        ll min_moves = mdp[0][sn - 1];
        mi poss = cdp[0][sn - 1];
        cout << min_moves << ' ' << poss * fi[min_moves] << '\n';
    }
}