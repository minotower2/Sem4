#ifndef LIST 
#define LIST

#include "list_node.h"
#include "command.h"

class list1 {
  private:
    list1_node *head = nullptr;
    list1_node *ltail = nullptr;
  public:
    list1() = default;
    ~list1() {
      delete_list();
    }

    void delete_list() {
      list1_node *curr, *next;
      for (curr = head; curr; curr = next) {
        next = curr->get_next();
        delete curr;
      }
      head = nullptr;
    }

    void add_node (record *x) {
      list1_node *tail = new list1_node;
      tail->body = x;
      if (head == nullptr) {head = tail; ltail = head;}
      else {
        ltail->next = tail;
        ltail = tail;
      }
    }

    void print_list (ordering *order){
      const list1_node *curr;
      for (curr = head; curr; curr = curr->get_next()) {
        if (curr->body) (curr->body)->print(order);
      }
    }

    list1_node * merge_lists(list1_node * head_a, list1_node * head_b, ordering * order) {
      list1_node * curr_a = head_a, * curr_b = head_b;
      list1_node * merged_tail = nullptr, * merged_head = nullptr;

      if (curr_a == nullptr) return curr_b;
      if (curr_b == nullptr) return curr_a;

      if ((*curr_a).cmp(*curr_b, order) == 0) {
        merged_tail = curr_a;
        merged_head = merged_tail;
        curr_a = curr_a->next;
      }
      else {
        merged_tail = curr_b;
        merged_head = merged_tail;
        curr_b = curr_b->next;
      }

      while (curr_a && curr_b) {
        if ((*curr_b).cmp(*curr_a, order) == 1) {
          merged_tail->next = curr_a;
          merged_tail = curr_a;
          curr_a = curr_a->next;
        }
        else {
          merged_tail->next = curr_b;
          merged_tail = curr_b;
          curr_b = curr_b->next;
        }
      }

      if(curr_a) merged_tail->next = curr_a;
      if(curr_b) merged_tail->next = curr_b;

      return merged_head;
    }

    list1_node * split_list(list1_node * curr, unsigned int len) {
      list1_node * next = curr;
      unsigned int size = 0;
      if(curr == nullptr) return nullptr;
      while (next != nullptr && size < len) {
        size++;
        curr = next;
        next = curr->next;
      }
      curr->next = nullptr;
      return next;
    }

    list1_node* get_tail(list1_node * curr) {
      if (curr == nullptr) return nullptr;
      while (curr->get_next() != nullptr) {
        curr = curr->get_next();
      }
      return curr;
    }

    void merge_sort(ordering *order) {
      list1_node *head_a = nullptr, *head_b = nullptr;
      list1_node *merged_head = nullptr, *merged_tail = nullptr;
      unsigned int group_size = 1;

      if (head == nullptr) return;

      head_a = head;
      head_b = split_list(head_a,group_size);
      head = split_list(head_b,group_size);

      merged_head = merge_lists(head_a, head_b, order);
      merged_tail = get_tail(merged_head);

      while (head_b != nullptr) {
        while (head != nullptr) {
          head_a = head;
          head_b = split_list(head_a, group_size);
          head = split_list(head_b, group_size);
          merged_tail->next = merge_lists(head_a, head_b, order);
          merged_tail = get_tail(merged_tail);
        }

        group_size *= 2;

        head = merged_head;
        head_a = head;
        head_b = split_list(head_a, group_size );
        head = split_list(head_b, group_size);
        merged_head = merge_lists(head_a, head_b, order);
        merged_tail = get_tail(merged_head);
      }

      head = head_a;
    }
};

class list {
  private:
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

    io_status read_list (FILE* fp) {
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
    bool parse_insert(const char *string) {
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
      list_node *curr;
      for (curr = head; curr; curr = curr->get_next()) {
        if (buff.is_eq(*curr)) {
          return false;
        }
      }
      list_node *tail;
      tail = new list_node;
      if (tail == nullptr) {
        delete_list();
        return false;
      }
      *tail = (list_node&&) buff;
      if (ltail) ltail->set_next(tail);
      if (head != ltail) tail->set_prev(ltail);
      ltail = tail;
      if (head == nullptr) head = ltail;
      return true;
    }

    bool delete_parse(const char *string) {
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
          if (curr == head) {
            if (curr->get_next()) {
              head = curr->get_next();
              curr->erase();
              delete curr;
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

    int check(command &com, ordering * order) {
      list_node * curr;
      list1 queue;
      int count = 0;
      int flag = com.get_ordering()[0] == ordering::none ? 1 : 0;
      for (curr = head; curr; curr = curr->get_next()) {
        if (com.apply(*curr)) {
          if (flag == 0) queue.add_node(curr);
          else curr->print(order);
          count++;
        }
      }
      if (flag == 0) {
        queue.merge_sort(com.get_ordering());
        queue.print_list(order);
      }
      return count;
    }
};

#endif
