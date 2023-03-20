// https://codeforces.com/contest/1198/problem/A

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

template <typename T>
pair<hmap<T, int>, hmap<int, T>> cord_compress(const vector<T> & cords, int offset = 0) {
    hmap<T, int> compress;
    hmap<int, T> decompress;
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
    int n, I;
    cin >> n >> I;
    vi a(n);
    F0R(i, n) {
        cin >> a[i];
    }
    auto [c, dc] = cord_compress(a);
    vi aa(n);
    F0R(i, n) aa[i] = c[a[i]];
    int target_bits_per_num = min(I * 8 / n, 30);
    int target_distinct_nums = 1 << target_bits_per_num;
    int K = c.size();
    if (target_distinct_nums >= K) {
        cout << 0 << '\n';
        return 0;
    }
    vi f(K);
    F0R(i, n) {
        f[aa[i]]++;
    }
    vi p(K+1);
    F0R(i, K) {
        p[i + 1] = p[i] + f[i];
    }
    int res = M;
    F0R(i, K - target_distinct_nums + 1) {
        smin(res, p[i] + p[K] - p[i + target_distinct_nums]);
    }
    cout << res << endl;
}