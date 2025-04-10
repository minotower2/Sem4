#ifndef HASH
#define HASH

#include "config.h"
#include "record.h"
#include "list1.h"
#include "btree.h"

class hashentry {
  private:
    b_tree <list1> birch;
  public:
    hashentry() : birch() {};
    void init(config conf) {
      birch.set_m(conf.get_m());
    }
    void delete_tree() {
      birch.delete_tree();
    }
    void print() {
      birch.print(10);
    }
    ~hashentry() = default;
    hashentry(const hashentry&) = delete;
    hashentry(hashentry&&) {
      birch.erase_links();
    }
    hashentry& operator = (const hashentry&) = delete;
    hashentry& operator = (hashentry&& x) {
      if (this == &x) return *this;
      birch = (b_tree<list1> &&)x.birch; (x.birch).erase_links();
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
      if (hash < 0) hash = hash*(-1);
      //printf("name = %s, key = %d\n", name, hash);
      return hash;
    }
    bool add_value(list_node *x) {
      if(x == nullptr) return false;
      list1 base;
      if (base.add_value(x) == false) {return false;}
      list1 * cop = birch.find(base);
      if (cop) {cop->add_value(x);}
      else birch.add_value(base);
      return true;
    }
    list1 * find(record *x) {
      list1 temp;
      list_node buf;
      if (x == nullptr) return nullptr;
      const char * name = x->get_name();
      if (name == nullptr) return nullptr;
      buf.init(name, 0, 0);
      temp.add_value(&buf);
      return birch.find(temp);
    }
    bool delete_record(list_node * x) {
      list1 temp;
      temp.add_value(x);
      return birch.delete_node(temp);
    }
};

class hashtable {
  private:
    hashentry body[TABLELENGTH];
  public:
    void print() {
      for (int i = 0; i < TABLELENGTH; i++) {
        printf("key = %d\n", i);
        body[i].print();
      }
    }
    hashtable() = default;
    ~hashtable() = default;
    bool add_entry(list_node *x, config conf) {
      hashentry temp;
      int l = temp.hash_calc(x->get_name(), conf);
      //printf("name = %s, key = %d\n", x->get_name(), l);
      body[l].init(conf);
      return body[l].add_value(x);
    }
    list1 * find_value(record *x, config conf) {
      hashentry temp;
      int hash = temp.hash_calc(x->get_name(), conf);
      return body[hash].find(x);
    }
    bool remove_value(list_node * x, config con) {
      list1 * res = find_value(x, con);
      if (res == nullptr) return true;
      list1 * l = res;
      if (l->get_head() == nullptr) return true;
      if ((l->get_head())->get_next() == nullptr) {
        hashentry temp;
        return body[temp.hash_calc(x->get_name(), con)].delete_record(x);
      }
      list1_node * curr = l->get_head();
      if ((curr->get_body())->is_eq(*x)) {
        list1_node * n = curr->get_next();
        curr->set_next(nullptr);
        delete curr;
        l->set_head(n);
      }
      else {
        for (list1_node * currer = (l->get_head())->get_next(); currer; currer = currer->get_next()) {
          if ((currer->get_body())->is_eq(*x)) {
            list1_node * n = currer->get_next();
            currer->set_next(nullptr);
            delete currer;
            curr->set_next(n);
            break;
          }
          curr = currer;
        }
      }
      return true;
    }
    bool delete_list(list_node * x, config conf) {
      hashentry temp;
      int hash = temp.hash_calc(x->get_name(), conf);
      return body[hash].delete_record(x);
    }
    void delete_hash() {
      for (int i = 0; i < TABLELENGTH; i++) {
        body[i].delete_tree();
      }
    }
};


#endif
