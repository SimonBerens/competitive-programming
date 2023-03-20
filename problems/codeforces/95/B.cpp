#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
template<typename K> using hset = gp_hash_table<K, null_type>;
template<typename K, typename V> using hmap = gp_hash_table<K, V>;


using namespace std;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define eb emplace_back

template<typename T>
void smin(T &x, T y) {
    x = min(x, y);
}

template<typename T>
void smax(T &x, T y) {
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

string balance(int l, int d) {
    // fours + sevens = l;
    // sevens = fours + d;
    int fours = (l - d) / 2;
    int sevens = fours + d;
    return string(fours, '4') + string(sevens, '7');
}

int main() {
    io();
    string s;
    cin >> s;
    int n = s.size();
    if (n % 2 == 1) {
        cout << balance(n + 1, 0) << '\n';
        return 0;
    }
    int valid_until = n;
    F0R(i, n) {
        if (s[i] != '4' && s[i] != '7') {
            valid_until = i;
            break;
        }
    }
    vi pd(n + 1);
    F0R(i, n) {
        pd[i + 1] = pd[i] + (s[i] == '4' ? 1 : -1);
    }
    if (valid_until == n) {
        if (pd[n] == 0) {
            cout << s << '\n';
            return 0;
        } else {
            valid_until = n - 1;
        }
    }
    R0F(i, valid_until + 1) {
        int n_changeable = n - i;
        if (s[i] < '4' && abs(pd[i]) <= n_changeable) {
            cout << s.substr(0, i) + balance(n_changeable, pd[i]) << '\n';
            return 0;
        } else if (s[i] < '7' && abs(pd[i] - 1) <= n_changeable - 1) {
            cout << s.substr(0, i) + '7' + balance(n_changeable-1, pd[i] -1) << '\n';
            return 0;
        }
    }
    cout << balance(n + 2, 0) << '\n';

}