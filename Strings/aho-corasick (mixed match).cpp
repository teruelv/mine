struct Aho_Corasick {
    struct node {
        unordered_map <int, int> next;
        int f, dp;
    } ;

    const int ALP = 26;

    vector <node> T;
    vector <vector <int>> jump;

    Aho_Corasick() {
        Push();
    }

    int Push() {
        T.push_back(node());
        jump.push_back(vector <int> (ALP, -1));
        return T.size() - 1;
    }

    node &operator [](int p) {
        return T[p];
    }

    void Add(string &s) {
        int p = 0;
        for(char c : s) {
            c -= 'a';
            if(!T[p].next.count(c))
                T[p].next[c] = Push();
            p = T[p].next[c];
        }
        T[p].dp++;
    }

    inline int go(int x, int to) {
        int &r = jump[x][to];
        if(r != -1)
            return r;
        r = x;
        if(r && !T[r].next.count(to))
            return r = go(T[r].f, to);
        return r = T[r].next[to];
    }

    void Build() {
        queue <int> q;
        for(auto [x, to] : T[0].next)
            q.push(to);
        while(!q.empty()) {
            int c = q.front();
            q.pop();
            for(auto [x, to] : T[c].next) {
                q.push(to);
                int f = T[c].f;
                while(f && !T[f].next.count(x))
                    f = T[f].f;
                T[to].f = T[f].next[x];
                T[to].dp += T[T[to].f].dp;
            }
        }
    }

    int Count(string &s) {
        int r = 0, p = 0;
        for(auto c : s)
            r += T[p = go(p, c - 'a')].dp;
        return r;
    }

    void clear() {
        jump.clear();
        T.clear();
        Push();
    }
} ;
