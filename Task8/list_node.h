#ifndef LISTNODE
#define LISTNODE
#include "record.h"

class list;
class list_node: public record {
  friend class list;
private:
  list_node *next = nullptr;
  list_node *prev = nullptr;
public:
  list_node() = default;
  list_node(const list_node& x) = delete;
  list_node(list_node&& x){
    next = x.next; x.next = nullptr;
    prev = x.prev; x.prev = nullptr;
  }
  ~list_node() {
    next = nullptr;
    prev = nullptr;
  }
  list_node& operator=(const list_node& x) = delete;
  list_node& operator=(list_node&& x) {
    *(record*)this = (record&&) x;
    next = x.next; x.next = nullptr;
    prev = x.prev; x.prev = nullptr;
    return *this;
  }
  list_node *get_next() const {return next;}
  list_node *get_prev() const {return prev;}
  void set_next(list_node *x) {next = x;}
  void set_prev(list_node *x) {prev = x;}
  void erase() {next = nullptr; prev = nullptr;}
private:
  bool del = false;
public:
  void set_del(bool x) {del = x;}
  bool get_del() {return del;}
};

class list1;
class list3;
class list1_node {
  friend class list1;
  friend class list3;
  private:
    list_node * body = nullptr;
    list1_node *next = nullptr;
  public:
    list1_node() = default;
    list1_node(const list1_node &x) = delete;
    list1_node(list1_node&& x) {
      next = x.next; x.next = nullptr;
      body = x.body; x.body = nullptr;
    }
    ~list1_node() {next = nullptr; body = nullptr;}
    list1_node& operator=(const list1_node& x) = delete;
    list1_node& operator=(list1_node&& x) {
      body = x.body; x.body = nullptr;
      next = x.next; x.next = nullptr;
      return *this;
    }
    list1_node *get_next() const {return next;}
    const char * get_name() {
      if (body == nullptr) return nullptr;
      return body->get_name();
    }
    int get_phone() {
      if (body == nullptr) return 0;
      return body->get_phone();
    }
    void set_next(list1_node *x) {next = x;}
    void set_body(list_node * x) {body = x;}
    list_node * get_body() {return body;}
    // 1 значит меньше 0 значит больше 2 значит равно
    int cmp(list1_node &x, ordering *order) {
      switch (order[0]) {
        case ordering::none:
          return 2;
        case ordering::name:
          if ((*body).compare_name(condition::lt, *(x.body))) return 1;
          if ((*body).compare_name(condition::gt, *(x.body))) return 0;
          break;
        case ordering::group:
          if ((*body).compare_group(condition::lt, *(x.body))) return 1;
          if ((*body).compare_group(condition::gt, *(x.body))) return 0;
          break;
        case ordering::phone:
          if ((*body).compare_phone(condition::lt, *(x.body))) return 1;
          if ((*body).compare_phone(condition::gt, *(x.body))) return 0;
          break;
      }
      switch (order[1]) {
        case ordering::none:
          return 2;
        case ordering::name:
          if ((*body).compare_name(condition::lt, *(x.body))) return 1;
          if ((*body).compare_name(condition::gt, *(x.body))) return 0;
          break;
        case ordering::group:
          if ((*body).compare_group(condition::lt, *(x.body))) return 1;
          if ((*body).compare_group(condition::gt, *(x.body))) return 0;
          break;
        case ordering::phone:
          if ((*body).compare_phone(condition::lt, *(x.body))) return 1;
          if ((*body).compare_phone(condition::gt, *(x.body))) return 0;
          break;
      }
      switch (order[2]) {
        case ordering::none:
          return 2;
        case ordering::name:
          if ((*body).compare_name(condition::lt, *(x.body))) return 1;
          if ((*body).compare_name(condition::gt, *(x.body))) return 0;
          break;
        case ordering::group:
          if ((*body).compare_group(condition::lt, *(x.body))) return 1;
          if ((*body).compare_group(condition::gt, *(x.body))) return 0;
          break;
        case ordering::phone:
          if ((*body).compare_phone(condition::lt, *(x.body))) return 1;
          if ((*body).compare_phone(condition::gt, *(x.body))) return 0;
          break;
      }
      return 2;
    }
};
#endif
