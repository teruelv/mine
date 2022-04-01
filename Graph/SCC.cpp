//SCC

// ady a -> b, inv b -> a
vector <int> ady[MAX], inv[MAX];
stack <int> st;
int n, SCC, scc[MAX];
void dfs(int u) {
    scc[u] = 1;
    for(int to : ady[u])
        if(!scc[to])
            dfs(to);
    st.push(u);
}
void dfsR(int u, int id) {
    scc[u] = id;
    for(int to : inv[u])
        if(!scc[to])
            dfsR(to, id);
}
void Go() {
    for(int i = 0; i < n; i++)
        if(!scc[i])
            dfs(i);
    memset(scc, 0, sizeof scc);
    while(!st.empty()) {
        int top = st.top();
        st.pop();
        if(!scc[top])
            dfsR(top, ++SCC);
    }
}
