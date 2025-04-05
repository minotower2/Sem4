#ifndef LIST 
#define LIST

#include "list_node.h"
#include "command.h"
#include "hash.h"

class record_name;

class list {
  private:
    hashtable tab;
    list_node * head = nullptr;
    list_node * ltail = nullptr;
  public:
    list() = default;
    ~list() {
      delete_list();
    }

    void delete_list() {
      list_node *curr, *next;
      for (curr = head; curr; curr = next) {
        next = curr->get_next();
        delete curr;
      }
      head = nullptr;
      ltail = nullptr;
    }
    void print_hash() {tab.print();}

    void print_list (int r = 10){
      const list_node *curr;
      int count = 0;
      if (r < 1) return;
      for (curr = head; curr; curr = curr->get_next()) {
        curr->print();
        count++;
        if (count == r) {
          break;
        }
      }
    }

    io_status read_list (FILE* fp, config con) {
      (void) con;
      list_node buf;
      io_status res;
      list_node *curr, *tail;
      res = buf.read(fp);
      if (res != io_status::success) {
        if (feof(fp)) {head = nullptr; return io_status::success;}
        else {return res;}
      }
      head = new list_node;
      if (head == nullptr) return io_status::memory;
      *head = (list_node&&) buf;
      ltail = head;
      curr = head;
      tail = curr;
      tab.add_entry(tail, con);
      while(buf.read(fp) == io_status::success) {
        tail = new list_node;
        if (tail == nullptr) {
          delete_list();
          return io_status::memory;
        }
        *tail = (list_node&&) buf;
        curr -> set_next(tail);
        curr = tail;
        ltail = tail;
        tab.add_entry(tail, con);
      }
      if (!feof(fp)) {
        delete_list();
        return io_status::eof;
      }
      if (head) {
        tail = head;
        for (curr = head->get_next(); curr; curr = curr->get_next()) {
          curr->set_prev(tail);
          tail = curr;
        }
      }
      return io_status::success;
    }
    bool parse_insert(const char *string, config con) {
      char buf[LEN];
      strcpy(buf, string);
      char *s;
      char name[LEN];
      int phone=0, group=0;
      s = strtok(buf, " \t\n,();");
      if (s == nullptr) return false;
      s = strtok(nullptr, " \n\t,();");
      if (s == nullptr) return false;
      strcpy(name, s);
      s = strtok(nullptr, " \n\t,();");
      if (s == nullptr) return false;
      if (sscanf(s, "%d", &phone) != 1) return false;
      s = strtok(nullptr, " \n\t,();");
      if (s == nullptr) return false;
      if (sscanf(s, "%d", &group) != 1) return false;
      list_node buff;
      if (buff.init(name, phone, group)) return false;
      if (tab.find_value(&buff, con) != nullptr) return false;
      list_node *tail;
      tail = new list_node;
      if (tail == nullptr) {
        delete_list();
        return false;
      }
      *tail = (list_node&&) buff;
      if (ltail) ltail->set_next(tail);
      if (head != nullptr) tail->set_prev(ltail);
      ltail = tail;
      if (head == nullptr) head = ltail;
      tab.add_entry(tail, con);
      return true;
    }

    bool delete_parse(const char *string, config con) {
      char buf[LEN];
      strcpy(buf, string);
      char *s;
      s = strtok(buf, " \t\n;");
      if (s == nullptr) return false;
      s = strtok(nullptr, " \t\n;");
      if (s==nullptr) {
        delete_list();
        return true;
      }
      if (strcmp(s, "where") != 0) return false;
      command buff;
      list_node *curr, *next;
      buff.where_parse(s);
      for (curr = head; curr; curr = next) {
        if (buff.apply(*curr)) {
          if (tab.remove_value(curr, con) == false) {
            tab.delete_list(curr, con);
          }
          if (curr == head) {
            if (curr->get_next()) {
              head = curr->get_next();
              curr->erase();
              delete curr;
              curr = head;
              next = head;
              continue;
            }
            else {
              delete_list();
              return true;
            }
          }
          else if (curr == ltail) {
            list_node *pr = curr->get_prev();
            pr->next = nullptr;
            ltail = pr;
            curr->erase();
            delete curr;
            return true;
          }
          else {
            list_node *p = curr->get_prev();
            list_node *n = curr->get_next();
            if (p) p->next = n;
            n->prev = p;
            curr->erase();
            delete curr;
            curr = p;
          }
        }
        next = curr->get_next();
      }
      return true;
    }

    int check(command &com, ordering * order, config con) {
      list_node * curr;
      list1 queue;
      int count = 0;
      if (com.is_good() == 1) {
        record temp;
        temp.init(com.get_name(), 0, 0);
        record_name * res = tab.find_value(&temp, con);
        if (res == nullptr) return 0;
        list1 * nodes = res->get_names();
        list1_node * cur;
        for (cur = nodes->get_head(); cur; cur = cur->get_next()) {
          if (cur->get_body() && com.apply(*(cur->get_body()))) {
            queue.add_node((cur->get_body()));
            count++;
          }
        }
      }
      else {
        for (curr = head; curr; curr = curr->get_next()) {
          if (com.apply(*curr)) {
            queue.add_node(curr);
            count++;
          }
        }
      }
      queue.merge_sort(com.get_ordering());
      queue.print_list(order);
      return count;
    }
};

#endif
