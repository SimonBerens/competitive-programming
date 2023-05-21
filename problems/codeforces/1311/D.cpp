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

int main() {
    io();
    ll MX = 2e4+5;
    vvi divs(MX);
    FOR(i, 1, MX) {
        FOR(m, 1, MX) {
            if (i*m>=MX) break;
            divs[i*m].pb(i);
        }
    }
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        ll a, b, c, ra, rb, rc;
        ll res = infll;
        cin >> a >> b >> c;
        FOR(cc, 1, MX) {
            for (ll bb : divs[cc]) {
                for (ll aa : divs[bb]) {
                    ll cand = abs(cc-c) + abs(bb-b) + abs(aa-a);
                    if (cand < res) {
                        ra = aa;
                        rb = bb;
                        rc = cc;
                        res = cand;
                    }
                }
            }
        }
        cout << res << '\n';
        cout << ra << ' ' << rb << ' ' << rc << '\n';
    }
}