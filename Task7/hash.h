#ifndef HASH
#define HASH
#define TABLELENGTH 1000

#include "config.h"
#include "record.h"
#include "list1.h"
#include "btree.h"

class record_name {
  private:
    list1 names;
  public:
    record_name() = default;
    record_name(const record_name& ) = delete;
    record_name(record_name && x) = default;
    ~record_name() = default;
    record_name& operator = (const record_name&) = delete;
    record_name& operator = (record_name&& x) = default;
    const char * get_name() {
      if (names.get_head() == nullptr) return nullptr;
      return (names.get_head())->get_name();
    }
    int operator> (record_name& x){
      return (cmp (x) > 0 ? 1 : 0);
    }
    int operator< (record_name& x) {
      return (cmp (x) < 0 ? 1 : 0);
    }
    int operator== (record_name& x) {
      return (cmp (x) == 0 ? 1 : 0);
    }
    void add_value(list_node * x) {names.add_node(x);}
    list1 * get_names() {return &names;}
    void print(FILE *fp) {
      list1_node * curr;
      for (curr= names.get_head(); curr; curr = curr->get_next()) {
        fprintf(fp, "%s\n", curr->get_name());
      }
    }
  private:
    int cmp(record_name& x) {
      if (get_name() == nullptr) {
        if (x.get_name() == nullptr) return 0;
        return -1;
      }
      if (x.get_name() == nullptr) return 1;
      return strcmp(get_name(), x.get_name());
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
      //printf("name = %s, key = %d\n", name, hash);
      return hash;
    }
    void add_value(list_node *x, int l) {
      if(x == nullptr) return;
      record_name base;
      base.add_value(x);
      key = l;
      record_name * cop = birch.find(base);
      if (cop) cop->add_value(x);
      else birch.add_value(base);
    }
    record_name * find(record *x) {
      record_name temp;
      list_node buf;
      if (x == nullptr) return nullptr;
      const char * name = x->get_name();
      if (name == nullptr) return nullptr;
      buf.init(name, 0, 0);
      temp.add_value(&buf);
      return birch.find(temp);
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
      for (int i = 0; i < TABLELENGTH; i++) {
        if (body[i].get_key() != 0) body[i].print();
      }
    }
    hashtable() = default;
    ~hashtable() = default;
    void add_entry(list_node *x, config conf) {
      hashentry temp;
      temp.init(conf, x->get_name());
      int l = temp.get_key();
      body[l].add_value(x, l);
    }
    record_name * find_value(record *x, config conf) {
      hashentry temp;
      int hash = temp.hash_calc(x->get_name(), conf);
      return body[hash].find(x);
    }

};

#endif
