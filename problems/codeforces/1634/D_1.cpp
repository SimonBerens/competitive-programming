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

ll query(ll i, ll j, ll k) {
    cout << "? " << i + 1 << ' ' << j + 1 << ' ' << k + 1 << endl;
    ll res;
    cin >> res;
    return res;
}

void submit(ll i, ll j) {
    cout << "! " << i + 1 << ' ' << j + 1 << endl;
}

vi solve_4(const vi & v) {
    vii qs;
    for (ll i : v) {
        set<ll> s(all(v));
        s.erase(i);
        vi t(all(s));
        ll r = query(t[0], t[1], t[2]);
        qs.pb({r, i});
    }
    sort(all(qs));
    return {qs[0][1], qs[1][1]};
}

int main() {
    io();
    int t;
    cin >> t;
    for (int test_no = 0; test_no < t; ++test_no) {
        ll n;
        cin >> n;
        vi pile({0, 1});
        for (ll i = 2; i + 1 < n; i += 2) {
            pile.pb(i);
            pile.pb(i+1);
            pile = solve_4(pile);
        }
        if (n%2) {
            pile.pb(n-1);
            F0R(i, 4) {
                bool found = false;
                F0R(j, 3) {
                    if (pile[j] == i) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    pile.pb(i);
                    break;
                }
            }
            pile = solve_4(pile);
        }
        submit(pile[0], pile[1]);
    }
}