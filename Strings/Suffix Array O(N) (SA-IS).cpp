#include <bits/stdc++.h>

using namespace std;

// Suffix Array and LCP in O(N). Uses SA-IS algorithm
// It's faster than most O(N) SACA's as said here:  https://codeforces.com/blog/entry/91417?#comment-799712
// the code is based on this article:               https://zork.net/~st/jottings/sais.html
// but has some influence from                      https://github.com/kurpicz/sais-lite-lcp
// and it's speed can be improved as shown here:    https://synergy.cs.vt.edu/pubs/papers/timoshevskaya-saisopt-iccabs14.pdf
// but this is fast enough for most ICPC problems,
// if not all
// Tested against some random problems +            https://codeforces.com/edu/course/2/lesson/2

struct SuffixArray {
    vector<int> sa, lcp, pos;

    static vector<int> sais(vector<int> s, int upper) {
        int n = s.size();
        if (n == 1) return {0};
        if (n == 2) return s[0] < s[1] ? vector<int>{0, 1} : vector<int>{1, 0};

        vector<int> ls(n);
        ls[n - 1] = 1;
        for (int i = n - 2; i >= 0; --i)
            ls[i] = (s[i] < s[i + 1]) || (s[i] == s[i + 1] && ls[i + 1]);

        vector<int> sum_l(upper + 2), sum_s(upper + 2);
        for (int i = 0; i < n; ++i) {
            if (ls[i]) ++sum_l[s[i] + 1];
            else ++sum_s[s[i]];
        }
        for (int i = 0; i <= upper; ++i) {
            sum_s[i] += sum_l[i];
            sum_l[i + 1] += sum_s[i];
        }

        vector<int> lms_map(n, -1), lms;
        lms.reserve(n / 2 + 1);

        for (int i = 1; i < n; ++i)
            if (!ls[i - 1] && ls[i]) {
                lms_map[i] = lms.size();
                lms.push_back(i);
            }

        auto induce = [&](const vector<int> &ord_lms) {
            vector<int> sa(n, -1), buf(upper + 2);

            copy(sum_s.begin(), sum_s.end(), buf.begin());
            for (int d: ord_lms) sa[buf[s[d]]++] = d;

            copy(sum_l.begin(), sum_l.end(), buf.begin());
            sa[buf[s[n - 1]]++] = n - 1;
            for (int i = 0; i < n; ++i) {
                int v = sa[i];
                if (v > 0 && !ls[v - 1]) sa[buf[s[v - 1]]++] = v - 1;
            }

            copy(sum_l.begin(), sum_l.end(), buf.begin());
            for (int i = n - 1; i >= 0; --i) {
                int v = sa[i];
                if (v > 0 && ls[v - 1]) sa[--buf[s[v - 1] + 1]] = v - 1;
            }
            return sa;
        };

        vector<int> sa = induce(lms);
        int m = lms.size();

        if (m <= 1) return sa;

        vector<int> sorted_lms;
        sorted_lms.reserve(m);

        for (int v: sa) if (lms_map[v] != -1) sorted_lms.push_back(v);

        vector<int> rec_s(m);
        int rec_upper = 0;
        rec_s[lms_map[sorted_lms[0]]] = 0;

        for (int i = 1; i < m; ++i) {
            int l = sorted_lms[i - 1], r = sorted_lms[i];
            int le = (lms_map[l] + 1 < m ? lms[lms_map[l] + 1] : n);
            int re = (lms_map[r] + 1 < m ? lms[lms_map[r] + 1] : n);

            bool same = (le - l == re - r);
            while (same && l < le) {
                if (s[l] != s[r]) same = false;
                ++l;
                ++r;
            }

            if (!same) ++rec_upper;
            rec_s[lms_map[sorted_lms[i]]] = rec_upper;
        }

        vector<int> ord(m);
        if (rec_upper + 1 < m) {
            vector<int> rec(m + 1);
            for (int i = 0; i < m; ++i) rec[i] = rec_s[i] + 1;
            rec[m] = 0;

            vector<int> rec_sa = sais(move(rec), rec_upper + 1);
            for (int i = 0; i < m; ++i) ord[i] = lms[rec_sa[i + 1]];
        } else {
            for (int i = 0; i < m; ++i) ord[rec_s[i]] = lms[i];
        }

        return induce(ord);
    }

    template<class Seq>
    void build_lcp(const Seq &s) {
        int n = s.size();
        pos.assign(n + 1, 0);
        for (int i = 0; i <= n; ++i) pos[sa[i]] = i;

        lcp.assign(n + 1, 0);
        for (int i = 0, k = 0; i < n; ++i) {
            if (pos[i] == 0) continue;
            int j = sa[pos[i] - 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
            lcp[pos[i]] = k;
            if (k) --k;
        }
    }

    SuffixArray(const string &s) {
        int n = s.size();
        vector<int> a(n + 1, 0);
        for (int i = 0; i < n; ++i) a[i] = s[i] + 1;
        sa = sais(move(a), *max_element(a.begin(), a.end()));
        build_lcp(s);
    }

    SuffixArray(const vector<int> &a) {
        int n = a.size();
        vector<int> b(n + 1);
        int upper = 0;
        for (int i = 0; i < n; ++i) {
            b[i] = a[i] + 1;
            if (b[i] > upper) upper = b[i];
        }
        b[n] = 0;

        sa = sais(move(b), upper);
        build_lcp(a);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;

    SuffixArray SA(s);
    int n = s.size();

    for (int i = 1; i <= n; i++) {
        cout << SA.lcp[i] << " " << s.substr(SA.sa[i]) << '\n';
    }

    return 0;
}
