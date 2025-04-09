#ifndef BTREE
#define BTREE
#include "btree_node.h"

class list1;
template <class T>
class b_tree {
private:
  int m = 2; // B-tree base
  b_tree_node<T> * root = nullptr;
public:
  b_tree() = default;
  b_tree(int i) {m = i;}
  ~b_tree() {
    delete_subtree (root);
    erase_links ();
  }
  b_tree(const b_tree &) = delete;
  b_tree(b_tree && x) {
    root = x.root(); x.root = nullptr;
    m = x.m; x.m = 0;
  }
  b_tree& operator = (const b_tree& x) = delete;
  b_tree& operator = (b_tree&& x) {
    if (this == &x) return *this;
    root = x.root; x.root = nullptr;
    m = x.m; x.m = 0;
    return *this;
  }
  io_status read (FILE * fp = stdin) {
    T x;
    io_status r;
    while(x.read(fp) == io_status::success) {
      r = add_value(x);
      if (r != io_status::success) return r;
    }
    if (!feof(fp)) return io_status::eof;
    return io_status::success;
  }
  void print (int r, FILE * fp = stdout) const {
    print_subtree (root, 0, r, fp);
  }
  void set_m(int n) {m = n;}
  b_tree_node<T> * get_root() {return root;}
  void erase_links () {
    m = 0;
    root = nullptr;
  }
private:
  static void delete_subtree (b_tree_node<T> * curr) {
    if (curr == nullptr) return;
    for (int i = 0; i <= curr->size; i++) delete_subtree (curr->children[i]);
    delete curr;
  }
  static void print_subtree (b_tree_node<T> * curr, int level, int r, FILE * fp = stdout) {
    if (curr == nullptr || level > r) return;
    curr->print (level, fp);
    for (int i = 0; i <= curr->size; i++) {
      if (curr->children[i] && level + 1 <= r) {
        for (int j = 0; j < level; j++) fprintf (fp, "  ");
        fprintf (fp, "children[%2d]\n", i);
        print_subtree (curr->children[i], level + 1, r, fp);
      }
    }
  }
public:
  io_status add_value (T& x) {
    if (root == nullptr) {
      root = new b_tree_node<T>();
      if (root == nullptr) return io_status::memory;
      if (root->init(m) != io_status::success) {
        delete root;
        return io_status::memory;
      }
      root->values[0] = static_cast<T&&>(x);
      root->size = 1;
      return io_status::success;
    }
    b_tree_node<T> *curr = root, *down = nullptr;
    io_status r = add_value_subtree (curr, down, x, m);
    if (r == io_status::memory) return io_status::memory;
    if (r == io_status::success) return io_status::success;
    // иначе r == io_status::create и был создан новый узел
    // который возвращается в ’down’
    // Создаем новый корень с одним значением ’x’
    // и двумя потомками ’curr’ and ’down’
    b_tree_node<T>* p = new b_tree_node<T>();
    if (p == nullptr) return io_status::memory;
    if (p->init (m) != io_status::success) {
      delete p;
      return io_status::memory;
    }
    p->values[0] = static_cast<T&&>(x);
    p->children[0] = curr;
    p->children[1] = down;
    p->size = 1;
    root = p;
    return io_status::success;
  }
  // Insert value ’x’ with children ’down’ at subtree ’curr’
  static io_status add_value_subtree (b_tree_node<T>*& curr, b_tree_node<T>*& down, T& x, int m) {
    int index = curr->bin_search (x);
    b_tree_node<T>* p = curr->children[index];
    if (p != nullptr) { // Есть потомок
      io_status r = add_value_subtree (p, down, x, m);
      if (r == io_status::memory) return io_status::memory;
      if (r == io_status::success) return io_status::success;
      // иначе r == io_status::create
      // и был создан новый узел,
      // который возвращается в ’down’
    }
    else down = nullptr;
    if (curr->size < 2 * m) { // Есть свободное место в текущем узле
      curr->add_value (x, down, index);
      return io_status::success;
    }
    else { // Создаем новый узел
      b_tree_node<T>* p = new b_tree_node<T>();
      if (p == nullptr) return io_status::memory;
      if (p->init (m) != io_status::success) {
        delete p;
        return io_status::memory;
      }
      if (index == m) { // ’x’ ровно посередине.
        // Перемещаем вторую половину в новый узел
        for (int i = 1; i <= m; i++) {
          p->values[i - 1] = static_cast<T&&>(curr->values[i + m - 1]);
          p->children[i] = curr->children[i + m];
          curr->children[i + m] = nullptr;
        }
        p->children[0] = down; // меньше всех
      }
      if (index < m) { // ’x’ в первой половине.
        // Перемещаем вторую половину в новый узел
        for (int i = 0; i < m; i++) {
          p->values[i] = static_cast<T&&>(curr->values[i + m]);
          p->children[i] = curr->children[i + m];
          curr->children[i + m] = nullptr;
        }
        p->children[m] = curr->children[2 * m];
        curr->children[2 * m] = nullptr;
        // сдвигаем элементы вправо
        // и вставляем ’x’ в позицию ’index’
        for (int i = m; i > index; i--) {
          curr->values[i] = static_cast<T&&> (curr->values[i - 1]);
          curr->children[i + 1] = curr->children[i];
        }
        curr->children[index + 1] = down;
        curr->values[index] = static_cast<T&&>(x);
        x = static_cast<T&&> (curr->values[m]);
        // новый ’x’ - максимальный
      }
      if (index > m) { // ’x’ во второй половине.
        // Перемещаем вторую половину до ’index’
        // в новый узел
        p->children[0] = curr->children[m + 1];
        curr->children[m + 1] = nullptr;
        for (int i = 1 ; i < index - m; i++) {
          p->values[i - 1] = static_cast<T&&> (curr->values[i + m]);
          p->children[i] = curr->children[i + m + 1];
          curr->children[i + m + 1] = nullptr;
        }
        // Вставляем ’x’ в нужную позицию
        p->values[index - m - 1] = static_cast<T&&> (x);
        p->children[index - m] = down;
        // Перемещаем остаток второй половины в новый узел
        for (int i = index - m + 1; i <= m; i++) {
          p->values[i - 1] = static_cast<T&&> (curr->values[i + m - 1]);
          p->children[i] = curr->children[i + m];
          curr->children[i + m] = nullptr;
        }
        x = static_cast<T&&> (curr->values[m]);
        // новый ’x’ - максимальный
      }
      down = p;
      p->size = m;
      curr->size = m;
      return io_status::create;
      // создан новый узел, он возвращается в ’down’
    }
    return io_status::success;
  }
public:
  T * find(T &x) {
    return find_subtree(root, x);
  }
  T * find_subtree(b_tree_node<T> *curr, T &x) {
    if (curr == nullptr) return nullptr;
    int i = curr->bin_search(x);
    if (i < curr->size && curr->values[i] == x) return &(curr->values[i]);
    return find_subtree(curr->children[i], x);
  }
private:
  b_tree_node<T> * find_node(b_tree_node<T> * curr, T&x) {
    if (curr == nullptr) return nullptr;
    int i = curr->bin_search(x);
    if (i < curr->size && curr->values[i] == x) return curr;
    return find_node(curr->children[i], x);
  }
public:
  bool delete_node(T& x) {
    b_tree_node<T> * curr = find_node(root, x);
    if (curr == nullptr) return true;
    if (curr->children[0] == nullptr) {
      int i = curr->bin_search(x);
      delete &(curr->values[i]);
      curr->size--;
      if (curr->size == 0) {
        delete curr;
        return true;
      }
      int j;
      for (j = i; j <= curr->size; j++){
        curr->values[j] = (T&&) curr->values[j+1];
      }
    }
    return true;

  }

  
};
#endif
