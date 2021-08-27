#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef long long ll;
typedef pair <ll, ll> ii;

//const int MAX = 205;
const int MAX = 2e5 + 5;
const int oo = 1e9;
const int mod = 1e9 + 7;

vector <int> G[MAX];

int n, m; //n left, m right nodes
int M[MAX], A[MAX]; //match

bool bfs() {
    queue<int> Q;
    for(int i = 1; i <= n * 2; i++)
        if(M[i] == 0)
            A[i] = 0, Q.push(i);
        else
            A[i] = oo;
    A[0] = oo;
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for(int i : G[u])
            if(A[M[i]] == oo) {
                A[M[i]] = A[u] + 1;
                Q.push(M[i]);
            }
    }
    return (A[0] != oo);
}

bool dfs(int u) {
    if(!u) return 1;
    for(int i : G[u])
        if(A[M[i]] == A[u] + 1 && dfs(M[i])) {
            M[i] = u;
            M[u] = i;
            return 1;
        }
    A[u] = oo;
    return 0;
}

int hopcroft_karp() {
    int r = 0;
//    memset(M, 0, sizeof M); //done in push
    while(bfs())
        for(int i = 1; i <= n * 2; i++)
            if(M[i] == 0 && dfs(i))
                r++;
    return r;
}

///
int a[MAX], b[MAX], c[MAX];

int push(int T) {
    for(int i = 1; i <= n * 2; i++)
        G[i].clear(), A[i] = M[i] = 0;

    for(int i = 1; i <= m; i++)
        if(c[i] <= T)
            G[a[i]].push_back(b[i] + n);

    return hopcroft_karp();
}

int main() {
    //    freopen("asd.in", "r", stdin);

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for(int i = 1; i <= m; i++)
        cin >> a[i] >> b[i] >> c[i];

    int ini = 1, mid, fin = 0, ok = 0;

    for(int i = 1; i <= m; i++)
        fin = max(fin, c[i]);

    while(ini < fin) {
        mid = (ini + fin) / 2;
        int aux = push(mid);
        //        cout << mid << ": " << aux << '\n';
        if(aux == n)
            fin = mid;
        else
            ini = mid + 1;
    }

    int aux = push(ini);
    if(aux != n)ini = -1;

    cout << ini << "\n";
}
