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

ll nt;
ll ns;

bool is_possible(const string & s, const string & t) {
    set<char> chars(all(s));
    return all_of(all(t), [&](char c) -> bool { return chars.count(c) == 1; });
}

auto build(const string &s, const string & t) {
    vvi lcp(nt+1, vi(ns+1));
    R0F(i, nt) {
        R0F(j, ns) {
            if (t[i] == s[j]) {
                lcp[i][j] = lcp[i+1][j+1] + 1;
            }
        }
    }
    vvi lcpr(nt+1, vi(ns+1));
    R0F(i, nt) {
        F0R(j, ns) {
            if (t[i] == s[j]) {
                lcpr[i][j+1] = lcpr[i+1][j] + 1;
            }
        }
    }
    vector<tuple<ll, ll, bool>> res; // l, sj, rev?
    F0R(i, nt) {
        auto m = max_element(all(lcp[i]));
        auto mr = max_element(all(lcpr[i]));
        if (*m > *mr) {
            res.eb(*m, m - lcp[i].begin(), false);
        } else {
            res.eb(*mr, mr - lcpr[i].begin() - *mr, true);
        }
    }
    return res;
}

int main() {
    io();
    string s, t;
    cin >> s >> t;
    nt = t.size();
    ns = s.size();
    if (!is_possible(s, t)) {
        cout << "-1\n";
        return 0;
    }
    auto lcp = build(s, t);
    vi dp(nt + 1, M);
    dp[0] = 0;
    vector<pair<ll, ii>> r(nt+1);
    F0R(i, nt) {
        auto [l, si, rev] = lcp[i];
        FOR(j, i, min(i+l, nt)) {
            if (dp[j+1] > dp[i] + 1) {
                dp[j+1] = dp[i] + 1;
                if (rev) r[j+1] = {j-i+1, {si+l-1,si+l-1-(j-i)}};
                else r[j+1] = {j-i+1, {si, si+j-i}};
            }
        }
    }
    vii res;
    for (ll i = nt; i>0; i-=r[i].first) {
        res.pb(r[i].second);
    }
    reverse(all(res));
    cout << res.size() << '\n';
    for (auto [i, j]: res) {
        cout << i+1 << ' ' << j+1 << '\n';
    }
}