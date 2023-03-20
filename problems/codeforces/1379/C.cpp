// https://codeforces.com/contest/1379/problem/C

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

template <typename T>
pair<map<T, int>, map<int, T>> cord_compress(const vector<T> & cords, int offset = 0) {
    map<T, int> compress;
    map<int, T> decompress;
    auto cpy = cords;
    sort(all(cpy));
    int lst = 0;
    F0R(i, cpy.size()) {
        if (compress.find(cpy[i]) == compress.end()) {
            int x = lst++ + offset;
            compress[cpy[i]] = x;
            decompress[x] = cpy[i];
        }
    }
    return {compress, decompress};
}

int main() {
    io();
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        int n, m;
        cin >> n >> m;
        vii f(m);
        vi cords;
        F0R(i, m) {
            int a, b;
            cin >> a >> b;
            cords.pb(a);
            cords.pb(b);
            f[i] = {a, b};
        }
        auto [cc, cd] = cord_compress(cords);
        F0R(i, m) F0R(j, 2) f[i][j] = cc[f[i][j]];
        int s = cc.size();
        vll cnta(s);
        F0R(i, m) cnta[f[i][0]]++;
        vll ssum(s + 1), scnt(s+1);
        R0F(i, s) {
            ssum[i] = ssum[i+1] + cd[i] * cnta[i];
            scnt[i] = scnt[i+1] + cnta[i];
        }
        ll res = 0;
        vi as(m);
        F0R(i, m) as[i] = cd[f[i][0]];
        sort(all(as));
        FOR(j, max(m - n, 0), m) res += as[j];
        for (auto [a, b] : f) {
            if (a <= b && scnt[b+1]+1 <= n) smax(res, cd[b] * (n - (scnt[b+1]+1)) + ssum[b+1] + cd[a]);
            else if (a > b && scnt[b+1] <= n) smax(res, cd[b] * (n - scnt[b+1]) + ssum[b+1]);
        }
        cout << res << '\n';
    }
}