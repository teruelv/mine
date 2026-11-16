/*
 -treap básico, usar como si fuera un map (ej: Treap <int, int> T)
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

    int rotate_right(int p) {
        int q = t[p].l;
        int u = t[q].r;
        t[q].r = p;
        t[p].l = u;
        pull(p);
        pull(q);
        return q;
    }

    int rotate_left(int p) {
        int q = t[p].r;
        int u = t[q].l;
        t[q].l = p;
        t[p].r = u;
        pull(p);
        pull(q);
        return q;
    }

    int _insert(int p, Key x, Value v) {
        if (!p) {
            p = add();
            t[p].x = x;
            t[p].v = t[p].mx = v;
            return p;
        }
        if (x == t[p].x) {
            t[p].v = max(t[p].v, v);
        } else if (x < t[p].x) {
            t[p].l = _insert(t[p].l, x, v);
        } else {
            t[p].r = _insert(t[p].r, x, v);
        }
        if (t[p].l && t[p].prioridad < t[t[p].l].prioridad)
            p = rotate_right(p);
        if (t[p].r && t[p].prioridad < t[t[p].r].prioridad)
            p = rotate_left(p);
        pull(p);
        return p;
    }

    void insert(Key x, Value v) {
        root = _insert(root, x, v);
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
