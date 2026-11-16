/*
 -treap basado en split/merge, usar como si fuera un map (ej: Treap <int, int> T)
 -usa valores numéricos
 -asume value >= 0, cambiar el neutro para negativos
 -query responde mayor valor con Key < x
 -insert añade una copia (Key, Val), si el Key existe toma el mayor valor
 */
template<typename Key, typename Value>
struct Treap {
    struct Node {
        int l = 0, r = 0;
        Key x{};
        Value v{}, mx{};
        int prioridad;
    };

    vector<Node> t;
    int root = 0, used = 0;

    Treap(int n = 0) : t(1) {
        t.reserve(n + 1);
    }

    int add() {
        int x = ++used;
        t.emplace_back();
        t[x].prioridad = rnd(0, INT_MAX);
        return x;
    }

    void pull(int x) {
        t[x].mx = t[x].v;
        if (t[x].l)t[x].mx = max(t[x].mx, t[t[x].l].mx);
        if (t[x].r)t[x].mx = max(t[x].mx, t[t[x].r].mx);
    }

    using i2 = pair<int, int>;

    i2 split(int p, Key x) {
        if (p == 0)
            return {0, 0};
        if (x <= t[p].x) {
            auto [a, b] = split(t[p].l, x);
            t[p].l = b;
            pull(p);
            return {a, p};
        } else {
            auto [a, b] = split(t[p].r, x);
            t[p].r = a;
            pull(p);
            return {p, b};
        }
    }

    int merge(int a, int b) {
        if (a == 0)return b;
        if (b == 0)return a;
        if (t[a].prioridad > t[b].prioridad) {
            t[a].r = merge(t[a].r, b);
            pull(a);
            return a;
        } else {
            t[b].l = merge(a, t[b].l);
            pull(b);
            return b;
        }
    }

    bool update(int p, Key x, Value v) {
        if (!p)return false;
        if (x == t[p].x) {
            t[p].v = max(t[p].v, v);
            pull(p);
            return true;
        }
        if (x < t[p].x) {
            bool ok = update(t[p].l, x, v);
            if (ok)pull(p);
            return ok;
        } else {
            bool ok = update(t[p].r, x, v);
            if (ok)pull(p);
            return ok;
        }
    }

    void insert(Key x, Value v) {
        if (update(root, x, v))return;
        auto [a, b] = split(root, x);
        int c = add();
        t[c].x = x;
        t[c].v = t[c].mx = v;
        a = merge(a, c);
        root = merge(a, b);
    }

    Value query(Key x) {
        int p = root;
        Value r = 0; // neutro
        while (p) {
            if (x <= t[p].x)
                p = t[p].l;
            else {
                r = max({r, t[p].v, t[t[p].l].mx});
                p = t[p].r;
            }
        }
        return r;
    }
};
