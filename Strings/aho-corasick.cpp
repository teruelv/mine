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

typedef long double ld;
typedef long long ll;

typedef pair <int, int> ii;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

static int rnd(int lo, int hi) {
    return uniform_int_distribution <int> (lo, hi)(rng);
}

const int MAX = 1e7 + 5;

struct node {
    unordered_map <int, int> next;
    int fail;
    vector <int> patterns;
} ;

vector <node> T;
unordered_map <int, vector <int>> G, who;
int dp[MAX], sol[MAX];

void Add(string s, int id) {
    int p = 0;
    for(char c : s) {
        if(!T[p].next.count(c)) {
            T[p].next[c] = T.size();
            T.push_back(node());
        }
        p = T[p].next[c];
    }
    who[p].push_back(id);
}

void build() {
    queue <int> q;
    for(auto [x, to] : T[0].next)
        q.push(to);
    while(!q.empty()) {
        int c = q.front();
        q.pop();
        for(auto [x, to] : T[c].next) {
            q.push(to);
            int f = T[c].fail;
            while(f && !T[f].next.count(x)) {
                f = T[f].fail;
            }
            T[to].fail = T[f].next[x];
            G[T[to].fail].push_back(to);
        }
    }
}

void solve(string t) {
    int p = 0;
    for(char c : t) {
        while(p && !T[p].next.count(c))
            p = T[p].fail;
        dp[p = T[p].next[c]]++;
    }
}

int mark[MAX];

int dfs(int x) {
    if(mark[x])
        return dp[x];
    mark[x] = 1;
    for(int to : G[x])
        dp[x] += dfs(to);
    for(int c : who[x])
        sol[c] = dp[x];
    return dp[x];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    string t;

    cin >> t >> n;

    T.push_back(node());

    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        Add(s, i);
    }

    build();
    solve(t);

    for(int i = 0; i < T.size(); i++)
        dfs(i);

    for(int i = 1; i <= n; i++)
        cout << sol[i] << '\n';

    return 0;
}
