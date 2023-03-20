// https://codeforces.com/contest/1508/problem/A

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

int cz(const string &s) {
    return count(all(s), '0');
}

int n;

bool valid(const string &s1, const string &s2) {
    return (cz(s1) >= n) == (cz(s2) >= n);
}

char opp(char c) {
    return c == '0' ? '1' : '0';
}

void construct(string &s1, string &s2) {
    char c = cz(s1) >= n ? '0' : '1';
    if ((c == '0' && cz(s1) < cz(s2)) || (c == '1' && cz(s1) > cz(s2))) swap(s1, s2);
    int ccnt = (c == '0' ? cz(s2) : 2 * n - cz(s2));
    string res;
    int i = 0, j = 0;
    F0R(_, ccnt) {
        int ni = s1.find(c, i);
        int nj = s2.find(c, j);
        res += string(max(ni - i, nj - j), opp(c)) + c;
        i = ni + 1;
        j = nj + 1;
    }
    res += s1.substr(i);
    cout << res + string(3 * n - res.size(), opp(c)) << '\n';
}

int main() {
    io();
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        cin >> n;
        array<string, 3> s;
        F0R(i, 3) cin >> s[i];
        if (valid(s[0], s[1])) construct(s[0], s[1]);
        else if (valid(s[0], s[2])) construct(s[0], s[2]);
        else construct(s[1], s[2]);
    }
}