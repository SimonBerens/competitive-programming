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

mt19937 randint(chrono::steady_clock::now().time_since_epoch().count());

// returns a random integer over [a, b] inclusive
inline int uniform_randint(const int a, const int b) {
    return uniform_int_distribution<int>(a, b)(randint);
}

void psol(ll x1, ll d) {
    cout << "! " <<  x1 << ' ' << d << endl;
}

ll q1(ll i) {
    cout << "? " << i+1 << endl;
    ll v;
    cin >> v;
    return v;
}

bool q2(ll x) {
    if (x > 1e9) return 0;
    cout << "> " << x << endl;
    ll v;
    cin >> v;
    return v;
}


int main() {
    ll n;
    cin >> n;
    ll m = 0;
    R0F(i, 30) {
        if (q2(m | (1 << i))) {
            m |= (1 << i);
        }
    }
    ++m;
    vi idxs(n);
    iota(all(idxs), 0);
    shuffle(all(idxs), randint);
    set<ll> s{m};
    F0R(i, min(30ll, n)) {
        s.insert(q1(idxs[i]));
    }
    vi v(all(s));
    ll g = v[1] - v[0];
    FOR(i, 1, v.size()-1) {
        g = gcd(g, v[i+1]-v[i]);
    }
    psol(m - (n-1)*g, g);
}