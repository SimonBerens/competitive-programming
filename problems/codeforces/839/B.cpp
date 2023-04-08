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
    ll n, k;
    cin >> n >> k;
    vi a(k);
    F0R(i, k) {
        cin >> a[i];
    }
    ll fours = n, twos = 2 * n, ones = 0;
    F0R(i, k) {
        ll f = min(a[i] / 4, fours);
        fours -= f;
        a[i] -= f * 4;
    }
    F0R(i, k) {
        if (a[i] > 2 && a[i] % 2 && fours) {
            fours--;
            a[i] -= 3;
        }
    }
    F0R(i, k) {
        if (fours && a[i]) {
            fours--;
            if (a[i] == 1) twos++;
            else ones++;
            a[i] = 0;
        }
    }
    F0R(i, k) {
        if (ones && a[i] % 2) {
            a[i]--;
            ones--;
        }
    }
    F0R(i, k) {
        ll o = min(ones, a[i]);
        a[i] -= o;
        ones -= o;
    }
    ll s = 0;
    F0R(i, k) {
        s += a[i] + (a[i] % 2);
    }
    if (s <= twos * 2) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}