// https://codeforces.com/contest/630/problem/Q

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

const ld PI = atan2(0, -1);

void io() {
    ios::sync_with_stdio(0);
    cin.tie(0);
}

void io(string name) {
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
    io();
}

ld volume(int n_sides, ld side_length) {
    ld h1  = tan(PI * (n_sides - 2) / (2 * n_sides)) * side_length / 2;
    ld s = sqrt(pow(h1, 2) + pow(side_length / 2, 2));
    ld h = sqrt(pow(side_length, 2) - pow(s, 2));
    ld b = n_sides * pow(side_length, 2) / tan(PI / n_sides) / 4;
    return b * h / 3;
}

int main() {
    io();
    array<int, 3> l;
    cin >> l[0] >> l[1] >> l[2];
    ld res = 0;
    F0R(i, 3) {
        res += volume(i + 3, l[i]);
    }
    cout << setprecision(10) << fixed << res << '\n';
}