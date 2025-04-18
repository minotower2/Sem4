#ifndef HASHPRIME
#define HASHPRIME

#include "config.h"
#include "record.h"
#include "listless.h"
#include "btree.h"

class hashentryprime {
  private:
    b_tree <list4> birch;
  public:
    hashentryprime() : birch() {};
    void init(config conf) {
      birch.set_m(conf.get_m());
    }
    void delete_tree() {
      birch.delete_tree();
    }
    void print() {
      birch.print(10);
    }
    ~hashentryprime() = default;
    hashentryprime(const hashentryprime&) = delete;
    hashentryprime(hashentryprime&&) {
      birch.erase_links();
    }
    hashentryprime& operator = (const hashentryprime&) = delete;
    hashentryprime& operator = (hashentryprime&& x) {
      if (this == &x) return *this;
      birch = (b_tree<list4> &&)x.birch; (x.birch).erase_links();
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
      hash %= TABLELENGTHPRIME;
      if (hash < 0) hash = hash*(-1);
      //printf("name = %s, key = %d\n", name, hash);
      return hash;
    }
    bool add_value(list_node *x) {
      if(x == nullptr) return false;
      list4 base;
      if (base.add_value(x) == false) {return false;}
      list4 * cop = birch.find(base);
      if (cop) {cop->add_value(x);}
      else birch.add_value(base);
      return true;
    }
    list4 * find(record *x) {
      list4 temp;
      list_node buf;
      if (x == nullptr) return nullptr;
      const char * name = x->get_name();
      if (name == nullptr) return nullptr;
      buf.init(name, 0, 0);
      temp.add_value(&buf);
      return birch.find(temp);
    }
    bool delete_record(list_node * x) {
      list4 temp; temp.add_value(x); return birch.delete_node(temp);
    }
};

class hashtableprime {
  private:
    hashentryprime body[TABLELENGTHPRIME];
  public:
    void print() {
      for (int i = 0; i < TABLELENGTHPRIME; i++) {
        printf("key = %d\n", i);
        body[i].print();
      }
    }
    hashtableprime() = default;
    ~hashtableprime() = default;
    bool add_entry(list_node *x, config conf) {
      hashentryprime temp;
      int l = temp.hash_calc(x->get_name(), conf);
      //printf("name = %s, key = %d\n", x->get_name(), l);
      body[l].init(conf);
      return body[l].add_value(x);
    }
    list4 * find_value(record *x, config conf) {
      hashentryprime temp;
      int hash = temp.hash_calc(x->get_name(), conf);
      return body[hash].find(x);
    }
    bool delete_list(list_node * x, config conf) {
      hashentryprime temp;
      int hash = temp.hash_calc(x->get_name(), conf);
      return body[hash].delete_record(x);
    }
    void delete_hash() {
      for (int i = 0; i < TABLELENGTHPRIME; i++) {
        body[i].delete_tree();
      }
    }
};


#endif
