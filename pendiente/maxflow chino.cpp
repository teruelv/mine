#pragma GCC optimize(3)
#include <list>
#include <cctype>
#include <cstdio>
#include <vector>
const int MAXN = 10005;
const int INF = 2147483647;
struct node {
    int v, f, index;
    node(int v, int f, int index) : v(v), f(f), index(index) {}
};
std::vector<node> edge[MAXN];
std::vector<int> list[MAXN], height, count, que, excess;
typedef std::list<int> List;
std::vector<List::iterator> iter;
List dlist[MAXN];
int highest, highestActive;
typedef std::vector<node>::iterator Iterator;
inline void addEdge(const int u, const int v, const int f) {
    edge[u].push_back(node(v, f, edge[v].size()));
    edge[v].push_back(node(u, 0, edge[u].size() - 1));
}
#define getchar() (S == T && (T = (S = BB) + fread(BB, 1, 1 << 15, stdin), S == T) ? EOF : *S++)
char BB[1 << 20], *S = BB, *T = BB;
inline void read(int &x) {
    x = 0;
    int w = 1;
    char ch = 0;

    while (!isdigit(ch)) {
        if (ch == '-')
            w = -1;

        ch = getchar();
    }

    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();

    x *= w;
}
inline int min(int a, int b) {
    return a < b ? a : b;
}
inline int max(int a, int b) {
    return a > b ? a : b;
}
inline void globalRelabel(int n, int t) {
    height.assign(n, n);
    height[t] = 0;
    count.assign(n, 0);
    que.clear();
    que.resize(n + 1);
    int qh = 0, qt = 0;

    for (que[qt++] = t; qh < qt;) {
        int u = que[qh++], h = height[u] + 1;

        for (Iterator p = edge[u].begin(); p != edge[u].end(); ++p)
            if (height[p->v] == n && edge[p->v][p->index].f > 0)
                count[height[p->v] = h]++, que[qt++] = p->v;
    }

    for (int i = 0; i <= n; ++i)
        list[i].clear(), dlist[i].clear();

    for (int u = 0; u < n; ++u)
        if (height[u] < n) {
            iter[u] = dlist[height[u]].insert(dlist[height[u]].begin(), u);

            if (excess[u] > 0)
                list[height[u]].push_back(u);
        }

    highest = (highestActive = height[que[qt - 1]]);
}
inline void push(int u, node &e) {
    int v = e.v, df = std::min(excess[u], e.f);
    e.f -= df;
    edge[v][e.index].f += df;
    excess[u] -= df;
    excess[v] += df;

    if (0 < excess[v] && excess[v] <= df)
        list[height[v]].push_back(v);
}
inline void discharge(int n, int u) {
    int nh = n;

    for (Iterator p = edge[u].begin(); p != edge[u].end(); ++p) {
        if (p->f > 0) {
            if (height[u] == height[p->v] + 1) {
                push(u, *p);

                if (!excess[u])
                    return;
            } else
                nh = min(nh, height[p->v] + 1);
        }
    }

    int h = height[u];

    if (count[h] == 1) {
        for (int i = h; i <= highest; ++i) {
            for (List::iterator p = dlist[i].begin(); p != dlist[i].end(); ++p)
                --count[height[*p]], height[*p] = n;

            dlist[i].clear();
        }

        highest = h - 1;
    } else {
        --count[h], iter[u] = dlist[h].erase(iter[u]), height[u] = nh;

        if (nh == n)
            return;

        ++count[nh], iter[u] = dlist[nh].insert(dlist[nh].begin(), u);
        highest = max(highest, highestActive = nh), list[nh].push_back(u);
    }
}
inline int hlpp(int n, int s, int t) {
    if (s == t)
        return 0;

    highestActive = highest = 0;
    height.assign(n, 0), height[s] = n, iter.resize(n);

    for (int i = 0; i < n; ++i)
        if (i != s)
            iter[i] = dlist[height[i]].insert(dlist[height[i]].begin(), i);

    count.assign(n, 0), count[0] = n - 1;
    excess.assign(n, 0), excess[s] = INF, excess[t] = -INF;

    for (int i = 0; i < (int)edge[s].size(); ++i)
        push(s, edge[s][i]);

    globalRelabel(n, t);

    for (int u; highestActive >= 0;) {
        if (list[highestActive].empty()) {
            --highestActive;
            continue;
        }

        u = list[highestActive].back(), list[highestActive].pop_back();
        discharge(n, u);
    }

    return excess[t] + INF;
}
int main() {
    int n, m;
    read(n), read(m);
    int s = 1, t = n;
    read(s), read(t);

    for (int i = 0, u, v, f; i < m; ++i)
        read(u), read(v), read(f), addEdge(u, v, f);

    printf("%d\n", hlpp(n + 1, s, t));
    return 0;
}
