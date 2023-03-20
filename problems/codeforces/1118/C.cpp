// https://codeforces.com/contest/1118/problem/C

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
template<typename K> using hset = gp_hash_table<K, null_type>;
template<typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back
#define smax(x, y) (x = max(x, y))
#define smin(x, y) (x = min(x, y))

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i,0,a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i,0,a)

template<typename T, unsigned long N>
istream &operator>>(istream &in, array<T, N> &arr) {
    F0R(i, N) in >> arr[i];
    return in;
}

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

void no() {
    cout << "NO\n";
    exit(0);
}

int n;
vvi res;
maxq<ii> q;

int rev(int i) {
    return n - 1 - i;
}

void push(vii v) {
    auto [cnt, i] = q.top();
    q.pop();
    if (cnt < v.size()) no();
    for (auto [r, c]: v) {
        res[r][c] = i;
    }
    q.push({cnt - (int) v.size(), i});
}

int main() {
    io();
    cin >> n;
    res = vvi(n, vi(n));
    map<int, int> f;
    F0R(i, n * n) {
        int a;
        cin >> a;
        f[a]++;
    }
    for (auto [i, cnt]: f) {
        q.push({cnt, i});
    }
    int m = n / 2;
    F0R(r, m) {
        F0R(c, m) {
            push({{r,      c},
                  {rev(r), c},
                  {r,      rev(c)},
                  {rev(r), rev(c)}});
        }
    }
    if (n % 2 == 1) {
        F0R(i, m) {
            push({{m, i},
                  {m, rev(i)}});
            push({{i,      m},
                  {rev(i), m}});
        }
        push({{m, m}});
    }
    cout << "YES\n";
    F0R(r, n) {
        F0R(c, n) {
            cout << res[r][c] << ' ';
        }
        cout << '\n';
    }
}