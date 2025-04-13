#ifndef LIST 
#define LIST

#include "list_node.h"
#include "command.h"
#include "hash.h"
#include "hashphone.h"
#include "list1.h"

class record_name;

class list {
  private:
    hashtable tab;
    hashtable_phone tabp;
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
      if (tab.add_entry(tail, con) == false) {delete_list(); return io_status::memory; }
      if (tabp.add_entry(tail, con) == false) {delete_list(); tab.delete_hash(); return io_status::memory; }
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
        if(tab.add_entry(tail, con) == false) {delete_list(); return io_status::memory;}
        if (tabp.add_entry(tail, con) == false) {delete_list(); tab.delete_hash(); return io_status::memory; }
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
      printf("insert: ");
      buff.print();
      list4* res = tabg.find_value_name(&buff, con);
      if (res != nullptr) {
        int flag = 0;
        if ((res->get_body())->is_eq(buff)) {
          flag = 1;
          if ((res->get_body())->get_del() == false) return false;
          else (res->get_body())->set_del(false);
        }
        for (list1_node * cur = res->get_next(); cur; cur = cur->get_next()) {
          if ((cur->get_body())->is_eq(buff)) {
            flag = 1;
            if ((cur->get_body())->get_del() == false) return false;
            else (cur->get_body())->set_del(false);
          }
        }
        if (flag == 1) return true;
      }
      list_node *tail;
      tail = new list_node;
      if (tail == nullptr) {
        return false;
      }
      *tail = (list_node&&) buff;
      if (ltail) ltail->set_next(tail);
      if (head != nullptr) tail->set_prev(ltail);
      ltail = tail;
      if (head == nullptr) head = ltail;
      tab.add_entry(tail, con);
      tabp.add_entry(tail, con);
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
        tab.delete_hash();
        tabp.delete_hash();
        tabg.delete_hash();
        return true;
      }
      if (strcmp(s, "where") != 0) return false;
      command buff;
      list_node *curr, *next;
      buff.where_parse(s);
      printf("delete: ");
      buff.print();
      int res = buff.is_good();
      res = 100;
      if (res == 1) {
        record temp;
        temp.init(buff.get_name(), 0, 0);
        list4 * nodes = tab.find_value(&temp, con);
        if (nodes == nullptr) return true;
        if (nodes->get_body() && ((nodes->get_body())->get_del() == false) && buff.apply(*(nodes->get_body()))) {
          (nodes->get_body())->set_del(true);
        }
        list1_node * cur;
        for (cur = nodes->get_next(); cur; cur = cur->get_next()) {
          if (cur->get_body() && ((cur->get_body())->get_del() == false) && buff.apply(*(cur->get_body()))) {
            (cur->get_body())->set_del(true);
          }
        }
      }
      else if (res == 2) {
        record temp;
        temp.init(nullptr, buff.get_phone(), 0);
        list3 * nodes = tabp.find_value(&temp, con);
        if (nodes == nullptr) return true;
        if (nodes->get_body() && ((nodes->get_body())->get_del() == false) && buff.apply(*(nodes->get_body()))) {
          (nodes->get_body())->set_del(true);
        }
        list1_node * cur;
        for (cur = nodes->get_next(); cur; cur = cur->get_next()) {
          if (cur->get_body() && ((cur->get_body())->get_del() == false) && buff.apply(*(cur->get_body()))) {
            (cur->get_body())->set_del(true);
          }
        }
      }
      else if (res == 3) {
        list1 tempqueue;
        record temp;
        temp.init(buff.get_name(), 0, 0);
        list4 * nodes = tab.find_value(&temp, con);
        if (nodes == nullptr) goto phone;
        if (nodes->get_body() && ((nodes->get_body())->get_del() == false) && buff.apply(*(nodes->get_body()))) {
          tempqueue.add_node((nodes->get_body()));
        }
        list1_node * cur;
        for (cur = nodes->get_next(); cur; cur = cur->get_next()) {
          if (cur->get_body() && ((cur->get_body())->get_del() == false) && buff.apply(*(cur->get_body()))) {
            tempqueue.add_node((cur->get_body()));
          }
        }
phone:
        temp.init(nullptr, buff.get_phone(), 0);
        list3 * nodess = tabp.find_value(&temp, con);
        if (nodess == nullptr) goto checking;
        list1_node * curr;
        if (nodess->get_body() && ((nodess->get_body())->get_del() == false) && buff.apply(*(nodess->get_body()))) {
          tempqueue.add_node((nodess->get_body()));
        }
        for (curr = nodess->get_next(); curr; curr = curr->get_next()) {
          if (curr->get_body() && ((curr->get_body())->get_del() == false) && buff.apply(*(curr->get_body()))) {
            tempqueue.add_node((curr->get_body()));
          }
        }
checking:
        if (tempqueue.get_head() == nullptr) return true;
        if ((tempqueue.get_head())->get_next() == nullptr) {
          ((tempqueue.get_head())->get_body())->set_del(true);
        }
        else {
          ordering orders[3] {ordering::name, ordering::phone, ordering::group};
          tempqueue.merge_sort(orders);
          list1_node *prev = tempqueue.get_head();
          for (curr = (tempqueue.get_head())->get_next(); curr; curr = curr->get_next()) {
            if ((curr->get_body())->is_eq(*(prev->get_body())) == false) {
              (prev->get_body())->set_del(true);
            }
            prev = curr;
          }
          (prev->get_body())->set_del(true);
        }
        return true;
      }
      else if (res == -1) {
        record temp;
        temp.init(buff.get_name(), 0, buff.get_group());
        list4 * nodes = tabg.find_value_name(&temp, con);
        if (nodes == nullptr) return true; 
        if (nodes->get_body() && ((nodes->get_body())->get_del() == false) && buff.apply(*(nodes->get_body()))) {
          (nodes->get_body())->set_del(true);
        }
        list1_node * cur;
        for (cur = nodes->get_next(); cur; cur = cur->get_next()) {
          if (cur->get_body() && ((cur->get_body())->get_del() == false) && buff.apply(*(cur->get_body()))) {
            (cur->get_body())->set_del(true);
          }
        }
      }
      else if (res == -2) {
        record temp;
        temp.init(nullptr, buff.get_phone(), buff.get_group());
        list3 * nodes = tabg.find_value_phone(&temp, con);
        if (nodes == nullptr) return true;
        list1_node * cur;
        if (nodes->get_body() && ((nodes->get_body())->get_del() == false) && buff.apply(*(nodes->get_body()))) {
          (nodes->get_body())->set_del(true);
        }
        for (cur = nodes->get_next(); cur; cur = cur->get_next()) {
          if (cur->get_body() && ((cur->get_body())->get_del() == false) && buff.apply(*(cur->get_body()))) {
            (cur->get_body())->set_del(true);
          }
        }
      }
      else {
        for (curr = head; curr; curr = next) {
          if (buff.apply(*curr)) {
            curr->set_del(true);
          }
          next = curr->get_next();
        }
      }
      return true;
    }

    int check(command &com, ordering * order, config con) {
      printf("select: ");
      com.print();
      list_node * curr;
      list1 queue;
      int count = 0;
      int res = com.is_good();
      if (res == 1) {
        record temp;
        temp.init(com.get_name(), 0, 0);
        list4 * nodes = tab.find_value(&temp, con);
        if (nodes == nullptr) return 0; 
        if (nodes->get_body() && ((nodes->get_body())->get_del() == false) && com.apply(*(nodes->get_body()))) {
          queue.add_node((nodes->get_body()));
          count++;
        }
        list1_node * cur;
        for (cur = nodes->get_next(); cur; cur = cur->get_next()) {
          if (cur->get_body() && ((cur->get_body())->get_del() == false) && com.apply(*(cur->get_body()))) {
            queue.add_node((cur->get_body()));
            count++;
          }
        }
      }
      else if (res == 2) {
        record temp;
        temp.init(nullptr, com.get_phone(), 0);
        list3 * nodes = tabp.find_value(&temp, con);
        if (nodes == nullptr) return 0;
        list1_node * cur;
        if (nodes->get_body() && ((nodes->get_body())->get_del() == false) && com.apply(*(nodes->get_body()))) {
          queue.add_node((nodes->get_body()));
          count++;
        }
        for (cur = nodes->get_next(); cur; cur = cur->get_next()) {
          if (cur->get_body() && ((cur->get_body())->get_del() == false) && com.apply(*(cur->get_body()))) {
            queue.add_node((cur->get_body()));
            count++;
          }
        }
      }
      else if (res == 3) {
        list1 tempqueue;
        record temp;
        temp.init(com.get_name(), 0, 0);
        list4 * nodes = tab.find_value(&temp, con);
        if (nodes == nullptr) goto phone;
        if (nodes->get_body() && ((nodes->get_body())->get_del() == false) && com.apply(*(nodes->get_body()))) {
          tempqueue.add_node((nodes->get_body()));
        }
        list1_node * cur;
        for (cur = nodes->get_next(); cur; cur = cur->get_next()) {
          if (cur->get_body() && ((cur->get_body())->get_del() == false) && com.apply(*(cur->get_body()))) {
            tempqueue.add_node((cur->get_body()));
          }
        }
phone:
        temp.init(nullptr, com.get_phone(), 0);
        list3 * nodess = tabp.find_value(&temp, con);
        if (nodess == nullptr) goto checking;
        list1_node * curr;
        if (nodess->get_body() && ((nodess->get_body())->get_del() == false) && com.apply(*(nodess->get_body()))) {
          tempqueue.add_node((nodess->get_body()));
        }
        for (curr = nodess->get_next(); curr; curr = curr->get_next()) {
          if (curr->get_body() && ((curr->get_body())->get_del() == false) && com.apply(*(curr->get_body()))) {
            tempqueue.add_node((curr->get_body()));
          }
        }
checking:
        if (tempqueue.get_head() == nullptr) return 0;
        if ((tempqueue.get_head())->get_next() == nullptr) {
          queue.add_node((tempqueue.get_head())->get_body());
          count++;
        }
        else {
          ordering orders[3] {ordering::name, ordering::phone, ordering::group};
          tempqueue.merge_sort(orders);
          list1_node *prev = tempqueue.get_head();
          for (curr = (tempqueue.get_head())->get_next(); curr; curr = curr->get_next()) {
            if ((curr->get_body())->is_eq(*(prev->get_body())) == false) {
              queue.add_node(prev->get_body());
              count++;
            }
            prev = curr;
          }
          queue.add_node(prev->get_body());
          count++;
        }
      }
      else {
        for (curr = head; curr; curr = curr->get_next()) {
          if (curr->get_del() == false && com.apply(*curr)) {
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
