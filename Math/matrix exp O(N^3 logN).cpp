
struct matrix {
    ll n, m[MAX][MAX];
    matrix(int N) {
        memset(m, 0, sizeof m);
        n = N;
    }
    void set_indentity() {
        memset(m, 0, sizeof m);
        for(int i = 1; i <= n; i++)m[i][i] = 1;
    }
    matrix operator * (const matrix &a) {
        assert(n == a.n);
        matrix c(n);
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                for(int k = 1; k <= n; k++) {
                    ll &aux = c.m[i][j];
                    aux += 1ll * m[i][k] * a.m[k][j] % mod;
                    if(aux >= mod)aux -= mod;
                }
        return c;
    }
} ;

matrix pot(matrix b, ll e) {
    matrix ret(b.n);
    ret.set_indentity();
    while(e > 0) {
        if(e & 1)
            ret = ret * b;
        b = b * b;
        e /= 2;
    }
    return ret;
}
