/*
Knapsack: Can you form K by adding some subset of A? (without repetition)
Sum(Ai) <= ~2e5, maybe a bit more
Can answer multiple querys
*/


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

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

static int rnd(int lo, int hi) {
    return uniform_int_distribution <int> (lo, hi)(rng);
}

typedef long double ld;
typedef long long ll;
typedef pair <int, int> ii;
typedef __int128 LL;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;

    cin >> n >> k;

    map <int, int> m;

    while(n--) {
        int x;
        cin >> x;
        m[x]++;
    }

    vector <ii> v;
    for(auto [x, y] : m) {
        v.push_back(ii(x, y));
    }
    m.clear();

    bitset <200002> dp;
    dp[0] = 1;

    for(auto [x, y] : v) {
        if(y == 1) {
            dp |= dp << x;
        } else {
            int lg = __lg((y + 1) / 2);
            int s = (1 << (lg + 1)) - 1;
            dp |= dp << (x * (y - s));
            lg = 1 << lg;
            while(lg) {
                dp |= dp << (x * lg);
                lg >>= 1;
            }
        }
        if(dp[k]) {
            cout << "YES\n";
            return 0;
        }
    }

    cout << "NO\n";
    return 0;
}
