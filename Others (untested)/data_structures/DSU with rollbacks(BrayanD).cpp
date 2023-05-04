struct DSU_WITH_ROLLBACKS
{
    struct dsu_save
    {
        int u, urank, v, vrank, comps;
        bool bipart;
    };

    stack<dsu_save> op;

    vector<int> rnk;
    vector<bool> col;
    bool bipartite;
    int comps;

    DSU_WITH_ROLLBACKS()
    {

    }

    DSU_WITH_ROLLBACKS(int N)
    {
        init(N);
    }

    void init(int N)
    {
        rnk.clear();
        col.clear();
        while(!op.empty())op.pop();
        rnk.resize(N);
        col.resize(N);
        for(int i = 0 ; i < N ; i++)
        {
            rnk[i] = 1;
            col[i] = false;
        }
        bipartite = true;
        comps = N;
    }

    pair<int,bool> find(int x)
    {
        if(rnk[x] > 0)return {x, col[x]};
        pair<int,bool> tp = find(-rnk[x]);
        tp.second ^= col[x];
        return tp;
    }

    void join(int a, int b)
    {
        pair<int,bool> ta = find(a), tb = find(b);
        a = ta.first;
        b = tb.first;
        op.push({a, rnk[a], b, rnk[b], comps, bipartite});
        if(a == b)
        {
            if(ta.second == tb.second)bipartite = false;
            return;
        }
        comps--;
        if(rnk[a] < rnk[b])swap(a,b);
        rnk[a] += rnk[b];
        rnk[b] = -a;
        col[b] = col[b]^(ta.second == tb.second);
    }

    void rollback()
    {
        if(op.empty())return;
        dsu_save x = op.top();
        op.pop();
        comps = x.comps;
        bipartite = x.bipart;
        rnk[x.u] = x.urank;
        col[x.u] = false;
        rnk[x.v] = x.vrank;
        col[x.v] = false;
    }
};
