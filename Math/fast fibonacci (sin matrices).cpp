map<ll, ll> m;

ll F(ll n) {
    if (n < 2)
        return n;
    if (m.count(n))
        return m[n];
    ll k = n / 2;
    if (n & 1) {
        ll f1 = F(k + 1);
        ll f2 = F(k);
        return m[n] = (f1 * f1 + f2 * f2) % mod;
    } else {
        ll f1 = F(k);
        ll f2 = F(k - 1);
        return m[n] = f1 * (f2 * 2 + f1) % mod;
    }
}
