
typedef tuple <int, int, int, int> Edge;

int N, h[MAX], pre[MAX], best[MAX];

vector<int> ady[MAX];
vector<Edge> E;

void init() {
    E.clear();
    for(int i = 0; i < MAX; i++) {
        ady[i].clear();
    }
}

void AddEdge(int u, int v, int cap, int cost) {
    ady[u].push_back(E.size());
    E.push_back(Edge(u, v, cap, cost));
    ady[v].push_back(E.size());
    E.push_back(Edge(v, u, 0, -cost));
}

void bellman_ford(int s) {
    memset(h, 127, sizeof h);
    h[s] = 0;
    for(int i = 0; i <= N; i++) {
        for(auto e : E) {
            int u, v, f, c;
            tie(u, v, f, c) = e;
            if(f > 0) h[v] = min(h[v], h[u] + c);
        }
    }
}

bool dijsktra(int s, int t) {
    memset(pre, -1, sizeof pre);
    memset(best, 127, sizeof best);
    pre[s] = -2;
    best[s] = 0;
    priority_queue< pair<int, int> > cola;
    cola.push(make_pair(0, s));
    while(!cola.empty()) {
        int u, w;
        tie(w, u) = cola.top();
        cola.pop();
        if(best[u] < -w) continue;
        for(auto e : ady[u]) {
            int u, v, f, c;
            tie(u, v, f, c) = E[e];
            int cost = best[u] + h[u] - h[v] + c;
            if(f > 0 && cost < best[v]) {
                best[v] = cost;
                pre[v] = e;
                cola.push(make_pair(-best[v], v));
            }
        }
    }
    return pre[t] != -1;
}

pair<int, int> maxFlow(int s, int t) {
    int ans_flow = 0, ans_cost = 0;
    bellman_ford(s);
    while(dijsktra(s, t)) {
        for(int i = 0; i <= N; i++) {
            if(best[i] == oo)  h[i] = oo;
            else if(h[i] < oo) h[i] += best[i];
        }
        int flow = oo;
        for(int v, idx = pre[t]; idx >= 0; v = get<0>(E[idx]), idx = pre[v]) {
            int cap = get<2>(E[idx]);
            flow = min(flow, cap);
        }
        for(int v, idx = pre[t]; idx >= 0; v = get<0>(E[idx]), idx = pre[v]) {
            int cost = get<3>(E[idx]);
            get<2>(E[idx]) -= flow;
            get<2>(E[idx ^ 1]) += flow;
            ans_cost += flow * cost;
        }
        ans_flow += flow;
    }
    return make_pair(ans_flow, ans_cost);
}
