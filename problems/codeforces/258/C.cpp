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

using mi = modint<M>;
using vmi = vector<mi>;

mt19937 randint(chrono::steady_clock::now().time_since_epoch().count());

// returns a random integer over [a, b] inclusive
inline int uniform_randint(const int a, const int b) {
    return uniform_int_distribution<int>(a, b)(randint);
}

// returns a vector of length n, containing 1 if a number is prime, else 0.
// runs in O(nloglogn) time.
vector<bool> primesieve(int n) {
    vector<bool> sieve(n, 1);
    for (int i = 2; i < n; i++)
        if (sieve[i])
            for (int j = 2*i; j < n; j += i)
                sieve[j] = 0;
    sieve[1] = 0;
    return sieve;
}

// returns a sorted list of all primes less than or equal to n.
// runs in O(nloglogn) time.
vector<ll> primesupto(int n) {
    vector<bool> sieve = primesieve(n+1);
    vector<ll> out;
    for (int i = 2; i <= n; i++)
        if (sieve[i]) out.push_back(i);
    return out;
}

// checks if a number is prime in O(log^3(n)) time, randint comes from random.cpp.
// works for n <= 10^18
bool isprime(ll n) {
    static vector<bool> sieve = primesieve(1000000);
    if (n < sieve.size()) return sieve[n];
    if (n%2 == 0) return false;
    ll d = n-1, r = 0;
    while (d%2 == 0) r++, d >>= 1;
    for (int k = 0; k < 30; k++) {
        __int128_t x = 1, a = uniform_int_distribution<ll>(2, n-2)(randint);
        for (ll i = 1; i <= d; i <<= 1) {
            if (d&i) x = (x*a)%n;
            a = (a*a)%n;
        }
        bool f = 0;
        if (x == 1 || x == n-1) f = 1;
        for (int i = 1; i < r; i++)
            f = f || (x = (x*x)%n) == n-1;
        if (!f) return false;
    }
    return true;
}

// returns a sorted list of all prime factors of n in O(min(n^(1/2), n^(1/4)+log^3(n)+10^5)) time.
// works for n <= 10^18
vector<ll> primefactors(ll n) {
    static vector<ll> small = primesupto(1000000);
    if (isprime(n)) return {n};
    vector<ll> out;
    for (ll p : small) {
        if (p*p > n) break;
        while (n%p == 0)
            n /= p, out.push_back(p);
    }
    if (n == 1 || isprime(n)) {
        if (n != 1) out.push_back(n);
        return out;
    }
    __int128_t x = 2, y = 2;
    ll f = 0;
    for (ll z = 1; 1; z <<= 1) {
        y = x;
        for (ll i = 0; i < z; i++)
            if ((f = gcd(ll((x = (x*x+1)%n)-y), n)) > 1) {
                out.push_back(min(f, n/f)), out.push_back(max(f, n/f));
                return out;
            }
    }
    return out;
}

// returns a sorted list of all divisors of n in approximately O(min(n^(1/2), n^(1/3)+log^3(n)+10^5)) time.
// works for n <= 10^18
vector<ll> divisors(ll n) {
    map<ll, int> p;
    for (ll x : primefactors(n))
        p[x]++;
    vector<ll> out = {1};
    for (auto& [q, f] : p) {
        vector<ll> tmp;
        for (ll x : out) {
            ll r = 1;
            for (int i = 0; i <= f; i++) {
                tmp.pb(x*r);
                r *= q;
            }
        }
        out = tmp;
    }
    sort(all(out));
    return out;
}


ll n, MX = 1e5+2;
vi a, a_ge(MX);
vmi f(MX, 1);

void calc_ge() {
    ll j = n-1;
    R0F(i, MX-1) {
        a_ge[i] = a_ge[i+1];
        while (j >= 0 && a[j] >= i) {
            j--;
            a_ge[i]++;
        }
    }
}

void calc_f() {
    FOR(i, 2, MX-1) {
        auto divs = divisors(i);
        divs.back() = MX-1;
        F0R(j, divs.size()-1) {
            f[i] *= mi(j+1).pow(a_ge[divs[j]] - a_ge[divs[j+1]]);
        }
    }
}

int main() {
    io();
    cin >> n;
    a = vi(n);
    F0R(i, n) {
        cin >> a[i];
    }
    sort(all(a));
    calc_ge();
    calc_f();
    mi res(1);
    FOR(i, 2, MX-1) {
        mi d = divisors(i).size() - 1;
        ll k = a_ge[i];
        res += f[i] * ((d + 1).pow(k) / d.pow(k) - 1);
    }
    cout << res << '\n';

}