#ifndef RB_TREE_H
#define RB_TREE_H

#include "student.h"

template <class T> class rb_tree;
template <class T>
class rb_tree_node: public T {
  enum color {
    invalid,
    red,
    black,
  };
  friend class rb_tree<T>;
  private:
    rb_tree_node *left = nullptr;
    rb_tree_node *right = nullptr;
    rb_tree_node *parent = nullptr;
    color color = invalid;
  public:
    rb_tree_node() = default;
    rb_tree_node(const rb_tree_node& x) = delete;
    rb_tree_node(rb_tree_node &&x) : T ((T&&)x) {
      erase_links();
      x.erase_links();
    }
    ~rb_tree_node() {
      erase_links();
    }
    rb_tree_node& operator= (const rb_tree_node& x) = delete;
    rb_tree_node& operator= (rb_tree_node &&x) {
      if (this == &x) return *this;
      (T&&) *this = (T&&) x;
      erase_links();
      x.erase_links();
      return *this;
    }
  private:
    void erase_links() {
      left = nullptr;
      right = nullptr;
      parent = nullptr;
    }
};


template <class T>
class rb_tree {
  private:
    rb_tree_node<T> *root = nullptr;
  public:
    rb_tree() = default;
    ~rb_tree() {
      delte_subtree(root);
    }
    rb_tree(const rb_tree&) = delete;
    rb_tree(rb_tree&& x) = delete;
    rb_tree& operator= (const rb_tree& x) = delete;
    rb_tree& operator= (rb_tree&& x) = delete;
    void print (unsigned int r = 10, FILE *fp = stdout) const {
      print_subtree (root, 0, r, fp);
    }
    io_status read (FILE * fp = stdin, unsigned int max_read = -1) {
      rb_tree_node<T> x; unsigned int count = 0;
      while(x.read(fp) == io_status::success && count < max_read) {
        rb_tree_node<T> *curr = new rb_tree_node<T> ();
        *curr = (rb_tree_node<T>&&) x;
        if (curr == nullptr) {
          delete_subtree(root);
          return io_status::memory;
        }
        if (root == nullptr) root = curr;
        else add_node_subtree(root, curr);
        if (count == max_read) return io_status::success;
      }
      if (!feof(fp)) return io_status::eof;
      return io_status::success;
    }

  private:
    void delete_subtree(rb_tree_node<T> *curr) {
      if (curr == nullptr) return;
      if (curr->left) delete_subtree(curr->left);
      if (curr->right) delete_subtree(curr->right);
      delete curr;
    }
    static void print_subtree (rb_tree_node<T> * curr, int level, int r, FILE *fp = stdout) {
      if (curr == nullptr || level > r) return;
      int spaces = level * 2;
      for (int i = 0; i < spaces; i++) fprintf (fp, " ");
      curr->print (fp);
      print_subtree (curr->left, level + 1, r, fp);
      print_subtree (curr->right, level + 1, r, fp);
  }
    static void add_node_subtree(rb_tree_node<T> *curr, rb_tree_node<T> *x) {

    }

};


#endif
