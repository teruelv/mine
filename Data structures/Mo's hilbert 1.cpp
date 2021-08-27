#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast","unroll-loops","omit-frame-poller","inline","03")

#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef long double ld;
typedef __int128 LL;

inline int64_t Hilbert(int x, int y, int pow, int Rotate) { //2 ^ pow >= n
    if(pow == 0)
        return 0;
    int hpow = 1 << (pow - 1);
    int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
    seg = (seg + Rotate) & 3;
    const int RotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (Rotate + RotateDelta[seg]) & 3;
    int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
    int64_t ans = seg * subSquareSize;
    int64_t add = Hilbert(nx, ny, pow - 1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ans;
}

int sq;

struct query {
    int a, b, id;
    ll ord;
    query(int x = 0, int y = 0, int z = 0) : a(x), b(y), id(z) {
        ord = Hilbert(x, y, 21, 0); // 2 ^ pow >= n !!!!
    }
} ;

inline bool operator < (const query &a, const query &b) {
    return a.ord < b.ord;
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