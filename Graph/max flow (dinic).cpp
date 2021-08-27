#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef long long ll;
typedef pair <ll, ll> ii;

//const ll MAX = 205;
const ll MAX = 1e5 + 5;
const ll mod = 1e9 + 7;
const ll oo = 1e9;

// edges are added twice so MAX *= 2

struct Edge {
    ll to, rev;
    ll f, cap;
    Edge(ll to, ll rev, ll f, ll cap): to(to), rev(rev), f(f), cap(cap) {}
};

ll dist[MAX], q[MAX], work[MAX];
vector<Edge> ady[MAX];

ll src, dst;
void reset() {
    for(ll i = 0; i < MAX; i++) {
        ady[i].clear();
    }
}

void AddEdge(ll s, ll t, ll cap, ll rcap = 0) {
    ady[s].push_back(Edge(t, ady[t].size(), 0, cap));
    ady[t].push_back(Edge(s, ady[s].size() - 1, 0, rcap));
}

bool dinic_bfs() {
    memset(dist, -1, sizeof dist);
    dist[src] = 0;
    ll qt = 0;
    q[ qt++ ] = src;
    for(ll qh = 0; qh < qt; qh++) {
        ll u = q[qh];
        for(auto e : ady[u]) {
            ll v = e.to;
            if(dist[v] < 0 && e.f < e.cap) {
                dist[v] = dist[u] + 1;
                q[qt++] = v;
            }
        }
    }
    return dist[dst] >= 0;
}

ll dinic_dfs(ll u, ll f) {
    if(u == dst) return f;
    for(ll& i = work[u]; i < ady[u].size(); i++) {
        Edge &e = ady[u][i];
        if(e.cap <= e.f)continue;
        ll v = e.to;
        if(dist[v] == dist[u] + 1) {
            ll df = dinic_dfs(v, min(f, e.cap - e.f));
            if(df > 0) {
                e.f += df;
                ady[v][e.rev].f -= df;
                return df;
            }
        }
    }
    return 0;
}

ll maxFlow(ll _src, ll _dst) {
    src = _src;
    dst = _dst;
    ll result = 0;
    while(dinic_bfs()) {
        memset(work, 0, sizeof work);
        while(ll delta = dinic_dfs(src, oo)) {
            result += delta;
        }
    }
    return result;
}

///
ll n, m, a, b, c;

int main() {
    //    freopen("asd.in", "r", stdin);

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    while(m--) {
        cin >> a >> b >> c;
        AddEdge(a, b, c);
        AddEdge(b, a, c);
    }

    cout << maxFlow(1, n) << '\n';
}
