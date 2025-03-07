#ifndef QUERRY
#define QUERRY

#include <memory>
#include <string.h>
#include "btree.h"
#include "rb_tree.h"
#include "avl_tree.h"
#include <vector>

#define LEN 1234

class word {
  private:
    std::unique_ptr<char[]> string;
  public:
    word() = default;
    ~word() = default;
    word(const word&) = delete;
    word(char *n) {
      init(n);
    }
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
          return io_status::success;
        }
        else
          return io_status::memory;
      }
      else {
        return io_status::success;
      }
    }
    char * get() const {return string.get();}
    int operator< (const word& x) const { if (string.get() == nullptr) return -1; if (x.get() == nullptr) return 1; return strcmp (string.get(), x.string.get()) < 0; }
    int operator<= (const word& x) const { if (string.get() == nullptr) return -1; if (x.get() == nullptr) return 1; return strcmp (string.get(), x.string.get()) <= 0; }
    int operator> (const word& x) const { if (string.get() == nullptr) return -1; if (x.get() == nullptr) return 1; return strcmp (string.get(), x.string.get()) > 0; }
    int operator>= (const word& x) const { if (string.get() == nullptr) return -1; if (x.get() == nullptr) return 1; return strcmp (string.get(), x.string.get()) >= 0; }
    int operator== (const word& x) const { if (string.get() == nullptr) return -1; if (x.get() == nullptr) return 1; return strcmp (string.get(), x.string.get()) == 0; }
    int operator!= (const word& x) const { if (string.get() == nullptr) return -1; if (x.get() == nullptr) return 1; return strcmp (string.get(), x.string.get()) != 0; }
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
      char *start = strtok(string, t);
      word buf;
      io_status r;
      while (start) {
        r = buf.init(start);
        if (r != io_status::success) return r;
        if (buf.get() == nullptr) return io_status::read;
        r = birch.add_value(buf);
        if (r != io_status::success) return r;
        start = strtok(nullptr, t);
      }
      return io_status::success;
    }
    ~querry_1() = default;
    void print(int r) {
      birch.print(r);
    }
    int search(char *s) {
      if (s == nullptr) return 0;
      word buf;
      io_status r = buf.init(s);
      if (r != io_status::success) return 0;
      return birch.search(birch.get_root(), buf);
    }
};


class querry_2 {
  private:
    rb_tree<word> birch;
  public:
    querry_2() = default;
    io_status initialize (char *string, const char *t) {
      char *start = strtok(string, t);
      io_status r;
      while (start) {
        r = birch.add_value(start);
        if (r != io_status::success) return r;
        start = strtok(nullptr, t);
      }
      return io_status::success;
    }
    ~querry_2() = default;
    void print(int r) {
      birch.print(r);
    }
    int search(char *s) {
      word buf;
      io_status r = buf.init(s);
      if (r != io_status::success) return 0;
      return birch.search(birch.get_root(), buf);
    }
};

class pair {
  private:
    word a;
    word b;
  public:
    pair() = default;
    ~pair() = default;
    pair(char *c, char *n) {init(c, n);}
    io_status init (char * n, char * m) {
      io_status ret;
      ret = a.init(n);
      if (ret != io_status::success) return ret;
      ret = b.init(m);
      if (ret != io_status::success) return ret;
      return io_status::success;
    }
    pair(const pair&) = delete;
    pair(pair&&) = default;
    pair& operator = (const pair&) = delete;
    pair& operator = (pair&&) = default;
    void print(FILE *fout = stdout) {
      fprintf(fout, "%s %s\n", a.get(), b.get());
    }
    int operator<(const pair& x) {return a < x.a;}
    int operator>(const pair& x) {return a > x.a;}
    int operator<=(const pair& x) {return a <= x.a;}
    int operator>=(const pair& x) {return a >= x.a;}
    int operator!=(const pair& x) {return a != x.a;}
    int operator==(const pair& x) {return a == x.a;}
    word& get_first() {return a;}
    word& get_second() {return b;}
};

class querry_3 {
  private:
    avl_tree<pair> birch;
  public:
    querry_3() = default;
    io_status initialize (char *string, char *x, const char *t) {
      std::vector<char *> words;
      std::vector<char *> replace;
      char *start = strtok(string, t);
      while (start) {
        words.push_back(start);
        start = strtok(nullptr, t);
      }
      start = strtok(x, t);
      while (start) {
        replace.push_back(start);
        start = strtok(nullptr, t);
      }
      long int a = words.size(), b = replace.size(), dif;
      if (a > b) {
        dif = a - b;
        for (long int i = 0; i < dif; i++) {
          replace.push_back(nullptr);
        }
      }
      for (long int i = 0; i < a; i++) {
        io_status r;
        r = birch.add_value(words[i], replace[i]);
        if (r != io_status::success) return r;
      }
      return io_status::success;
    }
    ~querry_3() = default;
    void print(int r) {
      birch.print(r);
    }
    int search(char *s) {
      if (s == nullptr) return 0;
      pair buf;
      io_status r = buf.init(s, nullptr);
      if (r != io_status::success) return 0;
      return birch.search(birch.get_root(), buf);
    }
};

#endif
