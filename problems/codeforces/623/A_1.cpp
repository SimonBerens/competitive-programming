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

int n, m, V;

vvi g;

optional<string> solve() {
    string res(n + 1, 'c');
    FOR(u, 1, V) {
        if (count(all(g[u]), 1) == n) {
            res[u] = 'b';
        }
    }
    FOR(u, 1, V) {
        if (res[u] != 'b') {
            FOR(v, 1, V) {
                if (g[u][v] == 1 && res[v] != 'b') {
                    res[v] = 'a';
                }
            }
            break;
        }
    }
    FOR(u, 1, V) {
        FOR(v, 1, V) {
            if ((abs(res[u] - res[v]) < 2) != g[u][v]) {
                return {};
            }
        }
    }
    return res.substr(1);
}

int main() {
    io();
    cin >> n >> m;
    V = n + 1;
    g = vvi(V, vi(V));
    F0R(i, m) {
        int u, v;
        cin >> u >> v;
        g[u][v] = g[v][u] = 1;
    }
    FOR(i, 1, V) {
        g[i][i] = 1;
    }
    auto s = solve();
    if (!s.has_value()) {
        cout << "NO\n";
    } else {
        cout << "YES\n" << s.value() << '\n';
    }
}