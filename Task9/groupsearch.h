#include "hashprime.h"
#include "hashphoneprime.h"
#define GROUPS 1000

class search_structure {
  private:
    hashtableprime tab;
    hashtableprime_phone tabp;
  public:
    search_structure() = default;
    ~search_structure() = default;
    bool add_entry(list_node * x, config conf) {
      if (tab.add_entry(x, conf) == false) return false;
      if (tabp.add_entry(x, conf) == false) return false;
      return true;
    }
    list4 * find_value_name(record *x, config conf) {
      return tab.find_value(x, conf);
    }
    list3 * find_value_phone(record *x, config conf) {
      return tabp.find_value(x, conf);
    }
    void delete_hash() {
      tab.delete_hash();
      tabp.delete_hash();
    }
};

class group_search {
  private:
    search_structure groups[GROUPS];
  public:
    group_search() = default;
    ~group_search() = default;
    bool add_entry(list_node *x, config conf) {
      int g = x->get_group();
      if (g < 0 || g >= GROUPS) return false;
      return groups[g].add_entry(x, conf);
    }
    list4 * find_value_name(record *x, config conf) {
      return groups[x->get_group()].find_value_name(x, conf);
    }
    list3 * find_value_phone(record *x, config conf) {
      return groups[x->get_group()].find_value_phone(x, conf);
    }
    void delete_hash() {
      for (int i = 0; i < GROUPS; i++) {
        groups[i].delete_hash();
      }
    }
};
