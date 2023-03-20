// https://codeforces.com/contest/1190/problem/B

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

bool flip = false;
void pans(int x) {
    cout << ((x ^ flip) == 0 ? "sjfnb" : "cslnb") << '\n';
}

int main() {
    io();
    ll n;
    cin >> n;
    vll a(n);
    F0R(i, n) cin >> a[i];
    map<ll, int> m;
    F0R(i, n) m[a[i]]++;
    for (auto [x, cnt]: m) {
        if (cnt > 1) {
            if (cnt > 2 || x == 0 || m[x-1] > 0) {
                pans(1);
                return 0;
            } else {
                flip = true;
                m[x]--;
                m[x-1]++;
            }
        }
    }
    vll b;
    for (auto [x, cnt]: m) {
        b.pb(x);
    }
    assert(b.size() == n);
    vll idxs(n);
    ll t = 0;
    F0R(i, n) {
        t += b[i] - i;
    }
    pans((t % 2) ^ 1);
}
