for(int mask = 1; mask < (1 << n); mask++) {
    for(int sub = mask; sub > 0; sub = (sub - 1) & mask)
        //do something;
    }
