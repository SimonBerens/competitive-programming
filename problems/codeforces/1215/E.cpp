#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
template<typename K> using hset = gp_hash_table<K, null_type>;
template<typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back

template<typename T>
void smin(T &x, T y) {
    x = min(x, y);
}

template<typename T>
void smax(T &x, T y) {
    x = max(x, y);
}

template<typename T>
T c2(T x) {
    return x * (x - 1) / 2;
}

template<typename T>
T sq(T x) {
    return x * x;
}

template<typename T>
T ceildiv(T p, T q) {
    return (p + q - 1) / q;
}

#define FOR(i, a, b) for (ll i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i,0,a)
#define ROF(i, a, b) for (ll i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i,0,a)

using ll = long long;
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

template<typename T>
pair<hmap<T, int>, hmap<int, T>> cord_compress(const vector<T> &cords, int offset = 0) {
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
    ll n;
    cin >> n;
    vi a(n);
    F0R(i, n) cin >> a[i];
    auto [compress, _] = cord_compress(a);
    F0R(i, n) a[i] = compress[a[i]];
    ll C = compress.size();
    // for each color, compute how much each color adds to the cost of moving the og color to the left
    vvi cost(C, vi(C));
    vi cnt(C);
    for (ll c : a) {
        cnt[c]++;
        F0R(cc, C) {
            if (cc != c) cost[c][cc] += cnt[cc];
        }
    }

    vi dp(1 << C, infll);
    dp[0] = 0;
    F0R(s, dp.size()) {
        F0R(c, C) {
            if ((s >> c) & 1) continue;
            ll t_cost = 0;
            F0R(cc, C) {
                if ((s >> cc) & 1) {
                    t_cost += cost[c][cc];
                }
            }
            smin(dp[s ^ (1 << c)], dp[s] + t_cost);
        }
    }
    cout << dp.back() << '\n';
}