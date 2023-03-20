// https://codeforces.com/contest/600/problem/D

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

ld sq(ld x) {
    return x * x;
}

// malding bc this doesn't work
void solve() {
    ld PI = atan2(0, -1);
    cout << fixed << setprecision(7);
    ld x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    ld dist = sqrt(sq(x1-x2) + sq(y1-y2));
    if (dist >= r1 + r2) {
        cout << 0. << '\n';
        return;
    }
    y2 = y1;
    x2 = x1 + dist;
    if (x1 + r1 >= x2 + r2 || x2 - r2 <= x1 - r1) {
        cout << PI * sq(min(r1, r2)) << '\n';
        return;
    }
    ld xint = (sq(r1) - sq(x1) - (sq(r2) - sq(x2))) / (2 * (x2 - x1));
    ld h = sqrt(sq(r1) - sq(xint - x1));
    ld t1 = asin(h / r1), t2 = asin(h / r2);
    ld a1 = xint > x1 ? t1 / 2 * sq(r1) - (xint - x1) * h / 2 : (PI - t1) / 2 * sq(r1) + (x1 - xint) * h / 2;
    ld a2 = x2 > xint? t2 / 2 * sq(r2) - (x2 - xint) * h / 2 : (PI - t2) / 2 * sq(r2) + (xint - x2) * h / 2;
    cout << 2 * (a1 + a2) << '\n';
}

void quit() { printf("0\n"), exit(0); }

int main() {
    io();
    ld x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    ld d = sqrt(sq(x2-x1)+sq(y2-y1));
    if (d+r1<=r2+1e-15) return printf("%1.12f\n",(double) (2*acos(0.0)*sq(r1))), 0;
    if (d+r2<=r1+1e-15) return printf("%1.12f\n",(double) (2*acos(0.0)*sq(r2))), 0;
    if (d>r1+r2) quit();

    ld one = (sq(d)+sq(r1)-sq(r2))/(2*d*r1);
    if (one<-1 || one>1) quit();
    one = sq(r1)*(acos(one)-one*sin(acos(one)));

    ld two = (sq(d)+sq(r2)-sq(r1))/(2*d*r2);
    if (two<-1 || two>1) quit();
    two = sq(r2)*(acos(two)-two*sin(acos(two)));

    printf("%1.12f\n",(double) (one+two));
}