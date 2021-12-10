ll phi(ll n) {
    ll ret = n;
    for(ll i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            ret -= ret / i;
            while(n % i == 0)
                n /= i;
        }
    }
    if(n != 1)
        ret -= ret / n;
    return ret;
}
