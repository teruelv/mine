#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#ifdef ONLINE_JUDGE
#pragma GCC optimize("Ofast","unroint-loops","omit-frame-pointer","inline","03")
#endif // ONLINE_JUDGE

#define all(x) (x).begin(), (x).end()
#define uni(x) (x).erase(unique(all(x)), (x).end())
#define rnk(x, y) upper_bound(all((x)), (y)) - (x).begin()

typedef long double ld;
typedef long long ll;
typedef pair <int, int> ii;
typedef __int128 LL;

ll pot(ll b, ll e, ll mod) {
    ll ret = 1;
    while(e) {
        if(e & 1)
            ret = ret * b % mod;
        b = b * b % mod;
        e /= 2;
    }
    return ret;
}

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

static int rnd(int lo, int hi) {
    return uniform_int_distribution <int> (lo, hi)(rng);
}

template<typename T>
T min_assignment(const vector<vector<T>> &c) {
    const int n = c.size(), m = c[0].size(); // assert(n <= m);
    vector<T> v(m), dist(m); // v: potential
    vector<int> matchL(n, -1), matchR(m, -1); // matching pairs
    vector<int> index(m), prev(m);

    iota(all(index), 0);

    auto residue = [&](int i, int j) {
        return c[i][j] - v[j];
    };

    for(int f = 0; f < n; ++f) {
        for(int j = 0; j < m; ++j) {
            dist[j] = residue(f, j);
            prev[j] = f;
        }
        T w;
        int j, l;
        for(int s = 0, t = 0;;) {
            if(s == t) {
                l = s;
                w = dist[index[t++]];
                for(int k = t; k < m; ++k) {
                    j = index[k];
                    T h = dist[j];
                    if(h <= w) {
                        if(h < w) {
                            t = s;
                            w = h;
                        }
                        index[k] = index[t];
                        index[t++] = j;
                    }
                }
                for(int k = s; k < t; ++k) {
                    j = index[k];
                    if(matchR[j] < 0)
                        goto aug;
                }
            }
            int q = index[s++], i = matchR[q];
            for(int k = t; k < m; ++k) {
                j = index[k];
                T h = residue(i, j) - residue(i, q) + w;
                if(h < dist[j]) {
                    dist[j] = h;
                    prev[j] = i;
                    if(h == w) {
                        if(matchR[j] < 0)
                            goto aug;
                        index[k] = index[t];
                        index[t++] = j;
                    }
                }
            }
        }
aug:
        for(int k = 0; k < l; ++k)
            v[index[k]] += dist[index[k]] - w;
        int i;
        do {
            matchR[j] = i = prev[j];
            swap(j, matchL[i]);
        } while(i != f);
    }
    T opt = 0;
    for(int i = 0; i < n; ++i)
        opt += c[i][matchL[i]]; // (i, matchL[i]) is a solution
    return opt;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while(t--) {
        int n, m;
        cin >> n >> m;
        int flip = n > m;
        if(flip)swap(n, m);
        int a, b, c;
        vector <vector <int>> v(n, vector <int> (m, 0));
        while(cin >> a >> b >> c && a) {
            if(flip)swap(a, b);
            v[a - 1][b - 1] = -c;
        }
        cout << -min_assignment <int> (v) << '\n';
    }
}
