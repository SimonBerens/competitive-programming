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

ll n;

ld solve(const string & a, const string & b) {
    vvi pc(26, vi(n+1));
    R0F(i, n) {
        F0R(c, 26) {
            pc[c][i] = pc[c][i+1] + (n - i) * (a[i] - 'A' == c);
        }
    }
    ld res = 0;
    F0R(i, n) {
        ll c = b[i] - 'A';
        res += (i+1) * pc[c][i+1];
    }
    return res;
}

int main() {
    io();
    cout << fixed << setprecision(7);
    cin >> n;
    string a, b;
    cin >> a >> b;

    ld d = n * (n + 1) * (2 * n + 1) / 6;
    ld s = solve(a, b) + solve(b, a);
    F0R(i, n) {
        s += (i + 1) * (n - i) * (a[i] == b[i]);
    }
    cout << s / d << '\n';
}