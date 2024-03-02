struct Graph {
    int n, rt, LN = 20, m;
    vector <vector <tri>> ady;
    vector <vector <int>> lca;
    vector <int> d1, d2, p, lvl, inv;
    set <int> s;
    Graph(int sz = 0, int edg = 0) {
        n = sz, m = edg;
        ady.resize(n + 1);
        p.resize(n + 1, -1);
        d1.resize(n + 1);
        d2.resize(n + 1);
        lvl.resize(n + 1);
        inv.resize(m + 1);
        lca.resize(n + 1, vector <int> (LN + 2, 0));
    }
    void SP(int r) {
        priority_queue <ii> pq;
        pq.push({0, r});
        d1[r] = 0;
        while(!pq.empty()) {
            auto [w, x] = pq.top();
            pq.pop();
            w = -w;
            if(w != d1[x])continue;
            for(auto [to, c, id] : ady[x])
                if(d1[to] == -1 || d1[to] > w + c) {
                    d1[to] = w + c;
                    p[to] = id;
                    inv[id] = to;
                    pq.push({-d1[to], to});
                }
        }
        for(int i = 1; i <= n; i++)
            if(i != r)
                s.insert(p[i]);
    }
    int query(int u, int v) {
        if(lvl[u] > lvl[v])
            swap(u, v);
        for(int i = LN; i >= 0; i--)
            if(lvl[v] - (1 << i) >= lvl[u])
                v = lca[v][i];
        if(u == v)
            return u;
        for(int i = LN - 1; i >= 0; i--) {
            if(lca[u][i] != lca[v][i]) {
                u = lca[u][i];
                v = lca[v][i];
            }
        }
        return lca[u][0];
    }
    void dfs(int x, int pre = 0) {
        lca[x][0] = pre, lvl[x] = lvl[pre] + 1;
        for(int i = 1; i <= LN; i++)
            lca[x][i] = lca[lca[x][i - 1]][i - 1];
        for(auto [to, c, id] : ady[x]) {
            if(p[to] == id) {
                dfs(to, x);
                int dd = d2[to] + c;
                if(d2[to] != -1)
                    if(d2[x] == -1 || d2[x] > dd)
                        d2[x] = dd;
            } else if(to != pre) {
                int dd = d1[to] + c;
                if(d2[x] == -1 || d2[x] > dd)
                    d2[x] = dd;
            }
        }
    }
    ll AskD(int x, int e) {
        if(!s.count(e))
            return d1[x];
        int v = inv[e], anc;
        anc = query(x, v);
        if(anc != v)
            return d1[x];
        if(d2[v] == -1)
            return -1;
        return d2[v] + d1[x] - d1[v];
    }
    void Print() {
        for(int i = 1; i <= n; i++)cout << d1[i] << " \n"[i==n];
        for(int i = 1; i <= n; i++)cout << d2[i] << " \n"[i==n];
    }
    void Work(int r) {
        rt = r;
        for(int i = 1; i <= n; i++)
            d1[i] = d2[i] = -1;
        SP(rt);
        d2[rt] = 0;
        dfs(rt);
    }
} ;
