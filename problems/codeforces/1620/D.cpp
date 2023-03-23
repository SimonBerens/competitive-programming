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

bool works(const vi & a, ll c1, ll c2, ll c3) {
    ll n = a.size();
    F0R(i, n) {
        bool found = false;
        F0R(a1, c1+1) {
            F0R(a2, c2+1) {
                ll d = a[i] - a1 - 2 * a2;
                if (d >= 0 && d % 3 == 0 && d / 3 <= c3) {
                    found = true;
                }
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

int main() {
    io();
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        ll n;
        cin >> n;
        vi a(n);
        F0R(i, n) {
            cin >> a[i];
        }
        sort(all(a));
        ll m = a.back();
        ll res = M;
        F0R(c1, 4) {
            F0R(c2, 4) {
                ll c3 = (m - c1 - 2 * c2 + 2) / 3;
                if (works(a, c1, c2, c3)) {
                    smin(res, c1 + c2 + c3);
                }
            }
        }
        cout << res << '\n';
    }
}