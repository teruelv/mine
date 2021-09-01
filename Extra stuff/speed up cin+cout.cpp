
struct _ENDLINE {
} _ENDL;

struct FastIO {
private:
#ifdef _WIN32
    inline char gcu() {
        return _getchar_nolock();
    }
    inline void pcu(char x) {
        _putchar_nolock(x);
    }
#else
    inline char gcu() {
        return getchar_unlocked();
    }
    inline void pcu(char x) {
        putchar_unlocked(x);
    }
#endif
    char *bufferi, *bufferll, *bufferLL;
    short imax, llmax, LLmax;
    inline bool valid(char x) {
        return !isspace(x) && x != EOF;
    }
public:
    FastIO(const int32_t a = 11, const int32_t b = 21, const int32_t c = 41): imax(a), llmax(b), LLmax(c) {
        bufferi = new char[a];
        bufferll = new char[b];
        bufferLL = new char[c];
    }
    void read(int64_t &x) {
        x = 0;
        char c;
        bool neg = false;
        while(true) {
            c = gcu();
            if(c == '-') {
                neg = true;
                break;
            }
            if(c >= '0' && c <= '9') {
                x = c - '0';
                break;
            }
        }
        while(isdigit(c = gcu())) {
            x = x * 10 + (c - '0');
        }
        if(neg) x = -x;
    }
    void read(int32_t &x) {
        x = 0;
        char c;
        bool neg = false;
        while(true) {
            c = gcu();
            if(c == '-') {
                neg = true;
                break;
            }
            if(c >= '0' && c <= '9') {
                x = c - '0';
                break;
            }
        }
        while(isdigit(c = gcu())) {
            x = x * 10 + (c - '0');
        }
        if(neg) x = -x;
    }
    void read(__int128 &x) {
        x = 0;
        char c;
        bool neg = false;
        while(true) {
            c = gcu();
            if(c == '-') {
                neg = true;
                break;
            }
            if(c >= '0' && c <= '9') {
                x = c - '0';
                break;
            }
        }
        while(isdigit(c = gcu())) {
            x = x * 10 + (c - '0');
        }
        if(neg) x = -x;
    }
    void read(char &x) {
        while(!valid(x = gcu()));
    }
    void read(string &s) {
        s.clear();
        char c;
        while(!valid(c = gcu())) ;
        s += c;
        while(valid(c = gcu())) s += c;
    }
    template<typename A, typename B> void read(pair<A, B> &p) {
        read(p.first);
        read(p.second);
    }
    template<typename T> FastIO& operator >> (T &x) {
        read(x);
        return *this;
    }
    void print(int64_t n) {
        int64_t i = llmax;
        bool neg = false;
        if(n < 0) {
            neg = true;
            n = -n;
        }
        do {
            bufferll[--i] = (n % 10) + '0';
            n /= 10;
        } while(n);
        if(neg) bufferll[--i] = '-';
        do {
            pcu(bufferll[i]);
        } while(++i < llmax);
    }
    void print(int32_t n) {
        int32_t i = imax;
        bool neg = false;
        if(n < 0) {
            neg = true;
            n = -n;
        }
        do {
            bufferi[--i] = (n % 10) + '0';
            n /= 10;
        } while(n);
        if(neg) bufferi[--i] = '-';
        do {
            pcu(bufferi[i]);
        } while(++i < imax);
    }
    void print(__int128 n) {
        int32_t i = LLmax;
        bool neg = false;
        if(n < 0) {
            neg = true;
            n = -n;
        }
        do {
            bufferLL[--i] = (n % 10) + '0';
            n /= 10;
        } while(n);
        if(neg) bufferLL[--i] = '-';
        do {
            pcu(bufferLL[i]);
        } while(++i < LLmax);
    }
    void print(char c) {
        pcu(c);
    }
    void print(const string &s) {
        for(char i : s) pcu(i);
    }
    template<typename T> FastIO& operator << (const T &x) {
        print(x);
        return *this;
    }
    FastIO& operator << (const _ENDLINE &x) {
        pcu('\n');
        fflush(stdout);
        return *this;
    }
};

FastIO _FR;

#define cin _FR
#define cout _FR
#define endl _ENDL
