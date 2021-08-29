struct STP { // persistent segment tree
    struct node {
        int v, l, r;
        node(int a = 0, int b = 0, int c = 0) : v(a), l(b), r(c) {}
    } ;
    vector <node> st;
    vector <int> rt;
    int N, sz;
    STP(int size) {
        N = size, sz = 0;
        rt.push_back(0);
        build(1, N);
    }
    inline void push() {
        sz++;
        st.push_back(node(0, 0, 0));
    }
    void build(int L, int R) {
        int p = sz;
        push();
        if(L != R) {
            int m = (L + R) >> 1;
            st[p].l = sz;
            build(L, m);
            st[p].r = sz;
            build(m + 1, R);
        }
    }
    void copy(int x, int y) {
        st[y] = st[x];
    }
    void update(int p, int x, int L, int R, int v) {
        push();
        copy(p, x);
        st[x].v++;
        if(L == R)return;
        int m = (L + R) >> 1;
        if(v <= m)
            update(st[p].l, st[x].l = sz, L, m, v);
        else
            update(st[p].r, st[x].r = sz, m + 1, R, v);
    }
    int query(int p, int x, int L, int R, int v) {   // freq(v)
        if(L == R)
            return st[x].v - st[p].v;
        int m = (L + R) >> 1;
        if(v <= m)
            return query(st[p].l, st[x].l, L, m, v);
        return query(st[p].r, st[x].r, m + 1, R, v);
    }
    int Kth(int p, int x, int L, int R, int kth) {
        if(L == R)return L;
        int m = (L + R) >> 1;
        int izq = st[st[x].l].v - st[st[p].l].v;
        if(izq >= kth)
            return Kth(st[p].l, st[x].l, L, m, kth);
        return Kth(st[p].r, st[x].r, m + 1, R, kth - izq);
    }
    int ask(int pre, int nxt, int v) {
        return Kth(rt[pre - 1], rt[nxt], 1, N, v);
    }
    void add(int v) {
        int tam = rt.size();
        rt.push_back(sz);
        update(rt[tam - 1], rt[tam], 1, N, v);
    }
    inline int size() {
        return sz;
    }
} ;
