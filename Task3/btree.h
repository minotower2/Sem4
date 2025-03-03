#ifndef BTREE
#define BTREE

#include "btree_node.h"

template <class T>
class b_tree {
private:
  int m = 1; // B-tree base
  b_tree_node<T> * root = nullptr;
public:
  b_tree (int i = 1) {m = i;}
  ~b_tree() {
    delete_subtree (root);
    erase_links ();
  }
  void set_m(int k) {m = k;}
  b_tree_node<T> * get_root() {return root;}
  void print (int r, FILE * fp = stdout) const {
    print_subtree (root, 0, r, fp);
  }
private:
  void erase_links () {
    m = 0;
    root = nullptr;
  }
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
  // Add element x to tree
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
  int search(b_tree_node<T> *curr, T& target) {
    if (curr == nullptr) return 0;
    int ind = curr->bin_check(target);
    if (ind != -1 && curr->values[ind] == target) return 1;
    for (int i = 0; i <= curr->size; i++) {
      if (search(curr->children[i], target) == 1) return 1;
    }
    return 0;
  }
};
#endif
