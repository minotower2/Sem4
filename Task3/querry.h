#ifndef QUERRY
#define QUERRY

#include <memory>
#include <string.h>
#include "btree.h"
#define LEN 1234

class word {
  private:
    std::unique_ptr<char[]> string;
  public:
    word() = default;
    ~word() = default;
    word(const word&) = delete;
    word(word&&) = default;
    word& operator = (const word&) = delete;
    word& operator = (word&&) = default;
    void print(FILE *fp = stdout) {
      fprintf(fp, "%s\n", string.get());
    }
    io_status init (char * n) {
      if (n != nullptr) {
        size_t len = strlen (n);
        string = std::make_unique<char []> (len + 1);
        if (string != nullptr) {
          for (size_t i = 0; i <= len; i++)
            string[i] = n[i];
        }
        else
          return io_status::memory;
      }
      return io_status::success;
    }
    int operator< (const word& x) const { return strcmp (string.get(), x.string.get()) < 0; }
    int operator<= (const word& x) const { return strcmp (string.get(), x.string.get()) <= 0; }
    int operator> (const word& x) const { return strcmp (string.get(), x.string.get()) > 0; }
    int operator>= (const word& x) const { return strcmp (string.get(), x.string.get()) >= 0; }
    int operator== (const word& x) const { return strcmp (string.get(), x.string.get()) == 0; }
    int operator!= (const word& x) const { return strcmp (string.get(), x.string.get()) != 0; }
};

class querry_1 {
  private:
    b_tree<word> birch;
  public:
    querry_1() = default;
    querry_1(int m) {
      birch.set_m(m);
    }
    io_status initialize (char *string, const char *t) {
      int i = 0;
      char *start = strtok(string, t);
      while (start) {
        word buf;
        io_status r;
        r = buf.init(start);
        if (r != io_status::success) return r;
        r = birch.add_value(buf);
        if (r != io_status::success) return r;
        start = strtok(string, t);
      }
      return io_status::success;
    }
    ~querry_1() = default;
};

#endif
