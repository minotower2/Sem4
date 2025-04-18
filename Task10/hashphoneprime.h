#ifndef HASHPHONEPRIME
#define HASHPHONEPRIME

#include "config.h"
#include "record.h"
#include "listless.h"
#include "btree.h"

class hashentryprime_phone {
  private:
    b_tree <list3> birch;
  public:
    hashentryprime_phone() : birch() {};
    void init(config conf) {
      birch.set_m(conf.get_n());
    }
    void delete_tree() {
      birch.delete_tree();
    }
    void print() {
      birch.print(10);
    }
    ~hashentryprime_phone() = default;
    hashentryprime_phone(const hashentryprime_phone&) = delete;
    hashentryprime_phone(hashentryprime_phone&&) {
      birch.erase_links();
    }
    hashentryprime_phone& operator = (const hashentryprime_phone&) = delete;
    hashentryprime_phone& operator = (hashentryprime_phone&& x) {
      if (this == &x) return *this;
      birch = (b_tree<list3> &&)x.birch; (x.birch).erase_links();
      return *this;
    }
    int hash_calc(int phone, config conf) {
      int hash = 0;
      hash = phone;
      int divisor = 1;
      for (int i = 0; i < conf.get_l(); i++) {
        divisor *= 10;
      }
      if (hash < 0) hash = hash*(-1);
      if (hash < divisor) return hash % TABLELENGTHPRIME;
      return (hash / (divisor / 10)) % TABLELENGTHPRIME;
    }
    bool add_value(list_node *x) {
      if(x == nullptr) return false;
      list3 base;
      if (base.add_value(x) == false) {return false;}
      list3 * cop = birch.find(base);
      if (cop) {cop->add_value(x);}
      else birch.add_value(base);
      return true;
    }
    list3 * find(record *x) {
      list3 temp;
      list_node buf;
      if (x == nullptr) return nullptr;
      int phone = x->get_phone();
      buf.init(nullptr, phone, 0);
      temp.add_value(&buf);
      return birch.find(temp);
    }
    bool delete_record(list_node * x) {
      list3 temp;
      temp.add_value(x);
      return birch.delete_node(temp);
    }
    void add_all_to(list1 &x) {
      birch.add(birch.get_root(), x);
    }
};

class hashtableprime_phone {
  private:
    hashentryprime_phone body[TABLELENGTHPRIME];
  public:
    void print() {
      for (int i = 0; i < TABLELENGTHPRIME; i++) {
        printf("key = %d\n", i);
        body[i].print();
      }
    }
    hashtableprime_phone() = default;
    ~hashtableprime_phone() = default;
    bool add_entry(list_node *x, config conf) {
      hashentryprime_phone temp;
      int l = temp.hash_calc(x->get_phone(), conf);
      //printf("name = %s, key = %d\n", x->get_name(), l);
      body[l].init(conf);
      return body[l].add_value(x);
    }
    list3 * find_value(record *x, config conf) {
      hashentryprime_phone temp;
      int hash = temp.hash_calc(x->get_phone(), conf);
      return body[hash].find(x);
    }
    bool delete_list(list_node * x, config conf) {
      hashentryprime_phone temp;
      int hash = temp.hash_calc(x->get_phone(), conf);
      return body[hash].delete_record(x);
    }
    void delete_hash() {
      for (int i = 0; i < TABLELENGTHPRIME; i++) {
        body[i].delete_tree();
      }
    }
    void add_all_to(list1 &x) {
      for (int i = 0; i < TABLELENGTHPRIME; i++) {
        body[i].add_all_to(x);
      }
    }
};


#endif
