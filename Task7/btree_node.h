#ifndef BTREENODE
#define BTREENODE
#include "stdio.h"
#include "record.h"

template <class T> class b_tree;

template <class T>
class b_tree_node {
  friend class b_tree<T>;
private:
  T *values = nullptr; // 2*m elements array
  int size = 0; // number of children
  b_tree_node ** children = nullptr; // 2*m+1 elements array
public:
  b_tree_node () = default;
  b_tree_node (const b_tree_node& ) = delete;
  b_tree_node (b_tree_node && x) {
    values = x.values; x.values = nullptr;
    children = x.children; x.children = nullptr;
    size = x.size; x.size = 0;
  }
  ~b_tree_node () {
    erase();
  }
  b_tree_node& operator= (b_tree_node&& x) {
    if (this == x) return *this;
    erase();
    values = x.values; x.values = nullptr;
    children = x.children; x.children = nullptr;
    size = x.size; x.size = 0;
    return *this;
  }
  void print (int p = 0, FILE * fp = stdout) const {
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < p; j++) fprintf (fp, "  ");
      fprintf (fp, "values[%2d] ", i + 1);
      values[i].print (fp);
    }
  }
private:
  void erase() {
    if (values) {
      delete [] values;
      values = nullptr;
    }
    if (children) {
      delete [] children;
      children = nullptr;
    }
  }
  void add_value (T& x, b_tree_node<T>* down, int index) {
    for (int i = size; i > index; i--) { 
      values[i] = static_cast<T&&>(values[i - 1]);
      children[i + 1] = children[i];
    }
    values[index] = static_cast<T&&>(x);
    children[index + 1] = down;
    size++;
  }
  io_status init(int m) {
    values = new T[2*m];
    if (values == nullptr) return io_status::memory;
    children = new b_tree_node* [2*m+1];
    if (children == nullptr) {
      delete values;
      return io_status::memory;
    }
    return io_status::success;
  }
  int bin_search (T& x) {
    int l = 0, r = size, c;
    while (r !=l ) {
      c = (r + l) / 2;
      if (values[c] < x) l = c + 1;
      else r = c;
    }
    return l;
  }
};
#endif
