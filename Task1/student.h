#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <memory>
#include <string.h>

enum class io_status {
  success,
  memory,
  format,
};

class student {
  private:
    std::unique_ptr<char[]> name;
    int value = 0;
  public:
    student() = default;
    student(const student& x) = delete;
    student(student&& x) = default;
    ~student() = default;
    student& operator=(const student& x) = delete;
    student& operator=(student&& x) = default;
    void print(FILE *fp = stdout) {
      fprintf(fp, "%s %d\n", name.get(), value);
    }
    io_status read(FILE *fp = stdin) {
      const int LEN = 1234;
      char n[LEN];
      int v;
      if (fscanf(fp, "%s%d", n, &v) != 2)
        return io_status::format;
      erase();
      return init(n, v);
    }
  private:
    void erase() {
      value = 0;
      name = nullptr;
    }
    io_status init(const char *n, int v) {
      value = v;
      size_t len = strlen(n);
      name = std::make_unique<char[]> (len+1);
      if (name != nullptr) {
        for (size_t i = 0; i <= len; i++) {
          name[i] = n[i];
        }
      }
      else return io_status::memory;
      return io_status::success;
    }
  public:
    int cmp(const student& x) const {
      if (name == nullptr) {
        if (x.name != nullptr) return -1;
        else return value - x.value;
      }
      if (x.name == nullptr) return 1;
      int res = strcmp(name.get(), x.name.get());
      if (res) return res;
      return value-x.value;
    }
    int operator < (const student& x) const {return cmp(x) < 0;}
    int operator <= (const student& x) const {return cmp(x) <= 0;}
    int operator > (const student& x) const {return cmp(x) > 0;}
    int operator >= (const student& x) const {return cmp(x) >= 0;}
    int operator == (const student& x) const {return cmp(x) == 0;}
    int operator != (const student& x) const {return cmp(x) != 0;}
};

#endif
