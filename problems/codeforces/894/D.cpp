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

template<typename T> T ceildiv(T p, T q) {
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

vv<ii> t;
vvi child_distances, prefix_distances;
vi p;


void dfs(ll u) {
    for (auto [v, w] : t[u]) {
        dfs(v);
    }
    child_distances[u].pb(0);
    if (t[u].size() == 1) {
        auto  [v, w] = t[u][0];
        F0R(i, child_distances[v].size()) {
            child_distances[u].pb(child_distances[v][i] + w);
        }
    } else if (t[u].size() == 2) {
        auto [v0, w0] = t[u][0];
        auto [v1, w1] = t[u][1];
        ll i0 = 0, i1 = 0, sz0 = child_distances[v0].size(), sz1 = child_distances[v1].size();
        auto push_left = [&](){
            child_distances[u].pb(child_distances[v0][i0] + w0);
            i0++;
        };
        auto push_right = [&](){
            child_distances[u].pb(child_distances[v1][i1] + w1);
            i1++;
        };
        while (!(i0 == sz0 && i1 == sz1)) {
            if (i0 < sz0 && i1 < sz1) {
                if (child_distances[v0][i0] +w0 < child_distances[v1][i1] + w1) {
                    push_left();
                } else {
                    push_right();
                }
            } else if (i0 < sz0) {
                push_left();
            } else {
                push_right();
            }
        }
    }
    prefix_distances[u].pb(0);
    F0R(i, child_distances[u].size()) {
        prefix_distances[u].pb(prefix_distances[u].back() + child_distances[u][i]);
    }
}

int main() {
    io();
    ll n, m;
    cin >> n >> m;
    t.assign(n+1, {});
    child_distances = prefix_distances = vvi(n+1);
    vi pw(n+1);
    FOR(i, 1, n) {
        ll w;
        cin >> w;
        t[(i+1)/2].pb({i+1, w});
        pw[i+1]=w;
    }
    dfs(1);
    F0R(_, m) {
        ll u, h;
        cin >> u >> h;
        ll res = 0, next_sum = 0, next_cnt = 0;
        while (u > 0 && h > 0) {
            ll i = lower_bound(all(child_distances[u]), h) - child_distances[u].begin();
            res += (i - next_cnt) * h - prefix_distances[u][i] + next_sum;
            next_cnt = lower_bound(all(child_distances[u]), h - 2 * pw[u]) - child_distances[u].begin();
            next_sum = prefix_distances[u][next_cnt] + next_cnt * pw[u];
            h -= pw[u];
            u /= 2;
        }
        cout << res << '\n';
    }
}