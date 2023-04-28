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

ll n, q, a, b;
vi v, c;

ll solve() {
    vi dp(n + 1, -infll);
    dp[0] = 0;
    ii m1{0, -1}, m2{0, -1};
    F0R(i, n) {
        ll color = c[i], &val = dp[color];
        ll first_c = (m1[1] == color ? m2 : m1)[0] + v[i] * b;
        ll same_c = val == -infll ? -infll : (val + v[i] * a);
        smax(val, max(first_c, same_c));
        if (val > m1[0] && color != m2[1]) {
            if (color != m1[1]) m2 = m1;
            m1 = {val, color};
        }
        else if (val > m2[0] && color != m1[1]) {
            m2 = {val, color};
            if (m1[0] < m2[0]) swap(m1, m2);
        }
    }
    return *max_element(all(dp));
}

int main() {
    io();
    cin >> n >> q;
    c = v = vi(n);
    F0R(i, n) cin >> v[i];
    F0R(i, n) cin >> c[i];
    F0R(_, q) {
        cin >> a >> b;
        cout << solve() << '\n';
    }
}