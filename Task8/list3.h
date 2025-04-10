#ifndef LIST3
#define LIST3
#include "list_node.h"
class list3 {
  private:
    list_node *body = nullptr;
    list1_node *next = nullptr;
  public:
    list3() = default;
    ~list3() {
      delete_list();
    }
    list3(const list3&) = delete;
    list3(list3&& x) {
      body = x.body; x.body = nullptr;
      next = x.next; x.next = nullptr;
    }
    list3& operator = (const list3& x) = delete;
    list3& operator = (list3 && x) {
      if (this == &x) return *this;
      body = x.body; x.body = nullptr;
      next = x.next; x.next = nullptr;
      return *this;
    }

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
#endif
