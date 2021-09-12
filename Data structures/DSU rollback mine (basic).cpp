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
    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if(a == b)return;
        if(ds[a].sz > ds[b].sz)
            swap(a, b);
        s.push(ds[a]);
        s.push(ds[b]);
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
