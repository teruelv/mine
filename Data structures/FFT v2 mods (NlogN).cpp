namespace FFT {
struct cd {
    ld x, y;

    cd(ld _x = 0, ld _y = 0) : x(_x), y(_y) {}

    inline cd operator + (const cd &c) const {
        return cd(x + c.x, y + c.y);
    }
    inline cd operator - (const cd &c) const {
        return cd(x - c.x, y - c.y);
    }
    inline cd operator * (const cd &c) const {
        return cd(x * c.x - y * c.y, x * c.y + y * c.x);
    }
    inline cd conj() const {
        return cd(x, -y);
    }
};

const static int maxk = 21, maxn = (1 << maxk) + 1;
cd ws[maxn];
int dp[maxn];
cd rs[maxn];
int n, k;
int lastk = -1;

void fft(vector <cd> &a, bool torev = 0) {
    if(lastk != k) {
        lastk = k;
        dp[0] = 0;

        for(int i = 1, g = -1; i < n; ++i) {
            if(!(i & (i - 1))) {
                ++g;
            }
            dp[i] = dp[i ^ (1 << g)] ^ (1 << (k - 1 - g));
        }

        ws[1] = cd(1, 0);
        for(int two = 0; two < k - 1; ++two) {
            ld alf = pi / n * (1 << (k - 1 - two));
            cd cur = cd(cos(alf), sin(alf));

            int p2 = (1 << two), p3 = p2 * 2;
            for(int j = p2; j < p3; ++j) {
                ws[j * 2 + 1] = (ws[j * 2] = ws[j]) * cur;
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        if(i < dp[i]) {
            swap(a[i], a[dp[i]]);
        }
    }
    if(torev) {
        for(int i = 0; i < n; ++i) {
            a[i].y = -a[i].y;
        }
    }
    for(int len = 1; len < n; len <<= 1) {
        for(int i = 0; i < n; i += len) {
            int wit = len;
            for(int it = 0, j = i + len; it < len; ++it, ++i, ++j) {
                cd tmp = a[j] * ws[wit++];
                a[j] = a[i] - tmp;
                a[i] = a[i] + tmp;
            }
        }
    }
}

vector <ll> mult(vector <ll> &A, vector <ll> &B) {
    int na = A.size(), nb = B.size();
    if(!na || !nb) {
        return { 0 };
    }
    vector <ll> ans;
    for(k = 0, n = 1; n < na + nb - 1; n <<= 1, ++k) ;
    assert(n < maxn);
    vector <cd> a(n);
    for(int i = 0; i < n; ++i) {
        a[i] = cd(i < na ? A[i] : 0, i < nb ? B[i] : 0);
    }
    fft(a);
    a[n] = a[0];
    for(int i = 0; i <= n - i; ++i) {
        a[i] = (a[i] * a[i] - (a[n - i] * a[n - i]).conj()) * cd(0, (ld) - 1 / n / 4);
        a[n - i] = a[i].conj();
    }
    fft(a, 1);
    for(int i = 0; i < n; ++i) {
        ll val = (ll) round(a[i].x);
        assert(abs(val - a[i].x) < 1e-1);
        if(val) {
            assert(i < na + nb - 1);
            while(ans.size() < i)
                ans.push_back(0);
            ans.push_back(val);
        }
    }
    return ans;
}
};