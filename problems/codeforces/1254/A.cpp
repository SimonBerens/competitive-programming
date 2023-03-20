// https://codeforces.com/contest/1254/problem/A

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

char outc(int x) {
    if (x <= 9) return '0' + x;
    else if (x - 9 <= 26) return 'A' + x - 10;
    else return 'a' + x - 36;
}

int main() {
    io();
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        int k;
        cin >> R >> C >> k;
        g = vvi(R, vi(C));
        int rice = 0;
        F0R(r, R) {
            F0R(c, C) {
                char ch;
                cin >> ch;
                g[r][c] = ch;
                if (ch == 'R') {
                    rice++;
                }
            }
        }
        int m = rice % k;
        vector<string> res(R, string(C, ' '));
        int crice = 0;
        int ck = 0;
        auto f = [&](int r, int c) -> void {
            if (g[r][c] == 'R') {
                crice++;
            }
            res[r][c] = outc(ck);
            // increment current chicken
            if (crice == rice / k + (m > 0) && ck < k - 1) {
                ck++;
                crice = 0;
                m = max(0, m-1);
            }
        };
        F0R(r, R) {
            if (r % 2 == 0) {
                F0R(c, C) {
                    f(r, c);
                }
            } else {
                R0F(c, C) {
                    f(r, c);
                }
            }
        }
        F0R(r, R) {
            cout << res[r] << '\n';
        }
    }
}