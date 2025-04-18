#ifndef LIST1
#define LIST1
#include "list_node.h"
#include "listless.h"
class list1 {
  private:
    list1_node *head = nullptr;
  public:
    list1() = default;
    ~list1() {
      delete_list();
    }
    list1(const list1&) = delete;
    list1(list1&& x) {
      head = x.head; x.head = nullptr;
    }
    list1& operator = (const list1& x) = delete;
    list1& operator = (list1 && x) {
      if (this == &x) return *this;
      head = nullptr;
      head = x.head; x.head = nullptr;
      return *this;
    }

    const char * get_name() {
      if (head == nullptr) return nullptr;
      return head->get_name();
    }
    int operator> (list1& x){
      return (cmp (x) > 0 ? 1 : 0);
    }
    int operator< (list1& x) {
      return (cmp (x) < 0 ? 1 : 0);
    }
    int operator== (list1& x) {
      return (cmp (x) == 0 ? 1 : 0);
    }
    bool add_value(list_node * x) {
      return add_node(x);
    }
  private:
    int cmp(list1& x) {
      if (get_name() == nullptr) {
        if (x.get_name() == nullptr) return 0;
        return -1;
      }
      if (x.get_name() == nullptr) return 1;
      return strcmp(get_name(), x.get_name());
    }
  public:
    
    list1_node * get_head() {return head;}
    void set_head(list1_node *x) {head = x;}

    void delete_list() {
      list1_node *curr, *next;
      for (curr = head; curr; curr = next) {
        next = curr->get_next();
        delete curr;
      }
      head = nullptr;
    }

    bool add_node (list_node *x) {
      list1_node *tail = new list1_node;
      if (tail == nullptr) return false;
      tail->set_body(x);
      if (head == nullptr) {head = tail;}
      else {
        tail->set_next(head);
        head = tail;
      }
      return true;
    }
    void add_nodes(list1 * temp) {
      list_node * curr;
      for (curr = (temp->get_head())->get_body(); curr; curr = curr->get_next()){
        add_node(curr);
      }
    }
    void add_nodes_list3 (list3 * temp) {
      list_node * curr;
      if (temp == nullptr) return;
      curr = temp->get_body();
      if (curr == nullptr) return;
      add_node(curr);
      if (temp->get_next() == nullptr) return;
      for (curr = (temp->get_next())->get_body(); curr; curr = curr->get_next()){
        add_node(curr);
      }
    }

    void print_list (ordering *order){
      const list1_node *curr;
      for (curr = head; curr; curr = curr->get_next()) {
        if (curr->body) (curr->body)->print(order);
      }
    }
    void write_list(ordering *order, int fd) {
      const list1_node *curr = head;
      for (curr = head; curr; curr = curr->get_next()) {
        if (curr->body) (curr->body)->writeToServer(fd, order);
      }
      const char *buf = "SUCCESS";
      int len = strlen(buf);
      len++;
      if (send (fd, &len, sizeof (int), MSG_NOSIGNAL) != (int) sizeof (int)) {
        perror ("write length");
        exit (EXIT_FAILURE);
      }
      // Пересылаем len байт
      int nbytes;
      for (int i = 0; len > 0; i += nbytes, len -= nbytes) {
        nbytes = send (fd, buf + i, len, MSG_NOSIGNAL);
        if (nbytes < 0)   {
          perror ("write");
          exit (EXIT_FAILURE);
        }
        else if (nbytes == 0) {
          perror ("write truncated");
          exit (EXIT_FAILURE);
        }
      }
    }
    void print(FILE *fp) {
      (void) fp;
      print_list(nullptr);
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
#endif
