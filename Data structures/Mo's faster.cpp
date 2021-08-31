#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast","unroll-loops","omit-frame-poller","inline","03")

#define all(x) (x).begin(), (x).end()


typedef long double ld;
typedef long long ll;
typedef pair <int, int> ii;
typedef __int128 LL;

int sq;

struct query {
    int a, b, id;
    query(int x = 0, int y = 0, int z = 0) : a(x), b(y), id(z) {}
    inline ii get() const {
        return make_pair(a / sq, ((a / sq) & 1) ? -b : +b);
    }
} ;

inline bool operator < (const query &a, const query &b) {
    return a.get() < b.get();
}

vector <query> mo;

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
    sq = sqrt(n);

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

    for(auto [l, r, p] : mo) {
        while(y < r)add(a[++y]);
        while(x > l)add(a[--x]);
        while(y > r)del(a[y--]);
        while(x < l)del(a[x++]);
        sol[p - 1] = v;
    }

    for(auto r : sol)
        cout << r << '\n';

    return 0;
}
