struct STP { // persistent segment tree
    vector <int> st, l, r, rt;
    int N;
    STP(int size) {
        N = size;
        rt.push_back(0);
        build(1, N);
    }
    inline void push() {
        l.push_back(0);
        r.push_back(0);
        st.push_back(0);
    }
    int build(int L, int R) {
        int p = size();
        push();
        if(L != R) {
            int m = (L + R) >> 1;
            l[p] = size();
            build(L, m);
            r[p] = size();
            build(m + 1, R);
        }
        return size() - 1;
    }
    void copy(int x, int y) {
        st[y] = st[x];
        l[y] = l[x];
        r[y] = r[x];
    }
    void update(int p, int x, int L, int R, int v) {
        push();
        copy(p, x);
        st[x]++;
        if(L == R)return;
        int m = (L + R) >> 1;
        if(v <= m)
            update(l[p], l[x] = size(), L, m, v);
        else
            update(r[p], r[x] = size(), m + 1, R, v);
    }
    int query(int p, int x, int L, int R, int v) {
        if(L == R)
            return st[x] - st[p];
        int m = (L + R) >> 1;
        if(v <= m)
            return query(l[p], l[x], L, m, v);
        return query(r[p], r[x], m + 1, R, v);
    }
    int ask(int pre, int nxt, int v) {
        return query(rt[pre - 1], rt[nxt], 1, N, v);
    }
    void add(int v) {
        int tam = rt.size();
        rt.push_back(size());
        update(rt[tam - 1], rt[tam], 1, N, v);
    }
    inline int size() {
        return st.size();
    }
} ;
