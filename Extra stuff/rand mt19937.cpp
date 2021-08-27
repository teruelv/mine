mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

static int rnd(int lo, int hi) {
    return uniform_int_distribution <int> (lo, hi)(rng);
}