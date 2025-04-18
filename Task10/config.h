#ifndef CONFIG
#define CONFIG
#define TABLELENGTH 20000
#define TABLELENGTHPRIME 40
#include "stdio.h"
#include "record.h"

class config {
  private:
    int k = -1;
    int m = -1;
    int l = -1;
    int n = -1;
  public:
    config() = default;
    ~config() = default;
    int get_k() {return k;}
    int get_m() {return m;}
    int get_l() {return l;}
    int get_n() {return n;}
    bool parse(FILE *fp) {
      char buf[LEN];
      int buffer1 = -1;
      while (fgets(buf, LEN, fp)) {
        if (buf[0] == '#' || buf[0] == '\0') continue;
        if (sscanf(buf, "%d", &buffer1) == 1) {
          if (buffer1 < 0) return false;
          if (k == -1) k = buffer1;
          else if (m == -1) m = buffer1;
          else if (l == -1) l = buffer1;
          else n = buffer1;
        }
      }
      if (k == -1 || m == -1 || l == -1 || n == -1) return false;
      return true;
    }
    void print() {printf("%d %d %d %d\n", k, m, l, n);}
};

#endif
