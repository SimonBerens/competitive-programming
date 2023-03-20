// https://codeforces.com/contest/1439/problem/A2

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

vvi g;
int n, m;

using mt = array<ii, 2>;
mt zmt{{{0,  0}, {0, 0}}};

map<mt, mt> gr;
vector<array<int, 6>> res;

void apply(int r, int c, const mt& mask) {
    res.eb();
    int cur = 0;
    F0R(i, 2) {
        F0R(j, 2) {
            g[r+i][c+j] ^= mask[i][j];
            if (mask[i][j]) {
                res.back()[cur++] = 1 + r + i;
                res.back()[cur++] = 1 + c + j;
            }
        }
    }
}

void rot_mask_90_cw(mt & mask) {
    int t = mask[0][0];
    mask[0][0] = mask[1][0];
    mask[1][0] = mask[1][1];
    mask[1][1] = mask[0][1];
    mask[0][1] = t;
}

mt ext(int r, int c) {
    return {{{g[r][c], g[r][c + 1]}, {g[r + 1][c], g[r + 1][c + 1]}}};
}



void solve() {
    res.clear();
    cin >> n >> m;
    g = vvi(n, vi(m));
    F0R(i, n) {
        F0R(j, m) {
            char c;
            cin >> c;
            g[i][j] = c - '0';
        }
    }
    if (n %2 && m%2 && g[n-1][m-1]) {
        apply(n-2, m-2, {{{0, 1}, {1, 1}}});
    }
    if (n % 2) {
        for (int c = 0; c+1 < m; c+=2) {
            if (g[n-1][c]) apply(n-2, c, {{{1, 1}, {1, 0}}});
            if (g[n-1][c+1]) apply(n-2, c, {{{1, 1}, {0, 1}}});
        }
    }
    if (m % 2) {
        for (int r = 0; r+1 < n; r += 2) {
            if (g[r][m-1]) apply(r, m-2, {{{1, 1}, {1, 0}}});
            if (g[r+1][m-1]) apply(r, m-2, {{{1, 0}, {1, 1}}});
        }
    }
    for (int r = 0; r+1 < n; r += 2) {
        for (int c = 0; c+1 < m; c += 2) {
            mt x;
            while ((x = ext(r, c)) != zmt) {
                mt xc = x;
                int rots = 0;
                while (gr.count(xc) == 0) {
                    rot_mask_90_cw(xc);
                    rots++;
                }
                mt a = gr[xc];
                F0R(i, 4-rots) rot_mask_90_cw(a);
                apply(r, c, a);
            }
        }
    }
    cout << res.size() << '\n';
    for (auto & v : res) {
        for (int i : v) cout << i << ' ';
        cout << '\n';
    }
}

int main() {
    io();
    gr[{{{0, 1}, {1, 1}}}] = {{{0, 1}, {1, 1}}};
    gr[{{{1, 0}, {0, 1}}}] = {{{1, 1}, {1, 0}}};
    gr[{{{1, 0}, {1, 0}}}] = {{{1, 1}, {0, 1}}};
    gr[{{{0, 1}, {0, 0}}}] = {{{1, 1}, {1, 0}}};
    gr[{{{1, 1}, {1, 1}}}] = {{{1, 1}, {1, 0}}};
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        solve();
    }
}