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

template <typename T> T pot(T b, ll e) {
    T ret = 1;
    while(e) {
        if(e & 1)
            ret = ret * b;
        b = b * b;
        e /= 2;
    }
    return ret;
}

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

static int rnd(int lo, int hi) {
    return uniform_int_distribution <int> (lo, hi)(rng);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ;
}
