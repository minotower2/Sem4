#ifndef LISTLESS 
#define LISTLESS 

#include "list_node.h"
class list3;
class list4;
class listless {
  friend class list3;
  friend class list4;
  private:
    list_node *body = nullptr;
    list1_node *next = nullptr;
  public:
    listless() = default;
    ~listless() {
      delete_list();
    }
    listless(const listless&) = delete;
    listless(listless&& x) {
      body = x.body; x.body = nullptr;
      next = x.next; x.next = nullptr;
    }
    listless& operator = (const listless& x) = delete;
    listless& operator = (listless && x) {
      if (this == &x) return *this;
      body = x.body; x.body = nullptr;
      next = x.next; x.next = nullptr;
      return *this;
    }
  public:
    list_node * get_body() {return body;}
    void set_body(list_node *x) {body = x;}
    void set_next(list1_node *x) {next = x;}
    list1_node * get_next() {return next;}

    void delete_list() {
      list1_node *curr;
      for (curr = next; curr; curr = next) {
        next = curr->get_next();
        delete curr;
      }
      next = nullptr;
      body = nullptr;
    }

    bool add_node (list_node *x) {
      if (body == nullptr) {body = x; return true;}
      list1_node *tail = new list1_node;
      if (tail == nullptr) return false;
      tail->set_body(x);
      if (next == nullptr) next = tail;
      else {
        list1_node *temp = next;
        next = tail;
        tail->set_next(temp);
      }
      return true;
    }
    void print_list (ordering *order){
      const list1_node *curr;
      if (body) body->print(order);
      for (curr = next; curr; curr = curr->get_next()) {
        if (curr->body) (curr->body)->print(order);
      }
    }
    void print(FILE *fp) {
      (void) fp;
      print_list(nullptr);
    }
};

class list3: public listless {
  public:
    int get_phone() {
      if (body == nullptr) return 0;
      return body->get_phone();
    }
    int operator> (list3& x){
      return (cmp (x) > 0 ? 1 : 0);
    }
    int operator< (list3& x) {
      return (cmp (x) < 0 ? 1 : 0);
    }
    int operator== (list3& x) {
      return (cmp (x) == 0 ? 1 : 0);
    }
    bool add_value(list_node * x) {
      return add_node(x);
    }
  private:
    int cmp(list3& x) {
      return get_phone() < x.get_phone();
    }
};

class list4 : public listless {
  public:
    const char * get_name() {
      if (body == nullptr) return nullptr;
      return body->get_name();
    }
    int operator> (list4& x){
      return (cmp (x) > 0 ? 1 : 0);
    }
    int operator< (list4& x) {
      return (cmp (x) < 0 ? 1 : 0);
    }
    int operator== (list4& x) {
      return (cmp (x) == 0 ? 1 : 0);
    }
    bool add_value(list_node * x) {
      return add_node(x);
    }
  private:
    int cmp(list4& x) {
      if (get_name() == nullptr) {
        if (x.get_name() == nullptr) return 0;
        return -1;
      }
      if (x.get_name() == nullptr) return 1;
      return strcmp(get_name(), x.get_name());
    }

};

#endif
