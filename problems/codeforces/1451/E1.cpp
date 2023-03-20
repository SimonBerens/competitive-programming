// https://codeforces.com/contest/1451/problem/E1

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

void psol(const vi & res) {
    cout << '!';
    for (int x : res) cout << ' ' << x;
    cout << endl;
}


int query(const string& type, int i, int j) {
    cout << type << ' ' << i+1 << ' ' << j+1 << endl;
    int x;
    cin >> x;
    if (x == -1) exit(0);
    return x;
}

int main() {
    int n;
    cin >> n;
    vi q(n);
    FOR(i, 1, n) {
        q[i] = query("XOR", 0, i);
    }
    map<int, int> seen;
    seen[0] = 0;
    FOR(i, 1, n) {
        if (seen.count(q[i])) {
            int x = query("AND", i, seen[q[i]]);
            vi res(n);
            F0R(j, n) {
                res[j] = q[j] ^ q[i] ^ x;
            }
            psol(res);
            return 0;
        }
        seen[q[i]] = i;
    }
    int one_idx = seen[1], two_idx = seen[2];
    int x = query("AND", 0, one_idx);
    int y = query("AND", 0, two_idx);
    int z = x | y;
    vi res(n);
    F0R(i, n) {
        res[i] = q[i] ^ z;
    }
    psol(res);
}