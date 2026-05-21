const ll mod = 998244353;
const ll G = 3;

int modPow(ll b, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1)
            r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}

void ntt(vector<ll> &a, bool invert) {
    ll n = a.size();
    vector<ll> rev(n);

    for (ll i = 1; i < n; ++i)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (n >> 1));

    for (ll i = 0; i < n; ++i)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);

    for (ll len = 1; len < n; len <<= 1) {
        ll wlen = modPow(G, (mod - 1) / (len << 1));
        if (invert) wlen = modPow(wlen, mod - 2);

        for (ll i = 0; i < n; i += (len << 1)) {
            ll w = 1;
            for (ll j = 0; j < len; ++j) {
                ll u = a[i + j];
                ll v = (ll) a[i + j + len] * w % mod;

                ll x = u + v;
                if (x >= mod) x -= mod;
                a[i + j] = x;

                x = u - v;
                if (x < 0) x += mod;
                a[i + j + len] = x;

                w = w * wlen % mod;
            }
        }
    }

    if (invert) {
        ll inv = modPow(n, mod - 2);
        for (ll &x: a) x = (ll) x * inv % mod;
    }
}

vector<ll> multiply(vector<ll> a, vector<ll> b) {
    if (a.empty() || b.empty()) return {};

    ll need = a.size() + b.size() - 1;
    ll n = 1;
    while (n < need) n <<= 1;

    a.resize(n);
    b.resize(n);

    ntt(a, false);
    ntt(b, false);

    for (ll i = 0; i < n; ++i) a[i] = (ll) a[i] * b[i] % mod;

    ntt(a, true);
    a.resize(need);
    return a;
}
