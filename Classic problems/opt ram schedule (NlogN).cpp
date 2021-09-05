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

const int MAX = 1e5 + 5;

int t, n, k, a[MAX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;

    while(t--) {
        cin >> n >> k;
        vector <int> b;
        for(int i = 1; i <= n; i++)cin >> a[i], b.emplace_back(a[i]);
        sort(all(b));
        uni(b);
        int m = b.size();
        vector <queue <int>> pos(m + 1);
        for(int i = 1; i <= n; i++) {
            a[i] = rnk(b, a[i]);
            pos[a[i]].push(i);
        }
        for(int i = 1; i <= m; i++)
            pos[i].push(n + 1);
        int sol = 0;
        set <int> s;
        set <ii, greater <ii>> pq;
        for(int i = 1; i <= n; i++) {
            int v = a[i];
            pos[v].pop();
            if(s.find(v) != s.end()) {
                auto it = pq.find(ii(i, v));
                if(it != pq.end())
                    pq.erase(it);
                pq.insert(ii(pos[v].front(), v));
                continue;
            }
            sol++;
            if(s.size() >= k) {
                auto [p, x] = *pq.begin();
                s.erase(s.find(x));
                pq.erase(pq.find(ii(pos[x].front(), x)));
            }
            s.insert(v);
            pq.insert(ii(pos[v].front(), v));
        }
        cout << sol << "\n";
    }

    return 0;
}
