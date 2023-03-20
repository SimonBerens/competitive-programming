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

ii read_edge(vector<set<int>> &graph, bool directed=false) {
    int a, b;
    cin >> a >> b;
    graph[a].insert(b);
    if (!directed) graph[b].insert(a);
    return {a, b};
}

vector<set<int>> read_graph(int V, int E, bool directed=false) {
    vector<set<int>> g(V);
    F0R(i, E) read_edge(g, directed);
    return g;
}

int n, m, V;

vector<set<int>> g;

optional<string> solve() {
    set<int> bs;
    set<set<int>> s;
    FOR(i, 1, V) {
        g[i].insert(i);
        if (g[i].size() == n) {
            bs.insert(i);
        }
    }
    FOR(i, 1, V) {
        if (g[i].size() != n) {
            for (int b : bs) {
                g[i].erase(b);
            }
            s.insert(g[i]);
        }
    }
    string res;
    if (!s.empty() && s.size() != 2) {
        return {};
    }
    FOR(i, 1, V) {
        if (g[i].size() == n) {
            res += 'b';
        } else {
            res += *s.begin() == g[i] ? 'a' : 'c';
        }
    }
    return res;
}

int main() {
    io();
    cin >> n >> m;
    V = n+1;
    g = read_graph(V, m);
    auto s = solve();
    if (!s.has_value()) {
        cout << "NO\n";
    } else {
        cout << "YES\n" << s.value() << '\n';
    }
}