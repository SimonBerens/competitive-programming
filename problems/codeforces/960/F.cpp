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



int main() {
    io();
    ll n, m;
    cin >> n >> m;
    vector<array<ll, 3>> edges(m);
    F0R(i, m) {
        auto &[w, u, v] = edges[i];
        cin >> u >> v >> w;
    }
    vector<map<ll, ll>> dp(n+1);
    for (auto [w, u, v] : edges) {
        auto get_l = [&]() -> ll {
            if (dp[u].empty()) return 1;
            auto it = dp[u].lower_bound(w);
            if (it == dp[u].begin()) return 1;
            --it;
            return it->second + 1;
        };
        ll l = get_l();
        auto is_worse = [&]() -> bool {
            auto it = dp[v].upper_bound(w);
            if (dp[v].empty() || it == dp[v].begin()) return false;
            --it;
            return it->second >= l;
        };
        if (is_worse()) {
            continue;
        }
        set<ll> to_erase;
        for (auto vit = dp[v].lower_bound(w); vit != dp[v].end() && vit->second <= l; vit++) {
            to_erase.insert(vit->first);
        }
        for (ll x : to_erase) {
            dp[v].erase(x);
        }
        dp[v][w] = l;
    }
    ll res = 0;
    for (auto & m: dp) {
        for (auto [_, l]: m) {
            smax(res, l);
        }
    }
    cout << res << '\n';
}