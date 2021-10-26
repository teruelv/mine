typedef vector <vector <int>> mat;

mat pre() {
    mat v;
    vector <int> a;

    v.push_back({ 0, 1, 2, 4, 3, 5 });
    v.push_back({ 1, 0, 3, 5, 2, 4 });
    v.push_back({ 2, 0, 1, 5, 4, 3 });
    v.push_back({ 5, 2, 1, 3, 4, 0 });
    v.push_back({ 3, 0, 4, 5, 1, 2 });
    v.push_back({ 4, 0, 2, 5, 3, 1 });

    auto aux = v;

    for(auto it : aux) {
        for(int r = 0; r < 3; r++) {
            swap(it[1], it[2]);
            swap(it[2], it[3]);
            swap(it[3], it[4]);
            v.push_back(it);
        }
    }

    return v;
}

mat fix(mat &rule, vector <int> &in) {
    mat ret;
    for(int i = 0; i < rule.size(); i++) {
        vector <int> v(6);
        for(int j = 0; j < 6; j++)
            v[j] = in[rule[i][j]];
        ret.push_back(v);
    }
    // comment here to keep equal rotations
    sort(all(ret));
    uni(ret);
    return ret;
}
