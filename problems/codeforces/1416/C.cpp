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

template<typename T> T c2(T x) {
    return x * (x - 1) / 2;
}

template<typename T> T sq(T x) {
    return x * x;
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

ii count_inversions(const vi& a) {
    vi z(a.size()+1);
    ll def = 0, swapped = 0;
    R0F(i, a.size()) {
        z[i] = z[i+1] + (a[i] == 0);
        if (a[i] == 1) {
            def += z[i];
        } else {
            swapped += a.size() - i - z[i];
        }
    }
    return {def, swapped};
}

vi get_bit_array(const vi &a, ll b) {
    vi res;
    F0R(i, a.size()) {
        res.pb((a[i] >> b) & 1);
    }
    return res;
}

vi inv_bit_array(const vi &a) {
    vi res;
    F0R(i, a.size()) {
        res.pb(!a[i]);
    }
    return res;
}

ii solve(const vi& a) {
    vvi v(1, a);
    ll t_inv = 0, x = 0;
    R0F(b, 33) {
        vvi nv;
        ll def_inv = 0, swap_inv = 0;
        for (const auto & vec: v) {
            auto bit_arr = get_bit_array(vec, b);
            auto [d, s] = count_inversions(bit_arr);
            def_inv += d;
            swap_inv += s;
            vvi p(2);
            F0R(i, vec.size()) {
                p[bit_arr[i]].pb(vec[i]);
            }
            F0R(i, 2) if (!p[i].empty()) nv.pb(p[i]);
        }
        t_inv += min(def_inv, swap_inv);
        x |= (swap_inv < def_inv) << b;
        swap(v, nv);
    }
    return {t_inv, x};
}

int main() {
    io();
    ll n;
    cin >> n;
    vi a(n);
    F0R(i, n) cin >> a[i];
    auto [inv, x] = solve(a);
    cout << inv << ' ' << x << '\n';
}