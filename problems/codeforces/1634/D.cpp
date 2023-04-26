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

map<array<ll, 3>, ll> cache;

ll query(ll i, ll j, ll k) {
    if (cache.count({i, j, k})) return cache[{i, j, k}];
    cout << "? " << i + 1 << ' ' << j + 1 << ' ' << k + 1 << endl;
    ll res;
    cin >> res;
    return cache[{i, j, k}] = res;
}

void submit(ll i, ll j) {
    cout << "! " << i + 1 << ' ' << j + 1 << endl;
}

ii solve_4(ll i, ll j, ll k, ll l) {
    // query i, j, k
    // query i, j, l
    // query i, k, l
    array<array<ll, 3>, 3> idxs{{{i, j, k},
                                 {i, j, l},
                                 {i, k, l}}};
    vector<array<ll, 4>> v;
    for (auto [a, b, c]: idxs) {
        v.pb({query(a, b, c), a, b, c});
    }
    auto set_int = [&](const array<ll, 4> & x, const array<ll, 4> & y) {
        ii res;
        ll cnt = 0;
        FOR(xi, 1, 4) {
            FOR(yi, 1, 4) {
                if (x[xi] == y[yi]) res[cnt++] = x[xi];
            }
        }
        return res;
    };
    auto set_diff = [&](const array<ll, 4> & x, const array<ll, 4> & y) {
        FOR(xi, 1, 4) {
            bool found = false;
            FOR(yi, 1, 4) {
                if (x[xi] == y[yi]) found = true;
            }
            if (!found) return x[xi];
        }
    };
    sort(all(v));
    if (v[1][0] == v[2][0]) {
        return set_int(v[1], v[2]);
    } else {
        return {set_diff(v[2], v[1]), set_diff(v[2], v[0])};
    }
}

int main() {
    io();
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        cache.clear();
        ll n;
        cin >> n;
        ii m1{-1, -1};
        FOR(i, 2, n) {
            smax(m1, {query(0, 1, i), i});
        }
        ii m2{-1, -1};
        FOR(i, 2, n) {
            if (i == m1[1]) continue;
            smax(m2, {query(0, m1[1], i), i});
        }
        auto [i, j] = solve_4(0, 1, m1[1], m2[1]);
        submit(i, j);
    }
}