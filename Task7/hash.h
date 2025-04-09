#ifndef HASH
#define HASH
#define TABLELENGTH 5

#include "config.h"
#include "record.h"
#include "list1.h"
#include "btree.h"

class hashentry {
  private:
    int key = 0;
    b_tree <list1> birch;
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
    hashentry(hashentry&&) {
      birch.erase_links();
      key = 0;
    }
    hashentry& operator = (const hashentry&) = delete;
    hashentry& operator = (hashentry&& x) {
      if (this == &x) return *this;
      birch = (b_tree<list1> &&)x.birch; (x.birch).erase_links();
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
    bool add_value(list_node *x, int l) {
      if(x == nullptr) return false;
      list1 base;
      if (base.add_value(x) == false) {return false;}
      key = l;
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
    int get_key() {return key;}
    int operator < (hashentry& x) {return key < x.get_key();}
    int operator > (hashentry& x) {return key > x.get_key();}
    int operator <= (hashentry& x) {return key <= x.get_key();}
    int operator >= (hashentry& x) {return key >= x.get_key();}
    int operator == (hashentry& x) {return key == x.get_key();}
    int operator != (hashentry& x) {return key != x.get_key();}
    bool delete_record(list_node * x) {
      list1 temp;
      temp.add_value(x);
      return birch.delete_node(temp);
    }
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
    bool add_entry(list_node *x, config conf) {
      hashentry temp;
      int l = temp.hash_calc(x->get_name(), conf);
      body[l].init(conf, x->get_name());
      return body[l].add_value(x, l);
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
      if ((l->get_head())->get_next() == nullptr) return false;
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
};


#endif
