struct SEGMENT_TREE {   // O(~3*QlogMAX) tiempo y memoria
    struct node {
        ii v, lz;
        int l, r;
        node() {}
        node(int x, int y, ii a, ii b) : l(x), r(y), v(a), lz(b)  {}
    } ;
    vector <node> st;
    int n, sz;
    void add() {
        st.push_back(node(0, 0, {0, 0}, {0, 0}));
        sz++;
    }
    SEGMENT_TREE(int N) {
        n = N, sz = -1;
        add();
        add();
    }
    ii ask(ii &a, ii &b) {
        return a > b ? a : b;
    }
    void push(int x, ii v) {
        if(!x)return;
        st[x].v = ask(st[x].v, v);
        st[x].lz = ask(st[x].lz, v);
    }
    int check(int x) {
        if(!x) {
            add();
            return sz;
        }
        return x;
    }
    ii query(int x, int l, int r, int lo, int hi) {
        if(lo > r || hi < l)
            return ii(0, 0);
        if(lo <= l && r <= hi) {
            return st[x].v;
        }
        int L = check(st[x].l);
        int R = check(st[x].r);
        if(st[x].lz.first) {
            push(L, st[x].lz);
            push(R, st[x].lz);
            st[x].lz = ii(0, 0);
        }
        int m = (l + r) >> 1;
        ii v1 = query(L, l, m, lo, hi);
        ii v2 = query(R, m + 1, r, lo, hi);
        st[x].l = L, st[x].r = R;
        return ask(v1, v2);
    }
    void update(int x, int l, int r, int lo, int hi, ii v) {
        if(lo > r || hi < l)
            return;
        if(lo <= l && r <= hi) {
            push(x, v);
            return;
        }
        int L = check(st[x].l);
        int R = check(st[x].r);
        if(st[x].lz.first) {
            push(L, st[x].lz);
            push(R, st[x].lz);
            st[x].lz = ii(0, 0);
        }
        int m = (l + r) >> 1;
        update(L, l, m, lo, hi, v);
        update(R, m + 1, r, lo, hi, v);
        st[x].l = L, st[x].r = R;
        st[x].v = ask(st[L].v, st[R].v);
    }
    ii get(int x, int y) {
        return query(1, 1, n, x, y);
    }
    void put(int x, int y, ii v) {
        update(1, 1, n, x, y, v);
    }
} ;
