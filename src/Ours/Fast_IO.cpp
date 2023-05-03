#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
FILE *Fin(fopen("test.in", "r")), *Fout(fopen("test.out", "w"));
#else
FILE *Fin(stdin), *Fout(stdout);
#endif
namespace IO {
class qistream {
  static const size_t SIZE = 1 << 16, BLOCK = 32;
  FILE* fp;
  char buf[SIZE];
  int p;

 public:
  qistream(FILE* _fp = stdin) : fp(_fp), p(0) {
    fread(buf + p, 1, SIZE - p, fp);
  }
  void flush() {
    memmove(buf, buf + p, SIZE - p), fread(buf + SIZE - p, 1, p, fp), p = 0;
  }
  template <class T>
  qistream& operator>>(T& x) {
    x = 0;
    p + BLOCK >= SIZE ? flush() : void();
    bool flag = false;
    for (; !isdigit(buf[p]); ++p)
      flag = buf[p] == '-';
    for (; isdigit(buf[p]); ++p)
      x = x * 10 + buf[p] - '0';
    x = flag ? -x : x;
    return *this;
  }
  char getch() { return buf[p++]; }
  qistream& operator>>(char* str) {
    char ch = getch();
    while (ch <= ' ')
      ch = getch();
    for (int i = 0; ch > ' '; ++i, ch = getch())
      str[i] = ch;
    return *this;
  }
} qcin(Fin);
class qostream {
  static const size_t SIZE = 1 << 16, BLOCK = 32;
  FILE* fp;
  char buf[SIZE];
  int p;

 public:
  qostream(FILE* _fp = stdout) : fp(_fp), p(0) {}
  ~qostream() { fwrite(buf, 1, p, fp); }
  void flush() { fwrite(buf, 1, p, fp), p = 0; }
  template <class T>
  qostream& operator<<(T x) {
    int len = 0;
    p + BLOCK >= SIZE ? flush() : void();
    x < 0 ? (x = -x, buf[p++] = '-') : 0;
    do
      buf[p + len] = x % 10 + '0', x /= 10, ++len;
    while (x);
    for (int i = 0, j = len - 1; i < j; ++i, --j)
      swap(buf[p + i], buf[p + j]);
    p += len;
    return *this;
  }
  void putch(char ch) { buf[p++] = ch; }
  qostream& operator<<(const char* str) {
    for (int i = 0; str[i]; ++i)
      putch(str[i]);
    return *this;
  }
} qcout(Fout);
}
using namespace IO;

// More simple
std::ios::sync_with_stdio(false);
std::cin.tie(nullptr);

// Time Calc
int st = clock();

// TODO...

printf("%lf\n", (double)(clock() - st)/CLOCKS_PER_SEC);