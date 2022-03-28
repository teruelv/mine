#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#ifdef ONLINE_JUDGE
#pragma GCC oPimize("Ofast","unroint-loops","omit-frame-pointer","inline","03")
#endif // ONLINE_JUDGE

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uni(x) (x).erase(unique(all(x)), (x).end())
#define rnk(x, y) upper_bound(all((x)), (y)) - (x).begin()

template <class T = int> using ii = pair <T, T>;
template <class T = int> using tri = tuple <T, T, T>;

typedef long double ld;
typedef long long ll;
//typedef __int128 LL;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

static int rnd(int lo, int hi) {
    return uniform_int_distribution <int> (lo, hi)(rng);
}

const ld eps = 1e-9;
const int oo = 1e18;

const int MAX = 1e5 + 5;
const int mod = 998244353;

struct SuffixArray {
    vector <int> sa, lcp, pos;
    SuffixArray(string &s, int lim = 256) {
        int n = s.size() + 1, k = 0, a, b;
        vector <int> x(all(s) + 1), y(n), ws(max(n, lim));
        sa = lcp = pos = y, iota(all(sa), 0);
        for(int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j, iota(all(y), n - j);
            for(int i = 0; i < n; i++)
                if(sa[i] >= j)
                    y[p++] = sa[i] - j;
            fill(all(ws), 0);
            for(int i = 0; i < n; i++)
                ws[x[i]]++;
            for(int i = 1; i < lim; i++) ws[i] += ws[i - 1];
            for(int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            for(int i = 1; i < n; i++) {
                a = sa[i - 1], b = sa[i];
                x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
            }
        }
        for(int i = 1; i < n; i++)
            pos[sa[i]] = i;
        for(int i = 0, j; i < n - 1; lcp[pos[i++]] = k)
            for(k && k--, j = sa[pos[i] - 1];
                    s[i + k] == s[j + k]; k++);
    }
} ;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;

    SuffixArray SA(s);

    int n = s.size();

    for(int i = 1; i <= n; i++) {
        cout << SA.lcp[i] << ' ';
        cout << s.substr(SA.sa[i], 1e9) << '\n';
    }

    return 0;
}
