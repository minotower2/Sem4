#ifndef CONFIG
#define CONFIG
#include "stdio.h"
#include "record.h"

class config {
  private:
    int k = -1;
    int m = -1;
  public:
    config() = default;
    ~config() = default;
    int get_k() {return k;}
    int get_m() {return m;}
    bool parse(FILE *fp) {
      char buf[LEN];
      int buffer1 = -1, buffer2 = -1;
      while (fgets(buf, LEN, fp)) {
        if (buf[0] == '#' || buf[0] == '\0') continue;
        if (sscanf(buf, "%d%d", &buffer1, &buffer2) == 2) {if (buffer1 == -1 || buffer2 == -1) return false; k = buffer1; m = buffer2; return true;}
        if (sscanf(buf, "%d", &buffer1) == 1) {
          if (buffer1 == -1) return false;
          if (k == -1) k = buffer1;
          else m = buffer1;
        }
      }
      if (k == -1 || m == -1) return false;
      return true;
    }
    void print() {printf("%d %d\n", k, m);}
};

#endif
