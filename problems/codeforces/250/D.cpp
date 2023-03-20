// https://codeforces.com/contest/250/problem/D

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
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vi ya(n), yb(m), l(m);
    F0R(i, n) cin >> ya[i];
    F0R(i, m) cin >> yb[i];
    F0R(i, m) cin >> l[i];
    int ri, rj;
    double rd = 1e18;
    auto dist = [&](int i, int j) {
        double da = sqrt(pow(ya[i], 2) + pow(a, 2));
        double dab = sqrt(pow(ya[i] - yb[j], 2) + pow(a - b, 2));
        return da + dab + l[j];
    };
    F0R(j, m) {
        int x = discrete_binary_search<int>([&](int i) -> bool {
            if (i +1 < n) {
                return dist(i, j) < dist(i+1, j);
            } else return true;
        }, 0, n-1);
        double d = dist(x, j);
        if (d < rd) {
            rd = d;
            ri = x;
            rj = j;
        }
    }
    cout << ri + 1 << ' ' << rj + 1 << '\n';
}