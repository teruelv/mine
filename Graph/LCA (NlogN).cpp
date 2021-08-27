void dfs(int x, int p) {
    lca[x][0] = p, lvl[x] = lvl[p] + 1;
    for(int i = 1; i <= LN; i++)
        lca[x][i] = lca[lca[x][i - 1]][i - 1];
    for(int to : ady[x])
        if(to != p)
            dfs(to, x);
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