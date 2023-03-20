// implementation of tutorial

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

template<typename IN>
IN discrete_binary_search(function<bool(IN)> predicate, IN low = 0, IN high = numeric_limits<IN>::max()) {
    while (low < high) {
        IN middle = low + (high - low) / 2; // todo std::midpoint in cpp 2020
        if (predicate(middle))
            high = middle;
        else low = middle + 1;
    }
    return low;
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

    auto solve = [&](int x) -> tuple<bool, int, int> {
        auto mask = [&](int i) -> int {
            int res = 0;
            F0R(j, m) {
                res ^= (a[i][j] >= x) << j;
            }
            return res;
        };
        set<int> b;
        F0R(i, n) {
            b.insert(mask(i));
        }
        vi v(all(b));
        F0R(i, v.size()) {
            FOR(j, i, v.size()) {
                if ((v[i] | v[j]) == (1 << m) - 1) {
                    int ri, rj;
                    F0R(k, n) {
                        int msk = mask(k);
                        if (msk == v[i]) ri = k;
                        if (msk == v[j]) rj = k;
                    }
                    return {true, ri, rj};
                }
            }
        }
        return {false, 0, 0};
    };
    int best =  discrete_binary_search<int>([&](int x) -> bool {
        auto [possible, i, j] = solve(x);
        return !possible;
    }, 0, M) - 1;
    auto [_, i, j] = solve(best);
    cout << i + 1 << ' ' << j + 1 << '\n';
}