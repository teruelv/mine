void calc_phi() {
    phi[1] = 1;
    for(ll i = 2; i < MAX; i++) {
        if(!phi[i]) {
            phi[i] = i - 1;
            for(ll j = i * 2; j < MAX; j += i) {
                if(!phi[j])
                    phi[j] = j;
                phi[j] = (phi[j] / i) * (i - 1) % mod;
            }
        }
    }
}