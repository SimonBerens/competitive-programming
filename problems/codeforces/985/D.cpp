// https://codeforces.com/contest/985/problem/D

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

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i,0,a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i,0,a)

using ll = long long;
using ld = long double;

template<typename T>
using vv = vector<vector<T>>;

using vi = vector<int>;
using ii = array<int, 2>;
using vii = vector<ii>;
using vvi = vv<int>;

using vll = vector<ll>;
using l2 = array<ll, 2>;
using vl2 = vector<l2>;
using vvll = vv<ll>;

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


int main() {
    io();
    ll n, H;
    cin >> n >> H;
    auto ct = [&](ll h) -> ll {
        if (h < H) return h * (h + 1) / 2;
        return h * (h + 1) / 2 + (h - 1 + H) * (h - H) / 2;
    };
    ll b = 2 * sqrt(n) + 100;
    ll rh = lst_true<ll>([&](ll h) -> bool {
        return ct(h) <= n;
    }, 0, b);
    ll t = ct(rh);
    if (rh <= H) {
        cout << rh + (n - t + rh - 1) / rh << '\n';
    } else {
        cout << rh + rh - H + (n - t + rh - 1) / rh << '\n';
    }
}