const ld eps = 1e-9;

struct line {
    point p, q;
} ;

using segment = line;

int sign(ld x) {
    return x < -eps ? -1 : x > eps;
}
int dblcmp(ld x, ld y) {
    return sign(x - y);
}

template<typename T> T dot(complex<T> a, complex<T> b) {
    return real(conj(a) * b);
}
template<typename T> T cross(complex<T> a, complex<T> b) {
    return imag(conj(a) * b);
}

bool intersect(const line &l, const segment &s) {
    return cross(l.q - s.p, l.p - l.q) >= 0 &&
           cross(l.q - s.q, l.p - l.q) <= 0;
}

point crosspoint(const line &l, const line &m) {
    ld A = cross(l.q - l.p, m.q - m.p);
    ld B = cross(l.q - l.p, l.q - m.p);

    if(dblcmp(cross(l.p - l.q, m.p - m.q), 0) == 0) {
        if(dblcmp(abs(m.p - l.p), abs(m.p - l.q)) <= 0)
            return l.p;
        return l.q;
    }

    if(abs(A) < eps && abs(B) < eps)
        return m.p; // same line
    if(abs(A) < eps)
        assert(false); // !!!PRECONDITION NOT SATISFIED!!!
    return m.p + B / A * (m.q - m.p);
}

//find angle (P3, P1, P2)
ld angle(ii P1, ii P2, ii P3) {
    return atan2(P3.Y - P1.Y, P3.X - P1.X) -
           atan2(P2.Y - P1.Y, P2.X - P1.X)
}

