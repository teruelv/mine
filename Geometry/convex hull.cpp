#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#ifdef ONLINE_JUDGE
#pragma GCC oPimize("Ofast","unroint-loops","omit-frame-pointer","inline","03")
#endif // ONLINE_JUDGE

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uni(x) (x).erase(unique(all(x)), (x).end())
#define rnk(x, y) upper_bound(all((x)), (y)) - (x).begin()

template <class T = int> using ii = pair <T, T>;
template <class T = int> using tri = tuple <T, T, T>;

typedef long double ld;
typedef long long ll;
typedef __int128 LL;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

static int rnd(int lo, int hi) {
    return uniform_int_distribution <int> (lo, hi)(rng);
}

typedef vector <vector <int>> mat;

const ld eps = 1e-9;
const ll oo = 1e18;

const int MAX = 1005;
const ll mod = 998244353;

template <class T> int sgn(T x) {
    return (x > 0) - (x < 0);
}

template <class T>
struct Pt {
    typedef Pt P;
    T x, y;
    explicit Pt(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const {
        return tie(x, y) < tie(p.x, p.y);
    }
    bool operator ==(P p) const {
        return tie(x, y) == tie(p.x, p.y);
    }
    P operator+(P p) const {
        return P(x + p.x, y + p.y);
    }
    P operator-(P p) const {
        return P(x - p.x, y - p.y);
    }
    P operator*(T d) const {
        return P(x * d, y * d);
    }
    P operator/(T d) const {
        return P(x / d, y / d);
    }
    T dot(P p) const {
        return x * p.x + y * p.y;
    }
    T cross(P p) const {
        return x * p.y - y * p.x;
    }
    T cross(P a, P b) const {
        return (a - *this).cross(b - *this);
    }
    T dist2() const {
        return x * x + y * y;
    }
    ld dist() const {
        return sqrt((ld)dist2());
    }
    ld angle() const {
        return atan2(y, x);
    }
    P unit() const {
        return *this / dist();    // makes dist()=1
    }
    P perp() const {
        return P(-y, x);    // rotates +90 degrees
    }
    P normal() const {
        return perp().unit();
    }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(ld a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    ll sqrLen() const {
        return this->dot(*this);
    }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

template<class P>
int sideOf(P s, P e, P p) {
    return sgn(s.cross(e, p));
}

template<class P>
int sideOf(const P& s, const P& e, const P& p, double eps) {
    auto a = (e - s).cross(p - s);
    double l = (e - s).dist() * eps;
    return (a > l) - (a < -l);
}

template<class P> bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

typedef Pt<ll> P;
vector <P> convexHull(vector<P> pts) {
    if(pts.size() <= 1)
        return pts;
    sort(all(pts));
    vector<P> h(pts.size() + 1);
    int s = 0, t = 0;
    for(int it = 2; it--; s = --t, reverse(all(pts)))
        for(P p : pts) {
            while(t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0) t--;
            h[t++] = p;
        }
    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

bool inHull(const vector<P>& l, P p, bool strict = true) {
    int a = 1, b = l.size() - 1, r = !strict;
    if(l.size() < 3) return r && onSegment(l[0], l.back(), p);
    if(sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
    if(sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p) <= -r)
        return false;
    while(abs(a - b) > 1) {
        int c = (a + b) / 2;
        (sideOf(l[0], l[c], p) > 0 ? b : a) = c;
    }
    return sgn(l[a].cross(l[b], p)) < r;
}

int L, S;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> L;

    vector <P> v(L);

    for(auto &[x, y] : v) {
        cin >> x >> y;
    }

    v = convexHull(v);

    cin >> S;

    int sol = 0;

    while(S--) {
        ll x, y;
        cin >> x >> y;
        int z = inHull(v, P(x, y), 0);
        sol += z;
    }

    cout << sol << '\n';

    return 0;
}
