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

mt19937 randint(chrono::steady_clock::now().time_since_epoch().count());

// returns a random integer over [a, b] inclusive
inline int uniform_randint(const int a, const int b) {
    return uniform_int_distribution<int>(a, b)(randint);
}

constexpr ll P = (1ull << 61) - 1;

template<>
modint<P> &modint<P>::operator*=(const modint<P> n) {
    uint64_t l1 = (uint32_t) v, h1 = v >> 32, l2 = (uint32_t) n.v, h2 = n.v >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & P) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & P) + (ret >> 61);
    ret = (ret & P) + (ret >> 61);
    v = ret - 1;
    return *this;
}

using mi = modint<P>;
using vmi = vector<mi>;

int b1 = uniform_randint(5000, 10000);
int b2 = uniform_randint(10001, 20000);

using shash_t = pair<mi, mi>;

struct hash_querier {
    vmi hsh1, hsh2;
    inline static vmi bp1{}, bp2{};

    explicit hash_querier(const string &s) :
            hsh1(s.size() + 1), hsh2(s.size() + 1) {
        F0R(i, s.size()) {
            hsh1[i + 1] = s[i] - 'a' + hsh1[i] * b1;
            hsh2[i + 1] = s[i] - 'a' + hsh2[i] * b2;
        }
        bp1.reserve(s.size()+1);
        bp2.reserve(s.size()+1);
        if (bp1.empty()) {
            bp1.eb(1);
            bp2.eb(1);
        }
        FOR(i, bp1.size()-1, s.size()) {
            bp1.pb(bp1[i] * b1);
            bp2.pb(bp2[i] * b2);
        }
    }

    // hash of substring [l, r] inclusive
    shash_t query(int l, int r) {
        return {hsh1[r + 1] - hsh1[l] * bp1[r - l + 1],
                hsh2[r + 1] - hsh2[l] * bp2[r - l + 1]};
    }
};

string pp(const string & s) {
    auto rs = s;
    reverse(all(rs));
    hash_querier h(s), hr(rs);
    ll n = s.size();
    auto ri = [&](ll i) -> ll {
        return n - 1 - i;
    };
    ll rl = 1;
    F0R(i, n/2) {
        if (2 * (i + 2) - 1 <= n && h.query(0, i+1) == hr.query(ri(2 * (i+1)), ri(i+1))) {
            smax(rl, 2 * (i+2) -1);
        }
        if (h.query(0, i) == hr.query(ri(2 * i + 1), ri(i+1))) {
            smax(rl, 2 * (i + 1));
        }
    }
    return s.substr(0, rl);
}

string psp(const string & s) {
    auto p = pp(s);
    auto rs = s;
    reverse(all(rs));
    auto su = pp(rs);
    if (p.size() > su.size()) {
        return p;
    } else {
        reverse(all(su));
        return su;
    }
}

int main() {
    io();
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        string s;
        cin >> s;
        ll n = s.size();
        string res = psp(s);
        F0R(i, n/2) {
            ll j = n - 1 - i;
            if (s[i] != s[j]) {
                if (i > 0) {
                    res = s.substr(0, i) + psp(s.substr(i, n - 2 * i)) + s.substr(n - i, i);
                }
                break;
            }
        }
        cout << res << '\n';
    }
}