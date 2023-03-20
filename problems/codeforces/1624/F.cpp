// https://codeforces.com/contest/1624/problem/F

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

int s = 0;

void psol(int x) {
    cout << "! " << s + x << endl;
}

int query(int c) {
    cout << "+ " << c << endl;
    s += c;
    int res;
    cin >> res;
    return res;
}

int main() {
    int n;
    cin >> n;
    int l = 1, r = n - 1, p = 0;
    while (l < r - 1) {
        cerr << l << ' ' << r << endl;
        int ll = (l + s) % n, rr = (r + s) % n;
        int m = (ll + rr + 1) / 2;
        int c = n - m;
        int q = query(c);
        if (q > p) {
            l += m - ll;
            p++;
        }
        else r -= rr - m + 1;
    }
    cerr << l << ' ' << r << endl;

    if (l == r || query(n -((r + s) % n)) == p) {
        psol(l);
    } else psol(r);
}