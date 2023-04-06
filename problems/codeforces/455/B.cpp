#include <bits/stdc++.h>

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


struct trie {
    vector<array<ll, 26>> t = {{}};
    vi is_leaf{true};
    ll n = 0;

    void add(const string & s) {
        ll cur = 0;
        for (auto c : s) {
            is_leaf[cur] = false;
            ll i = c-'a';
            if (t[cur][i] == 0) {
                t[cur][i] = t.size();
                is_leaf.pb(true);
                t.pb({});
            }
            cur = t[cur][i];
        }
    }

    bool can_win(ll u=0) {
        F0R(i, 26) {
            if (t[u][i] > 0 && !can_win(t[u][i])) {
                return true;
            }
        }
        return false;
    }

    bool can_lose(ll u=0) {
        if (is_leaf[u]) {
            return true;
        }
        F0R(i, 26) {
            if (t[u][i] > 0 && !can_lose(t[u][i])) {
                return true;
            }
        }
        return false;
    }

};


void first() {
    cout << "First\n";
}

void second() {
    cout << "Second\n";
}

int main() {
    io();
    ll n, k;
    cin >> n >> k;
    ll m = k % 2;
    trie T;
    F0R(i, n) {
        string s;
        cin >> s;
        T.add(s);
    }
    bool first_wins = T.can_win();
    bool first_loses = T.can_lose();
    if (first_wins && first_loses) first();
    else if (first_wins && !first_loses) {
        if (m) first();
        else second();
    } else if (!first_wins && first_loses) {
        second();
    } else {
        second();
    }
}