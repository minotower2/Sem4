#ifndef RECORD
#define RECORD
#include <memory>
#include <stdio.h>
#include <string.h>
#include "ordering.h"
#define LEN 1234

enum class condition {
  none,
  eq,
  ne,
  lt,
  gt,
  le,
  ge,
  like,
  nlike,
};

enum class io_status
{
  success,
  eof,
  format,
  memory,
  open,
  create,
};

class record {
  private:
    std::unique_ptr<char []> name = nullptr;
    int phone = 0;
    int group = 0;
  public:
    record () = default;
    ~record () = default;
    const char * get_name () const { return name.get (); }
    int get_phone () const { return phone; }
    int get_group () const { return group; }
    record (record &&x) = default;
    record& operator= (record&& x) = default;
    record (const record &x) = delete;
    record& operator= (const record&) = delete;
    int init (const char *n, int p, int g) {
      phone = p;
      group = g;
      if (n) {
        name = std::make_unique<char []> (strlen (n) + 1);
        if (!name) return -1;
        strcpy (name.get(), n);
      }
      else name = nullptr;
      return 0;
    }
    void set_phone(int p) {
      phone = p;
    }
    void set_group(int g) {
      group = g;
    }
    int set_name(const char *n) {
      if (n) {
        name = std::make_unique<char []> (strlen (n) + 1);
        if (!name) return -1;
        strcpy (name.get(), n);
      }
      else name = nullptr;
      return 0;
    }
    io_status read (FILE *fp = stdin) {
      char buf[LEN];
      name = nullptr;
      if (fscanf (fp, "%s%d%d", buf, &phone, &group) != 3) {
        if (feof(fp)) return io_status::eof;
        return io_status::format;
      }
      if (init (buf, phone, group)) return io_status::memory;
      return io_status::success;
    }
    void print(const ordering order[] = nullptr, FILE *fp = stdout) const {
      const int max_items = 3;
      const ordering default_ordering[max_items] = {ordering::name, ordering::phone, ordering::group};
      const ordering * p = (order ? order : default_ordering);
      for (int i = 0; i < max_items; i++) switch (p[i]) {
        case ordering::name:
          fprintf (fp, " %s", name.get()); break;
        case ordering::phone:
          fprintf (fp, " %d", phone); break;
        case ordering::group:
          fprintf (fp, " %d", group); break;
        case ordering::none:
          continue;
      }
      fprintf (fp, "\n");
    }

