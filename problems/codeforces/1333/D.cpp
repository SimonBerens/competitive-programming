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

using ll = int;
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
    vi a;
    F0R(i, n) {
        char c;
        cin >> c;
        a.pb(c == 'R');
    }
    vv<ii> v;
    ll tot = 0;
    while (true) {
        vi to_swap;
        F0R(i, n-1) {
            if (a[i] > a[i+1]) {
                to_swap.pb(i);
                tot++;
            }
        }
        if (to_swap.empty()) break;
        v.eb();
        for (ll i: to_swap) {
            swap(a[i], a[i+1]);
            v.back().pb({i, i+1});
        }
    }
    if (k > tot || k < v.size()) {
        cout << "-1\n";
        return 0;
    }
    vv<ii> res;
    ll cur = 0;
    F0R(i, v.size()) {
        if (cur + v[i].size() + v.size() - i - 1 > k) {
            ll z = k - cur - (v.size() - i - 1) - 1;
            F0R(j, z) {
                res.pb({v[i][j]});
            }
            res.eb(v[i].begin() + z, v[i].end());
            copy(v.begin() + i + 1, v.end(), back_inserter(res));
            break;
        } else {
            F0R(j, v[i].size()) {
                res.pb({v[i][j]});
            }
            cur += v[i].size();
        }
    }
    for (auto &line: res) {
        cout << line.size();
        for (auto [l, r]: line) {
            cout << ' ' << r;
        }
        cout << '\n';
    }
}