// https://codeforces.com/contest/1288/problem/D

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

int main() {
    io();
    int n, m;
    cin >> n >> m;
    vvi a(n, vi(m));
    F0R(i, n) {
        F0R(j, m) {
            cin >> a[i][j];
        }
    }
    vii b(1 << m, {0, -1});
    vvi c(n, vi(1 << m, M));
    F0R(i, 1 << m) {
        F0R(j, n) {
            F0R(k, m) {
                if (((i >> k) & 1) == 1) {
                    smin(c[j][i], a[j][k]);
                }
            }
            smax(b[i], (ii{ c[j][i], j }));
        }
    }
    int res = -1, ri, rj;
    F0R(i, n) {
        if (c[i].back() > res) {
            res = c[i].back();
            ri = rj = i;
        }
    }
    F0R(i, n) {
        FOR(j, 1, (1 << m)-1) {
            int comp = ((1 << m) - 1) ^ j;
            int cand = min(b[comp][0], c[i][j]);
            if (cand > res) {
                res = cand;
                ri = i;
                rj = b[comp][1];
            }
        }
    }
    cout << ri+1 << ' ' << rj+1 << '\n';
}