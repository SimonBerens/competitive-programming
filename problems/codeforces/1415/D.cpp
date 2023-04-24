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

int main() {
    io();
    ll n;
    cin >> n;
    vi a(n);
    F0R(i, n) cin >> a[i];
    vi h(n);
    F0R(i, n) {
        while (a[i] >> h[i]) {
            h[i]++;
        }
    }
    F0R(i, n-2) {
        if (h[i] == h[i+1] && h[i+1] == h[i+2]) {
            cout << "1\n";
            return 0;
        }
    }
    ll res = M;
    F0R(i, n-1) {
        ll lx = 0;
        R0F(l, i+1) {
            lx ^= a[l];
            ll rx = 0;
            FOR(r, i+1, n) {
                rx ^= a[r];
                if (lx > rx) {
                    smin(res, r-l-1);
                }
            }
        }
    }
    if (res == M) {
        res = -1;
    }
    cout << res << '\n';
}