    bool compare_name (condition x, const record& y) const {
      switch(x) {
        case condition::none:
          return true;
        case condition::eq:
          if (name.get() == nullptr && y.get_name() == nullptr) return true;
          if (name.get() == nullptr || y.get_name() == nullptr) return false;
          return strcmp(name.get(), y.get_name()) == 0;
        case condition::ne:
          if (name.get() == nullptr && y.get_name() == nullptr) return false;
          if (name.get() == nullptr || y.get_name() == nullptr) return true;
          return strcmp(name.get(), y.get_name()) != 0;
        case condition::lt:
          if (name.get() == nullptr && y.get_name() != nullptr) return true;
          if (name.get() == nullptr || y.get_name() == nullptr) return false;
          return strcmp(name.get(), y.get_name()) > 0;
        case condition::gt:
          if (name.get() != nullptr && y.get_name() == nullptr) return true;
          if (name.get() == nullptr || y.get_name() == nullptr) return false;
          return strcmp(name.get(), y.get_name()) < 0;
        case condition::le:
          if (name.get() == nullptr && y.get_name() == nullptr) return true;
          if (name.get() == nullptr && y.get_name() != nullptr) return true;
          if (name.get() == nullptr || y.get_name() == nullptr) return false;
          return strcmp(name.get(), y.get_name()) >= 0;
        case condition::ge:
          if (name.get() == nullptr && y.get_name() == nullptr) return true;
          if (name.get() != nullptr && y.get_name() == nullptr) return true;
          if (name.get() == nullptr || y.get_name() == nullptr) return false;
          return strcmp(name.get(), y.get_name()) <= 0;
        case condition::like:
          return like_compare(y.get_name(), name.get());
        case condition::nlike:
          return !like_compare(y.get_name(), name.get());
      }
      return false;
    }
    bool compare_phone (condition x, const record& y) const {
      switch (x) {
        case condition::none:
          return true;
        case condition::eq:
          return phone == y.phone;
        case condition::ne:
          return phone != y.phone;
        case condition::lt:
          return phone > y.phone;
        case condition::gt:
          return phone < y.phone;
        case condition::le:
          return phone >= y.phone;
        case condition::ge:
          return phone <= y.phone;
        case condition::like:
          return false;
        case condition::nlike:
          return true;
      }
      return false;
    }
    bool compare_group (condition x, const record& y) const {
      switch (x) {
        case condition::none:
          return true;
        case condition::eq:
          return group == y.group;
        case condition::ne:
          return group != y.group;
        case condition::lt:
          return group > y.group;
        case condition::gt:
          return group < y.group;
        case condition::le:
          return group >= y.group;
        case condition::ge:
          return group <= y.group;
        case condition::like:
          return false;
        case condition::nlike:
          return true;
      }
      return false;
    }
  private:
    bool like_compare(const char* x, const char* y) const {
      char buffer[LEN];
      char buffercopy[LEN];
      char keys[LEN];
      int j = 0, k = 0, l = 0;
      int len = strlen(y);
      for (int i = 0; i < len; i++) {
        if (y[i] == '\\' && y[i+1] == '\\') {
          buffer[j++] = '\\';
          buffercopy[l++] = '\\';
          keys[k++] = '0';
          i++;
        }
        else if (y[i] == '\\' && y[i+1] == '\0') {
          return false;
        }
        else if (y[i] == '\\') {
          buffer[j++] = y[i+1];
          buffercopy[l++] = y[i+1];
          keys[k++] = '0';
          i++;
        }
        else if (y[i] == '_'){
          buffer[j++] = y[i];
          buffercopy[l++] = y[i];
          keys[k++] = '1';
        }
        else if (y[i] == '%'){
          buffer[j++] = y[i];
          buffercopy[l++] = y[i];
          keys[k++] = '2';
        }
        else if (y[i] == '[') {
          if (y[i+1] == '\0') return false;
          if (y[i+1] == '^') {
            if (y[i+2] == '\0' || y[i+3] == '\0' || y[i+4] == '\0' || y[i+5] == '\0') return false;
            if (y[i+3] != '-' || y[i+5] != ']') return false;
            buffer[j++] = y[i+2];
            buffercopy[l++] = y[i+4];
            keys[k++] = '4';
            i += 5;
          }
          else {
            if (y[i+2] == '\0' || y[i+3] == '\0' || y[i+4] == '\0') return false;
            if (y[i+2] != '-' || y[i+4] != ']') return false;
            buffer[j++] = y[i+1];
            buffercopy[l++] = y[i+3];
            keys[k++] = '3';
            i += 4;
          }
        }
        else {
          buffer[j++] = y[i];
          buffercopy[l++] = y[i];
          keys[k++] = '0';
        }
      }
      buffer[j] = '\0';
      keys[k] = '\0';
      buffercopy[l] = '\0';
      int m, n = 0;

      char buffercopycopy[LEN];
      if (keys[0] == '2') {
        if (strlen(keys) == 1) return true;
        if (keys[strlen(keys)-1] == '2') {
          n = 0;
          for (m = 1; buffer[m]; m++) {
            if (buffer[m] == '%') break;
            buffercopycopy[n++] = buffer[m];
          }
          buffercopycopy[n] = '\0';
          if (strstr(x, buffercopycopy) == nullptr) return false;
          else return true;
        }
        else {
          n = 0;
          for (m = 1; buffer[m]; m++) {
            buffercopycopy[n++] = buffer[m];
          }
          buffercopycopy[n] = '\0';
          int dif = strlen(x) - strlen(buffercopycopy);
          if (dif < 0) return false;
          if (strcmp(buffercopycopy, x+dif) == 0) return true;
          else return false;
        }
      }
      j = 0;
      for(int k = 0; keys[j]; j++, k++) {
        if (x[k] == '\0') {
          return false;
        }
        if (keys[j] == '0') {
          if (buffer[j] != x[k]) {
            return false;
          }
        }
        if (keys[j] == '3') {
          if (x[k] > buffercopy[j] || x[k] < buffer[j]) {
            return false;
          }
        }
        if (keys[j] == '4') {
          if (x[k] <= buffercopy[j] && x[k] >= buffer[j]) {
            return false;
          }
        }
        if (keys[j+1] == '\0' && x[k+1] != '\0') {
          return false;
        }
        if (keys[j+1] == '2' && buffer[j+2] == '\0') break;
        if (keys[j+1] == '2') {
          strcpy(buffercopycopy, buffer+j+2);
          int dif = strlen(x) - strlen(buffercopycopy);
          if (dif < 0) return false;
          if (strcmp(buffercopycopy, x+dif) == 0) return true;
          else return false;
        }
      }

      return true;
    }
};
#endif
