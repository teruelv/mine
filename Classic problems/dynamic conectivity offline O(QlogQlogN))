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

struct DSU_ROLLBACK {
    struct node {
        int p, id, sz;
        node(int P = 0, int ID = 0, int SZ = 1) : p(P), id(ID), sz(SZ) {}
    } ;
    int n, comps;
    vector <node> ds;
    stack <node> s;
    DSU_ROLLBACK(int sz) {
        n = comps = sz;
        ds.resize(n);
        for(int i = 0; i < n; i++)ds[i] = node(i, i);
    }
    int find(int k) {
        return ds[k].p == k ? k : find(ds[k].p);
    }
    void merge(int a, int b, bool save = 1) {
        a = find(a);
        b = find(b);
        if(a == b)return;
        if(ds[a].sz > ds[b].sz)
            swap(a, b);
        if(save) {
            s.push(ds[a]);
            s.push(ds[b]);
        }
        comps--;
        ds[a].p = b;
        ds[b].sz += ds[a].sz;
    }
    void persist() {
        s.push(node(-1, -1, -1));
    }
    void rollback() {
        while(s.size() && s.top().id != -1) {
            comps++;
            node x = s.top();
            ds[x.id] = x, s.pop();
            node y = s.top();
            ds[y.id] = y, s.pop();
        }
        s.pop();
    }
} ;

const int MAX = 3e5 + 5;

int Q[MAX];
vector <ii> st[4 * MAX];

void update(int x, int l, int r, int lo, int hi, ii p, DSU_ROLLBACK &ds) {
    if(lo > r || hi < l)
        return;
    if(lo <= l && r <= hi) {
        st[x].push_back(p);
        return;
    }
    int m = (l + r) >> 1;
    update(2 * x, l, m, lo, hi, p, ds);
    update(2 * x + 1, m + 1, r, lo, hi, p, ds);
}

void solve(int x, int l, int r, DSU_ROLLBACK &ds) {
    ds.persist();
    for(auto [u, v] : st[x])
        ds.merge(u, v);
    if(l == r) {
        if(Q[l])
            cout << ds.comps << '\n';
    } else {
        int m = (l + r) >> 1;
        solve(2 * x, l, m, ds);
        solve(2 * x + 1, m + 1, r, ds);
    }
    ds.rollback();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, x, y;
    cin >> n >> m;

    DSU_ROLLBACK ds(n);

    map <ii, int> p;

    for(int i = 1; i <= m; i++) {
        string op;
        cin >> op;
        if(op[0] == '?') {
            Q[i] = 1;
        } else {
            cin >> x >> y;
            x--, y--;
            if(x > y)swap(x, y);
            if(op[0] == '+') {
                p[ii(x, y)] = i;
            } else {
                int &id = p[ii(x, y)];
                update(1, 1, m, id, i, ii(x, y), ds);
                id = 0;
            }
        }
    }

    for(auto [x, y] : p) {
        if(y)
            update(1, 1, m, y, m, x, ds);
    }

    if(m)
        solve(1, 1, m, ds);

    return 0;
}
