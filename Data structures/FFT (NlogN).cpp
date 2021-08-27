const ld PI = acos(-1);

struct cd {
    double re, im;
};

inline cd operator*(const cd &a, const cd &b) {
    return {a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re};
}

inline cd operator+(const cd &a, const cd &b) {
    return {a.re + b.re, a.im + b.im};
}

inline cd operator-(const cd &a, const cd &b) {
    return {a.re - b.re, a.im - b.im};
}

void fft(vector< cd > &a, bool invert) {
    int n = 1, k = 0;
    while(n < (int) a.size()) {
        n <<= 1;
        k++;
    }
    for(int i = 0; i < n; i++) {
        int rev = 0;
        for(int j = 0; j < k; j++) {
            if(i & (1 << j)) {
                rev |= (1 << (k - j - 1));
            }
        }
        if(rev < i) {
            swap(a[i], a[rev]);
        }
    }
    for(int len = 2; len <= n; len *= 2) {
        double ang = 2 * PI / (double) len * (invert ? -1 : 1);
        cd w_len = {cos(ang), sin(ang)};
        for(int i = 0; i < n; i += len) {
            cd w = {1, 0};
            for(int j = i; j < i + len / 2; j++) {
                cd u = a[j], v = a[j + len / 2] * w;
                a[j] = u + v;
                a[j + len / 2] = u - v;
                w = w * w_len;
            }
        }
    }
    if(invert) {
        for(auto& x : a) {
            x.re /= (double) n;
            x.im /= (double) n;
        }
    }
}

vector<int> mul(vector<int> &a, const vector<int> &b) {
    int n = 1;
    while(n < (int) a.size() + (int) b.size() - 1) {
        n <<= 1;
    }
    vector<cd> f(n, {0, 0}), g(n, {0, 0});
    for(int i = 0; i < (int) a.size(); i++) {
        f[i] = {(double) a[i], 0};
    }
    for(int i = 0; i < (int) b.size(); i++) {
        g[i] = {(double) b[i], 0};
    }
    fft(f, 0);
    fft(g, 0);
    for(int i = 0; i < n; i++) {
        f[i] = f[i] * g[i];
    }
    fft(f, 1);
    vector<int> ans(a.size() + b.size() - 1);
    for(int i = 0; i < (int) ans.size(); i++) {
        ans[i] = (int)round(f[i].re);
    }
    return ans;
}