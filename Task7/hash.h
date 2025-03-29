#ifndef HASH
#define HASH
#define TABLELENGTH 100000
#include "btree.h"
#include "config.h"
#include "record.h"
#include "list_node.h"

class record_name {
  private:
    list_node *base = nullptr;
  public:
    record_name() = default;
    record_name(const record_name& ) = delete;
    record_name(record_name && x) {
      base = x.base; x.base = nullptr;
    } 
    ~record_name() = default;
    record_name& operator = (const record_name&) = delete;
    record_name& operator = (record_name&& x) {
      if (this == &x) return *this;
      base = x.base; x.base = nullptr;
      return *this;
    }
    record * get_base() {return base;}
    void set_base(list_node * x) {base = x;}
    int operator < (record_name& x) {return cmp(x) < 0;}
    int operator > (record_name& x) {return cmp(x) > 0;}
    int operator <= (record_name& x) {return cmp(x) <= 0;}
    int operator >= (record_name& x) {return cmp(x) >= 0;}
    int operator == (record_name& x) {return cmp(x) == 0;}
    int operator != (record_name& x) {return cmp(x) != 0;}
    void print(FILE *fp = stdout) {
      (void) fp;
      (*base).print();
    }

  private:
    int cmp(record_name & x) {
      if (base->get_name() == nullptr) {
        if ((x.get_base())->get_name() == nullptr) return 0;
        else return -1;
      }
      int res = strcmp(base->get_name(), (x.get_base())->get_name());
      if (res != 0) return res;
      int p1 = base->get_phone(), p2 = (x.get_base())->get_phone();
      if (p1 < p2) return -1;
      if (p1 > p2) return 1;
      int g1 = base->get_group(), g2 = (x.get_base())->get_group();
      if (g1 < g2) return -1;
      if (g1 > g2) return 1;
      return 0;
    }
};

class hashentry {
  private:
    int key = 0;
    b_tree<record_name> birch;
  public:
    hashentry() = default;
    void init(config conf, const char * name) {
      birch.set_m(conf.get_m());
      key = hash_calc(name, conf);
    }
    void print() {
      printf("key = %d\n", key);
      birch.print(10);
    }
    ~hashentry() = default;
    hashentry(const hashentry&) = delete;
    hashentry(hashentry&&) = default;
    hashentry& operator = (const hashentry&) = delete;
    hashentry& operator = (hashentry&& x) {
      if (this == &x) return *this;
      birch = (b_tree<record_name> &&)x.birch; (x.birch).erase_links();
      key = x.key; x.key = 0;
      return *this;
    }
    int hash_calc(const char *name, config conf) {
      int hash = 0;
      long pow = 1, m = 832631, p = 31;
      for (int i = 0; i < conf.get_k(); i++) {
        if (name[i] == '\0') break;
        hash += (hash + (name[i] - 'a' + 1) * pow) % m;
        pow = (pow * p) % m;
      }
      hash %= TABLELENGTH;
      return hash;
    }
    void add_value(list_node *x) {
      record_name base;
      base.set_base(x);
      birch.add_value(base);
    }
    record_name * find(record_name *x) {
      return birch.find(*x);
    }
    int get_key() {return key;}
    int operator < (hashentry& x) {return key < x.get_key();}
    int operator > (hashentry& x) {return key > x.get_key();}
    int operator <= (hashentry& x) {return key <= x.get_key();}
    int operator >= (hashentry& x) {return key >= x.get_key();}
    int operator == (hashentry& x) {return key == x.get_key();}
    int operator != (hashentry& x) {return key != x.get_key();}
};

class hashtable {
  private:
    hashentry body[TABLELENGTH];
    int nonfree = 0;
  public:
    void print() {
      for (int i = 0; i < nonfree; i++) {
        body[i].print();
      }
    }
    hashtable() = default;
    ~hashtable() = default;
    void add_entry(list_node *x, config conf) {
      hashentry temp;
      temp.init(conf, x->get_name());
      int l = 0, r = nonfree, c;
      while (r !=l ) {
        c = (r + l) / 2;
        if (body[c] < temp) l = c + 1;
        else r = c;
      }
      if (body[l] == temp) {
        body[l].add_value(x);
      }
      else {
        for (int i = l+1; i < l+1+nonfree; i++) {
          body[i] = (hashentry &&) body[i-1];
        }
        body[l] = (hashentry&&) temp;
        temp.add_value(x);
        nonfree++;
      }
    }
    record_name * find_value(list_node *x, config conf) {
      hashentry temp;
      int hash = temp.hash_calc(x->get_name(), conf);
      int l = 0, r = nonfree, c;
      while (r !=l ) {
        c = (r + l) / 2;
        if (body[c].get_key() < hash) l = c + 1;
        else r = c;
      }
      if (body[l].get_key() == hash) {
        record_name buf;
        buf.set_base(x);
        return body[l].find(&buf);
      }
      return 0;
    }

};

#endif
