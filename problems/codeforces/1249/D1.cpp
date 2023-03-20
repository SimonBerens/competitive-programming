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

template<typename T>
vi sort_indices(const vector<T> &v) {
    int s = v.size();
    vi idxs(s);
    iota(all(idxs), 0);
    sort(all(idxs), [&](int i, int j) -> bool { return v[i] < v[j]; });
    return idxs;
}

template<typename T>
vi sort_indices(const vector<T> &v, function<bool(const T &, const T &)> comp) {
    int s = v.size();
    vi idxs(s);
    iota(all(idxs), 0);
    sort(all(idxs), [&](int i, int j) -> bool { return comp(v[i], v[j]); });
    return idxs;
}

int main() {
    io();
    int n, k;
    cin >> n >> k;
    vii segments(n);
    F0R(i, n) {
        auto &[l, r] = segments[i];
        cin >> l >> r;
    }
    auto idxs = sort_indices<ii>(segments, [](ii a, ii b) -> bool { return a[1] < b[1]; });
    int S = 201;
    vi overlap(S);
    vi res;
    F0R(z, n) {
        int i = idxs[z];
        auto [l, r] = segments[i];
        // see if there are any elements >= k between l and r
        bool deleted = false;
        FOR(j, l, r + 1) {
            if (overlap[j] >= k) {
                res.pb(i);
                deleted = true;
                break;
            }
        }
        if (!deleted) {
            FOR(j, l, r + 1) {
                overlap[j]++;
            }
        }
    }
    cout << res.size() << '\n';
    for (int x: res) {
        cout << x + 1 << ' ';
    }
    cout << '\n';
}