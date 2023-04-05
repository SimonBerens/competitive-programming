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

vvi g;

int R, C;

vii dirs{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
vii dirs8{{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

bool inbounds(int r, int c) {
    return 0 <= r && r < R && 0 <= c && c < C;
}

vii adjc(int r, int c, const vii &ds = dirs) {
    vii res;
    for (auto[dr, dc]: ds) {
        int nr = r + dr, nc = c + dc;
        if (inbounds(nr, nc)) res.pb({nr, nc});
    }
    return res;
}

int enc(int r, int c) {
    return r * C + c;
}

ii dec(int idx) {
    return {idx / R, idx % R};
}

int n, d;
ll FREE = 0, START = 1, WALL = 2;

vvi calc_wall_dist() {
    queue<array<ll, 3>> q;
    vvi wd(n, vi(n, -1));
    F0R(r, n) {
        F0R(c, n) {
            if (g[r][c] == WALL) {
                q.push({0, r, c});
                wd[r][c] = 0;
            }
        }
    }
    while (!q.empty()) {
        auto [l, r, c] = q.front();
        q.pop();
        for (auto [nr, nc]: adjc(r, c)) {
            if (wd[nr][nc] == -1 && g[nr][nc] != WALL) {
                wd[nr][nc] = l + 1;
                q.push({l+1, nr, nc});
            }
        }
    }
    return wd;
}

vvi calc_robot_rs(const vvi & wall_dist) {
    queue<array<ll, 3>> q;
    F0R(r, n) {
        F0R(c, n) {
            if (g[r][c] == START) {
                q.push({0, r, c});
            }
        }
    }
    vvi seen(n, vi(n));
    while (!q.empty()) {
        auto [p, r, c] = q.front();
        q.pop();
        if (seen[r][c]) continue;
        ll rad = p / d + 1;
        seen[r][c] = rad;
        if (wall_dist[r][c] < rad) {
            seen[r][c]--;
            continue;
        }
        for (auto [nr, nc] : adjc(r, c)) {
            if (g[nr][nc] != 2 && !seen[nr][nc] && wall_dist[nr][nc] >= rad) {
                q.push({p+1, nr, nc});
            }
        }
    }
    return seen;
}

ll count_cells(const vvi & robot_rs) {
    vvi seen(n, vi(n));
    maxq<array<ll, 3>> q;
    F0R(r, n) {
        F0R(c, n) {
            if (robot_rs[r][c]) {
                q.push({robot_rs[r][c], r, c});
            }
        }
    }
    ll res = 0;
    while (!q.empty()) {
        auto [p, r, c] = q.top();
        q.pop();
        if (seen[r][c]) continue;
        seen[r][c] = true;
        res++;
        if (p == 1) continue;
        for (auto [nr, nc] : adjc(r, c)) {
            if (!seen[nr][nc] && g[nr][nc] != 2) {
                q.push({p - 1, nr, nc});
            }
        }
    }
    return res;
}


int main() {
    io();
    cin >> n >> d;
    R = C = n;
    g.assign(n, vi(n));
    F0R(r, n) {
        string s;
        cin >> s;
        F0R(c, n) {
            if (s[c] == '.') g[r][c] = FREE;
            else if (s[c] == 'S') g[r][c] = START;
            else if (s[c] == '#') g[r][c] = WALL;
        }
    }
    auto wall_dist = calc_wall_dist();
    auto robot_rs = calc_robot_rs(wall_dist);
    cout << count_cells(robot_rs) << '\n';
}