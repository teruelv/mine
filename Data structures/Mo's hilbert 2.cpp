#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast","unroll-loops","omit-frame-poller","inline","03")

#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef long double ld;
typedef __int128 LL;

const int logn = 21; // 2^logn >= n!!!
const int maxn = 1 << logn; // 2^logn >= n!!!

ll Hilbert(int x, int y) {
    ll d = 0;
    for(int s = 1 << (logn - 1); s; s >>= 1) {
        bool rx = x & s, ry = y & s;
        d = d << 2 | rx * 3 ^ static_cast<int>(ry);
        if(!ry) {
            if(rx) {
                x = maxn - x;
                y = maxn - y;
            }
            swap(x, y);
        }
    }
    return d;
}

struct Query {
    int a, b, id;
    ll ord;
    Query(int x = 0, int y = 0, int z = 0) : a(x), b(y), id(z) {
        ord = Hilbert(x, y);
    }
    bool operator < (const Query &a) const {
        return ord < a.ord;
    }
} ;

vector <Query> mo;

int n, q, x, y;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> q;

    vector <int> a(n + 1);
    vector <ll> sol(q);

    for(int i = 1; i <= n; i++)
        cin >> a[i];

    vector <int> c(*max_element(all(a)) + 1);

    for(int i = 1; i <= q; i++) {
        cin >> x >> y;
        mo.push_back(query(x, y, i));
    }

    sort(all(mo));

    ll v = 0;

    auto add = [&](ll z) {
        v += z * (2 * ++c[z] - 1);
    } ;
    auto del = [&](ll z) {
        v -= z * (2 * c[z]-- - 1);
    };

    x = 1, y = 0;

    for(auto [l, r, p, z] : mo) {
        while(y < r)
            add(a[++y]);
        while(y > r)
            del(a[y--]);
        while(x > l)
            add(a[--x]);
        while(x < l)
            del(a[x++]);
        sol[p - 1] = v;
    }

    for(auto r : sol)
        cout << r << '\n';

    return 0;
}
