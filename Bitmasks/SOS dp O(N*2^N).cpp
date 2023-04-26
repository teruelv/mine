    for(int msk = 0; msk < (1 << n); msk++)
        dp[msk] = sum;

    for(int i = 0; i < n; i++)
        for(int msk = 0; msk < (1 << n); msk++)
            if(msk & (1 << i))
                dp[msk] = (dp[msk] + dp[msk ^ (1 << i)]) % mod;
