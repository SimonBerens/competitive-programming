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
    ll n, m, q;
    cin >> n >> m >> q;
    vvi g(n, vi(m));
    F0R(i, n) {
        string s;
        cin >> s;
        F0R(j, m) {
            g[i][j] = s[j] - '0';
        }
    }
    vvi p(n+1, vi(m+1));
    F0R(i, n) {
        F0R(j, m) {
            p[i+1][j+1] = p[i][j+1] + p[i+1][j] - p[i][j] + g[i][j];
        }
    }
    vv<vvi> pp(n+1, vv<vi>(m+1, vvi(n+1, vi(m+1))));
    auto Z = [&](const array<ll, 4>& i) -> ll& {
        return pp[i[0]+1][i[1]+1][i[2]][i[3]];
    };
    F0R(i1, n) {
        F0R(j1, m) {
            R0F(i2, i1+1) {
                R0F(j2, j1+1) {
                    array<ll, 4> A, B, C, D;
                    A = {i1, j1, i2+1, j2};
                    B = {i1, j1-1, i2, j2};
                    C = {i1-1, j1, i2, j2};
                    D = {i1, j1, i2, j2+1};
                    auto X = [&](const vector<array<ll, 4>>& P) -> ll {
                        array<ll, 4> tmp{M, M, -M, -M};
                        F0R(i, P.size()) {
                            smin(tmp[0], P[i][0]);
                            smin(tmp[1], P[i][1]);
                            smax(tmp[2], P[i][2]);
                            smax(tmp[3], P[i][3]);
                        }
                        return Z(tmp);
                    };
                    ll & x = Z({i1, j1, i2, j2});
                    x += Z(A) + Z(B) + Z(C) + Z(D);
                    x -= X({A, B}) + X({A, C}) + X({A, D}) + X({B, C}) + X({B, D}) + X({C, D});
                    x += X({A, B, C}) + X({A, B, D}) + X({A, C, D}) + X({B, C, D});
                    x -= X({A, B, C, D});
                    if (p[i1+1][j1+1] - p[i2][j1+1] - p[i1+1][j2] + p[i2][j2] == 0) {
                        x++;
                    }
                }
            }
        }
    }
    F0R(_, q) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << pp[c][d][a-1][b-1] << '\n';
    }
}