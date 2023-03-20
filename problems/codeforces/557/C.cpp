// https://codeforces.com/contest/557/problem/C

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
    int n;
    cin >> n;
    vi l(n), d(n);
    F0R(i, n) cin >> l[i];
    F0R(i, n) cin >> d[i];
    map<int, vi, greater<>> lcnt;
    F0R(i, n) lcnt[l[i]].pb(i);
    vi dcnt(201);
    F0R(i, n) dcnt[d[i]]++;
    int energy = 0;
    int current_legs = n;
    int res = M;
    for (auto [len, idxs] : lcnt) {
        int cnt = idxs.size();
        int max_legs_allowed = 2 * cnt - 1;
        int D = 0;
        for (int i : idxs) {
            dcnt[d[i]]--;
            D += d[i];
        }
        int deletes_needed = max(0, current_legs - max_legs_allowed);
        int cur_energy = 0;
        FOR(ddd, 1, 201) {
            int deleted = min(deletes_needed, dcnt[ddd]);
            deletes_needed -= deleted;
            cur_energy += ddd * deleted;
        }
        smin(res, energy + cur_energy);
        energy += D;
        current_legs -= cnt;
    }
    cout << res << '\n';
}