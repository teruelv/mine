#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast","unroll-loops","omit-frame-poller","inline","03")

#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef long double ld;
typedef __int128 LL;

int sq;

struct Query {
    int a, b, id;
    Query(int x = 0, int y = 0, int z = 0) : a(x), b(y), id(z) {}
    bool operator < (const Query &q) const {
        if(a / sq != q.a / sq)
            return a / sq < q.a / sq;
        return b < q.b;
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

    for(int i = 1; i <= q; i++) {
        cin >> x >> y;
        mo.push_back(query(x, y, i));
    }

    vector <int> c(*max_element(all(a)) + 1);

    sq = sqrt(n);
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
        while(y < r)
            add(a[++y]);
        while(y > r)
            del(a[y--]);
        while(x > l)
            add(a[--x]);
        while(x < l)
            del(a[x++]);
        sol[p-1] = v;
    }

    for(auto r : sol)
        cout << r << '\n';

    return 0;
}
