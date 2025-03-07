#ifndef LIST 
#define LIST

#include "list_node.h"
#include "command.h"

class list {
  private:
    list_node * head = nullptr;
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

    int check(command &com) {
      list_node * curr;
      int count = 0;
      for (curr = head; curr; curr = curr->get_next()) {
        if (com.apply(*curr)) {
          curr->print();
          count++;
        }
      }
      return count;
    }
};

#endif
